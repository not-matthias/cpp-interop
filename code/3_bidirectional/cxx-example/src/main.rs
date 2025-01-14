use cxx::let_cxx_string;

#[cxx::bridge]
mod ffi {
    // We can only define shared types in Rust and then generate the C++ impl with cxx. We can use C++ types in Rust, but they are opaque.
    //
    // See: https://cxx.rs/shared.html
    #[derive(Debug, Clone)]
    pub struct Movie {
        pub title: String,
        pub year: u16,
        pub rating: f32,
        pub genre: Genre,
    }

    #[derive(Debug, Copy, Clone)]
    pub enum Genre {
        Action,
        Comedy,
        Drama,
    }

    extern "Rust" {
        // ...
    }

    unsafe extern "C++" {
        include!("cxx-example/cpp/db.hpp");

        type MovieDatabase;
        fn create_movie_database() -> UniquePtr<MovieDatabase>;

        fn add_movie(self: Pin<&mut MovieDatabase>, movie: &Movie);
        fn remove_movie(self: Pin<&mut MovieDatabase>, title: &CxxString) -> bool;

        // CxxVector:
        fn get_movies(self: &MovieDatabase) -> &CxxVector<Movie>;

        // Result:
        fn get_movie(self: &MovieDatabase, title: &CxxString) -> Result<Movie>;

        // Callback:
        fn for_each_movie(self: &MovieDatabase, callback: fn(&Movie));

        // 5. Rust Vec
        fn add_movies(self: Pin<&mut MovieDatabase>, movies: &Vec<Movie>);
    }
}

fn main() {
    let mut db = ffi::create_movie_database();
    let movie = ffi::Movie {
        title: "Inception".to_string(),
        year: 2010,
        rating: 8.8,
        genre: ffi::Genre::Action,
    };

    {
        db.pin_mut().get_movies().iter().for_each(|movie| {
            println!("{:?}", movie);
        });

        db.pin_mut().add_movie(&movie);

        db.pin_mut().get_movies().iter().for_each(|movie| {
            println!("{:?}", movie);
        });
    }

    {
        let_cxx_string!(title = "Inception");
        let result = db.get_movie(&title);
        println!("{:?}", result);

        let_cxx_string!(title = "The Dark Knight");
        let result = db.get_movie(&title);
        println!("{:?}", result);
    }

    {
        db.pin_mut().for_each_movie(|movie| {
            println!("Rust callback: {}", movie.title);
        });
    }

    {
        let_cxx_string!(title = "Inception");
        let ret = db.pin_mut().remove_movie(&title);
        println!("Removal successful? {}", ret);
    }

    {
        let movies = vec![
            ffi::Movie {
                title: "Inception".to_string(),
                year: 2010,
                rating: 8.8,
                genre: ffi::Genre::Action,
            },
            ffi::Movie {
                title: "The Dark Knight".to_string(),
                year: 2008,
                rating: 9.0,
                genre: ffi::Genre::Action,
            },
        ];

        db.pin_mut().add_movies(&movies);

        db.pin_mut().get_movies().iter().for_each(|movie| {
            println!("{:?}", movie);
        });
    }
}
