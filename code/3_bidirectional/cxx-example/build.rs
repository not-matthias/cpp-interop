fn main() {
    cxx_build::bridge("src/main.rs")
        .file("cpp/db.cpp")
        .std("c++17")
        .compile("cxx-example");

    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=cpp/db.cpp");
    println!("cargo:rerun-if-changed=cpp/db.hpp");
}
