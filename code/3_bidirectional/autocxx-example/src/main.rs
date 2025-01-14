// Use all the autocxx types which might be handy.
use autocxx::extern_rust::extern_rust_type;
use autocxx::prelude::*;
use cxx::let_cxx_string;

pub fn nts<const N: usize>(array: &[u8]) -> [i8; N] {
    let mut result = [0i8; N];
    for i in 0..array.len() {
        result[i] = array[i] as i8;
    }
    result
}

#[extern_rust_type]
#[derive(Debug, Copy, Clone)]
pub struct RustStruct {
    pub x: i32,
    pub y: i32,
}

include_cpp! {
    #include "db.hpp"

    // This removes the need of using `unsafe` when calling FFI functions
    // Note: Generated C++ APIs which use raw pointers remain unsafe no matter
    // what policy you choose.
    //
    // see: https://docs.rs/autocxx/latest/autocxx/macro.safety.html
    safety!(unsafe)

    // extern_rust_type!(RustGenre)

    // Generate Rust bindings for the given C++ type such that it can be passed and owned by value in Rust. 
    // This only works for C++ types which have trivial move constructors 
    // and no destructor - you’ll encounter a compile error otherwise.
    generate_pod!("Movie")

    // allowlist a type and all its methods
    generate!("MovieDatabase")

    // Block certain types:
    // block!("dont_generate_this_type")
}

// Create manual bindings for the failed bindings:
// https://cxx.rs/extern-c++.html#integrating-with-bindgen-generated-or-handwritten-unsafe-bindings
#[cxx::bridge]
mod cxxffi {
    unsafe extern "C++" {
        include!("db.hpp");

        type Movie = crate::ffi::Movie;
        type MovieDatabase = crate::ffi::MovieDatabase;

        // Redefine the name as it already exists using the `rust_name` attribute
        // See: https://cxx.rs/attributes.html

        // Callback:
        #[rust_name = "for_each_movie1"]
        fn for_each_movie(self: &MovieDatabase, callback: fn(&Movie));

        // Rust Vec
        #[rust_name = "add_movies1"]
        fn add_movies(self: Pin<&mut MovieDatabase>, movies: &[Movie]);
    }
}

impl ffi::Movie {
    pub fn new(title: &str, year: u16, rating: f32, genre: ffi::Genre) -> Self {
        let title = nts::<64>(title.as_bytes());

        Self {
            title,
            title_len: title.len(),
            year,
            rating,
            genre,
        }
    }
}

impl core::fmt::Debug for ffi::Genre {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        let genre = match self {
            ffi::Genre::ACTION => "ACTION",
            ffi::Genre::COMEDY => "COMEDY",
            ffi::Genre::DRAMA => "DRAMA",
        };

        write!(f, "{}", genre)
    }
}

impl core::fmt::Debug for ffi::Movie {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        let title = unsafe { std::ffi::CStr::from_ptr(self.title.as_ptr()) };
        f.debug_struct("Movie")
            .field("title", &title)
            .field("year", &self.year)
            .field("rating", &self.rating)
            .field("genre", &self.genre)
            .finish()
    }
}

fn main() {
     // Stack-allocated db
     moveit! {
        let _db = ffi::MovieDatabase::new();
    };

    // Heap-allocated Rust
    let _db = ffi::MovieDatabase::new().within_box();

    // Heap-allocated C++
    let mut db = ffi::MovieDatabase::new().within_unique_ptr();

    let movies = [
        ("The Matrix", 1999, 8.7),
        ("The Matrix Reloaded", 2003, 7.2),
        ("The Matrix Revolutions", 2003, 6.8),
        ("The Matrix Resurrections", 2021, 5.8),
    ];

    movies.iter().for_each(|(title, year, rating)| {
        let movie = ffi::Movie::new(title, *year, *rating, ffi::Genre::ACTION);
        db.pin_mut().add_movie(&movie);
    });

    db.pin_mut().get_movies().iter().for_each(|movie| {
        println!("{:?}", movie);
    });

    let_cxx_string!(title = "The Matrix");
    let movie = db.get_movie(&title);
    println!("Found movie: {:?}", movie);

    let_cxx_string!(title = "The Matrix Reloaded");
    let ret = db.pin_mut().remove_movie(&title);
    println!("Removed movie: {:?}", ret);

    let movies = vec![
        ffi::Movie::new("Inception", 2010, 8.8, ffi::Genre::ACTION),
        ffi::Movie::new("Interstellar", 2014, 8.6, ffi::Genre::DRAMA),
    ];
    db.pin_mut().add_movies1(&movies);

    db.for_each_movie1(|movie| {
        println!("Rust callback with cxx: {:?}", movie);
    });
}
