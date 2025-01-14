# IPC

## Bindings for IPC

Generate the C++ deserialization code with `serde-generate`:
```bash
cd rust
cargo r --bin bindings
```

This will generate the `cpp/include/shared.hpp` file. The other files from the `include/` directory can be downloaded from the [`serde-generate` repository](https://github.com/zefchain/serde-reflection/tree/main/serde-generate/runtime/cpp).

## IPC types and libraries

Types of IPC:
- Socket
- Shared memory:
- Pipes
- ...

Libraries:
- [iceoryx2](https://crates.io/crates/iceoryx2)
- gRPC
- Protobuf
- Cap'n Proto
- [tarpc](https://github.com/google/tarpc)

Crates:
- [ipc-channel](https://crates.io/crates/ipc-channel)
- [shared_mem_queue](https://docs.rs/shared-mem-queue/0.4.0/shared_mem_queue/)
- [shared-memory](https://github.com/elast0ny/shared_memory)
