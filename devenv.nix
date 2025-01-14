{ pkgs, lib, config, inputs, ... }:

{
  # https://devenv.sh/packages/
  packages = with pkgs; [
    just
    rust-cbindgen
    libclang

    # LSPs
    clang-tools
    rust-analyzer
  ];

  # https://devenv.sh/languages/
  languages.rust.enable = true;
  languages.cplusplus.enable = true;

  # Fix clang path for NixOS:
  # https://github.com/NixOS/nixpkgs/issues/52447#issuecomment-852079285
  env.LIBCLANG_PATH="${pkgs.llvmPackages.libclang.lib}/lib";

  # See full reference at https://devenv.sh/reference/options/
}
