fn build_and_link() {
    cc::Build::new()
        .cpp(true)
        // This is already done because of `.cpp(true)`:
        // .cpp_link_stdlib(None)
        //
        // See: https://github.com/rust-lang/cc-rs/blob/966183eb651b4ea473cdb32a91120e374f42ba4a/src/lib.rs#L3065
        .file("cpp/db.cpp")
        .compile("db");
}

fn main() {
    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=cpp/db.cpp");
    println!("cargo:rerun-if-changed=cpp/db.hpp");
    println!("cargo:rerun-if-changed=cpp/c_ffi_ext.hpp");

    build_and_link();

    // Options: https://docs.rs/bindgen/latest/bindgen/struct.Builder.html
    let bindings = bindgen::Builder::default()
        .header("wrapper.hpp")
        // Enable C++
        .clang_arg("-x")
        .clang_arg("c++")
        .clang_arg("-std=c++17")
        // .enable_cxx_namespaces()
        // Tell cargo to invalidate the built crate whenever any of the
        // included header files changed.
        .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
        // ignore all std types, they aren't translatable to Rust anyway,
        .opaque_type("std::.*")
        // Allowlist all the types and functions we need.
        .allowlist_type("Movie")
        .allowlist_type("Genre")
        .allowlist_type("MovieDatabase")
        .allowlist_function(".*movie.*")
        .allowlist_recursively(true)
        // Nicer enums
        .default_enum_style(bindgen::EnumVariation::Rust {
            non_exhaustive: false,
        })
        // Implement Debug and Default for all types
        // .impl_debug(true)
        // .derive_debug(true)
        .derive_default(true)
        // Can also be opt-out with the following:
        // https://rust-lang.github.io/rust-bindgen/nocopy.html
        // .no_copy("Movie")
        // .no_debug("Movie")
        .no_default("std::.*")
        .generate()
        .unwrap();

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = std::path::PathBuf::from(std::env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
