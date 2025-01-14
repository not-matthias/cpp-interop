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

fn link_manually() {
    let manifest_dir = std::env::var("CARGO_MANIFEST_DIR").unwrap();
    println!("cargo:rustc-link-search=native={}/build/", manifest_dir);
    println!("cargo:rustc-link-lib=static=db");
    println!("cargo:rustc-link-lib=static=stdc++");
}

fn main() {
    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=cpp/db.cpp");
    println!("cargo:rerun-if-changed=cpp/db.hpp");
    println!("cargo:rerun-if-changed=cpp/c_ffi_ext.hpp");

    build_and_link();
    // or
    // link_manually();
}
