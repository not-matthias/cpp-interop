use std::ffi::c_void;

// Manually converted C structs
//
#[derive(Debug)]
#[repr(C)]
pub enum Genre {
    Action,
    Comedy,
    Drama,
}

// #[derive(Debug)]
#[repr(C)]
pub struct Movie {
    title: [u8; 64],
    title_len: usize,

    year: u16,
    rating: f32,
    genre: Genre,
}
const _: () = {
    // ["Size of MovieDatabase"][::std::mem::size_of::<MovieDatabase>() - 24usize];
    // const { assert_eq!(core::mem::size_of::<Movie>(), 90) };
};

impl Movie {
    pub fn new(title: &str, year: u16, rating: f32, genre: Genre) -> Self {
        let mut title_bytes = [0; 64];
        title_bytes[..title.len()].copy_from_slice(title.as_bytes());
        let title_len = title.len();

        Movie {
            title: title_bytes,
            title_len,
            year,
            rating,
            genre,
        }
    }
}

// Better impl for C struct
impl std::fmt::Debug for Movie {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let title = std::str::from_utf8(&self.title[..self.title_len]).unwrap();
        write!(
            f,
            "Movie {{ title: {:?}, year: {}, rating: {}, genre: {:?} }}",
            title, self.year, self.rating, self.genre
        )
    }
}

// Manually imported C functions
//
#[link(name = "db", kind = "static")]
extern "C" {
    pub static mut TOTAL_MOVIES_ADDED: i32;

    pub fn new_movie_database() -> *mut c_void;
    pub fn delete_movie_database(db: *mut c_void);
    pub fn add_movie(db: *mut c_void, movie: *const Movie);
    pub fn add_movie_via_params(
        db: *mut c_void,
        title: *const u8,
        title_len: usize,
        year: u16,
        rating: f32,
        genre: Genre,
    );
    pub fn get_movie(db: *mut c_void, title: *const u8) -> *const Movie;
    pub fn remove_movie(db: *mut c_void, title: *const u8) -> bool;

    // void for_each_movie(MovieDatabase *db, void (*callback)(const Movie &))
    pub fn for_each_movie(db: *mut c_void, callback: extern "C" fn(*const Movie));

}

// extern "C" {

//   // #[link_name = "\u{1}_ZN7MyClass6methodEv"]
//   // pub fn MyClass_method(this: *mut MyClass);

//   extern "C" {
//       #[link_name = "\u{1}_ZN7MyClassC1Ev"]
//       pub fn MyClass_MyClass(this: *mut MyClass);
//   }
// }
