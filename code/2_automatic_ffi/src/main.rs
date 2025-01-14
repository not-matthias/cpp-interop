use bindgen_example::{Genre, Movie, MovieDatabase};

fn nts<const N: usize>(array: &[u8]) -> [i8; N] {
    let mut result = [0i8; N];
    for i in 0..array.len() {
        result[i] = array[i] as i8;
    }
    result
}

fn add_movies(db: &mut MovieDatabase) {
    let movies = [
        ("The Matrix", 1999, 8.7),
        ("The Matrix Reloaded", 2003, 7.2),
        ("The Matrix Revolutions", 2003, 6.8),
        ("The Matrix Resurrections", 2021, 5.8),
    ];

    for (title, year, rating) in movies.iter() {
        let title = nts::<64>(title.as_bytes());

        let movie = Movie {
            title,
            title_len: title.len() as _,
            year: *year,
            rating: *rating,
            genre: Genre::ACTION,
        };

        unsafe { db.add_movie(&movie) };
    }
}

extern "C" fn rust_callback(movie: *const Movie) {
    let movie = unsafe { &*movie };
    let name = unsafe { std::ffi::CStr::from_ptr(movie.title.as_ptr()) };
    println!(
        "Title: {:?}, Genre: {:?}, Year: {:?}, Rating: {:?}",
        name.to_str().unwrap(),
        movie.genre,
        movie.year,
        movie.rating
    );

    // Or alternatively:
    // println!("{:?}", movie);
}

fn main() {
    let mut db = MovieDatabase::default();

    add_movies(&mut db);
    unsafe { db.for_each_movie(Some(rust_callback)) };

    println!("After removing The Matrix:");
    unsafe { db.remove_movie("The Matrix\0".as_ptr() as _) };
    unsafe { db.for_each_movie(Some(rust_callback)) };

    let movie = unsafe { db.get_movie("The Matrix Reloaded\0".as_ptr() as _) };
    println!("The Matrix Reloaded: {:p}", movie);

    let movie = unsafe { db.get_movie("Unknown\0".as_ptr() as _) };
    println!("Unknown movie: {:p}", movie);
}
