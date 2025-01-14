fn main() -> anyhow::Result<()> {
    let include_path = std::path::PathBuf::from("cpp/");
    let cpp_source = std::path::PathBuf::from("cpp/db.cpp");

    autocxx_build::Builder::new("src/main.rs", &[include_path])
        .build()
        .unwrap()
        .flag_if_supported("-std=c++17")
        .file(cpp_source)
        .compile("autocxx-example");  // arbitrary library name, pick anything

    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=cpp/db.cpp");
    println!("cargo:rerun-if-changed=cpp/db.hpp");

    Ok(())
}
