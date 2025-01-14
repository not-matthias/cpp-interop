use ipc_example::Binary;
use ipc_example::{Action, ActionResponse, Genre, Movie};
use std::{
    io::{Read, Write},
    net::TcpStream,
};

fn read_response(stream: &mut TcpStream) -> Option<ActionResponse> {
    let mut buf = [0; 1024];
    let n = stream.read(&mut buf).unwrap();
    if n == 0 {
        return None;
    }

    bincode::deserialize(&buf[..n]).ok()
}

fn main() {
    let mut stream = TcpStream::connect("127.0.0.1:7878").unwrap();

    // The only other item of interest is that we can set TCP_NODELAY, which disables Nagle's algorithm. Generally TCP waits briefly to build a packet large enough to be worth sending. Given that we are looking for fast transmission, it makes sense to disable this. Benchmarks with and without this setting are given. Spoiler - it didn't seem to change anything.
    // stream.set_nodelay(true).unwrap();

    let action = Action::Add(Movie {
        title: "The Shawshank Redemption".to_string(),
        year: 1994,
        rating: 9.3,
        genre: Genre::Drama,
    });
    stream.write_all(&action.to_bytes()).unwrap();
    println!("{:?}", read_response(&mut stream));

    let action = Action::Get("The Shawshank Redemption".into());
    stream.write_all(&action.to_bytes()).unwrap();
    println!("{:?}", read_response(&mut stream));

    let action = Action::Remove("The Shawshank Redemption".into());
    stream.write_all(&action.to_bytes()).unwrap();
    println!("{:?}", read_response(&mut stream));

    let action = Action::Get("The Shawshank Redemption".into());
    stream.write_all(&action.to_bytes()).unwrap();
    println!("{:?}", read_response(&mut stream));

    // Store:
    // - i64/f64
    // - String
    // - Vec<i64>/[i64; 100]
    // - HashMap<String, i64>
    // - Custom struct/enum
    //
}
