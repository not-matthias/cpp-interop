use rust::{Action, ActionResponse, Genre, Movie};
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
    // TODO: Connect to the server and send requests
}
