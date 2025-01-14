use ipc_example::{Action, ActionResponse, Genre, Movie};
use serde_generate::CodeGeneratorConfig;
use serde_reflection::{Tracer, TracerConfig};

fn main() {
    let mut tracer = Tracer::new(TracerConfig::default());
    tracer.trace_simple_type::<Genre>().unwrap();
    tracer.trace_simple_type::<Movie>().unwrap();
    tracer.trace_simple_type::<Action>().unwrap();
    tracer.trace_simple_type::<ActionResponse>().unwrap();
    let registry = tracer.registry().unwrap();

    let config = CodeGeneratorConfig::new("ipc".to_string())
        .with_encodings(vec![serde_generate::Encoding::Bincode]);

    let mut source = Vec::new();
    let gen = serde_generate::cpp::CodeGenerator::new(&config);
    gen.output(&mut source, &registry).unwrap();

    std::fs::write("../cpp/include/shared.hpp", source).unwrap();
}
