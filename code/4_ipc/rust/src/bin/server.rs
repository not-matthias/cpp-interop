use ipc_example::{Action, ActionResponse, Binary, Movie};
use std::{
    io::{Read, Write},
    net::{TcpListener, TcpStream},
    sync::{Arc, Mutex},
};

type State = Arc<Mutex<Vec<Movie>>>;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();

    let state: State = Arc::new(Mutex::new(Vec::new()));

    for stream in listener.incoming() {
        let stream = stream.unwrap();

        let _state = state.clone();
        std::thread::spawn(move || {
            handle_connection(stream, _state);
        });
    }
}

fn handle_action(action: Action, state: &State) -> ActionResponse {
    match action {
        Action::Add(movie) => {
            let mut state = state.lock().unwrap();
            state.push(movie);

            ActionResponse::Ok
        }
        Action::Get(title) => {
            let state = state.lock().unwrap();

            if let Some(movie) = state.iter().find(|m| m.title == title) {
                ActionResponse::Data(movie.clone())
            } else {
                ActionResponse::Error
            }
        }
        Action::Remove(name) => {
            let mut state = state.lock().unwrap();

            let prev_size = state.len();
            state.retain(|m| m.title != name);

            if state.len() < prev_size {
                ActionResponse::Ok
            } else {
                ActionResponse::Error
            }
        }
    }
}

fn handle_connection(mut stream: TcpStream, state: State) {
    loop {
        let mut buf = [0; 1024];
        match stream.read(&mut buf) {
            Ok(0) => break, // Connection closed
            Ok(n) => {
                let action: Action = bincode::deserialize(&buf[..n]).unwrap();
                println!("Received: {:?}", action);

                let response = handle_action(action, &state);
                stream.write_all(&response.to_bytes()).unwrap();
            }
            Err(error) => {
                println!("Error reading from stream: {}", error);
                break;
            }
        }
    }
}
