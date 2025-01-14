use crate::ffi::*;

pub struct MovieDatabase {
    ptr: *mut std::ffi::c_void,
}

impl MovieDatabase {
    pub fn new() -> Self {
        let ptr = unsafe { new_movie_database() };
        MovieDatabase { ptr }
    }

    pub fn add_movie(&self, movie: &Movie) {
        unsafe { add_movie(self.ptr, movie) };
    }

    pub fn add_movie_via_params(&self, title: &str, year: u16, rating: f32, genre: Genre) {
        let ctitle = std::ffi::CString::new(title).unwrap();

        unsafe {
            add_movie_via_params(
                self.ptr,
                ctitle.as_ptr() as _,
                title.len(),
                year,
                rating,
                genre,
            )
        };
    }

    pub fn get_movie(&self, title: &str) -> Option<&Movie> {
        let ctitle = std::ffi::CString::new(title).unwrap();

        let movie_ptr = unsafe { get_movie(self.ptr, ctitle.as_ptr() as _) };
        if movie_ptr.is_null() {
            None
        } else {
            Some(unsafe { &*movie_ptr })
        }
    }

    pub fn remove_movie(&self, title: &str) -> bool {
        let ctitle = std::ffi::CString::new(title).unwrap();

        unsafe { remove_movie(self.ptr, ctitle.as_ptr() as _) }
    }

    /// Rust closures are not compatible with C function pointers: https://stackoverflow.com/a/32270215
    pub fn for_each_movie(&self, callback: extern "C" fn(*const Movie)) {
        unsafe { for_each_movie(self.ptr, callback) };
    }
}

impl Drop for MovieDatabase {
    fn drop(&mut self) {
        unsafe { delete_movie_database(self.ptr) };
    }
}
