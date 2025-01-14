use ffi::*;
use safe::*;

pub mod ffi;
pub mod safe;

fn ffi_test() {
    let db = unsafe { new_movie_database() };
    println!("Database: {:?}", db);

    let movie = unsafe { get_movie(db, b"Interstellar\0".as_ptr()) };
    println!("MoviePtr: {:?}", movie);

    {
        let movie = Movie::new("Interstellar", 2014, 8.6, Genre::Drama);
        unsafe { add_movie(db, &movie) };

        unsafe { add_movie_via_params(db, b"Inception\0".as_ptr(), 9, 2010, 8.8, Genre::Action) };

        let movie = unsafe { get_movie(db, b"Interstellar\0".as_ptr()) };
        println!("MoviePtr: {:?}", movie);
        println!("Movie: {:?}", unsafe { &*movie });

        // print each movie
        extern "C" fn rust_callback(movie: *const Movie) {
            let movie = unsafe { &*movie };
            println!("callback: {:?}", movie);
        }
        unsafe { for_each_movie(db, rust_callback as _) };

        unsafe { remove_movie(db, b"Interstellar\0".as_ptr()) };
        unsafe { remove_movie(db, b"Inception\0".as_ptr()) };
    }

    let movie = unsafe { get_movie(db, b"Interstellar\0".as_ptr()) };
    println!("MoviePtr: {:?}", movie);

    unsafe { delete_movie_database(db) };

    println!("We added {} movies", unsafe { ffi::TOTAL_MOVIES_ADDED });
}

fn safe_test() {
    let db = MovieDatabase::new();

    let movie = db.get_movie("Interstellar");
    println!("get before creation: {:?}", movie);

    {
        let movie = Movie::new("Interstellar", 2014, 8.6, Genre::Drama);
        db.add_movie(&movie);

        // db.add_movie_via_params("Interstellar", 2014, 8.6, Genre::Drama);

        let movie = db.get_movie("Interstellar");
        println!("Movie: {:?}", movie);

        db.remove_movie("Interstellar");
    }

    {
        let movie = Movie::new("Inception", 2010, 8.8, Genre::Action);
        db.add_movie(&movie);

        let movie = Movie::new("Interstellar", 2014, 8.6, Genre::Drama);
        db.add_movie(&movie);

        let movie = Movie::new("Dunkirk", 2017, 7.8, Genre::Action);
        db.add_movie(&movie);

        // print each movie
        extern "C" fn rust_callback(movie: *const Movie) {
            let movie = unsafe { &*movie };
            println!("rust_callback: {:?}", movie);
        }

        db.for_each_movie(rust_callback);
    }

    let movie = db.get_movie("Interstellar");
    println!("get after deletion: {:?}", movie);
}

fn main() {
    ffi_test();
    safe_test();
}
