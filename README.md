# cpp-interop-seminar

## Requirements

- VSCode Extension: ms-vscode.cpptools
- Clang (for bindgen, see [here](https://rust-lang.github.io/rust-bindgen/requirements.html))

## Content

The following projects are included in this repository:
- [Manual FFI](./code/1_manual_ffi/)
- [Automatic FFI using bindgen](./code/2_automatic_ffi/)
- [Bidirectional FFI using cxx](./code/3_bidirectional/cxx-example/)
- [Bidirectional FFI using autocxx](./code/3_bidirectional/autocxx-example/)
- [IPC using Sockets](./code/4_ipc/)

The skeleton is designed like this: 
- [c-ffi](./skeleton/c-ffi/): First implement manual FFI for the `db` C++ library and then use bindgen to automate it. Both raw and safe bindings should be written. 
- [cpp-ffi](./skeleton/cxx-ffi/): Generate bindings using cxx. 
- [autocpp-ffi](./skeleton/autocxx-ffi/): Generate bindings using autocxx.
- [ipc](./skeleton/ipc/): Communicate between languages by using sockets.  