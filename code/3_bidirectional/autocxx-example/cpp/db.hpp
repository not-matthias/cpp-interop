#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "cxx.h"

enum Genre
{
    ACTION,
    COMEDY,
    DRAMA
};

struct Movie
{
    // Error: the include_cpp! macro couldn't be expanded into Rust bindings to C++: An item was requested using
    // 'generate_pod' which was not safe to hold by value in Rust. Type Movie could not be POD because its dependent
    // type std::string isn't safe to be POD. Because: type std::string is not safe for POD std::string title;

    char title[64];
    size_t title_len;

    uint16_t year;
    float rating;
    Genre genre;
};

class MovieDatabase
{
  public:
    // 1. Simple functions:
    void add_movie(const Movie &movie);
    bool remove_movie(const std::string &title);

    // 2. Return CxxVector
    const std::vector<Movie> &get_movies() const;

    // 3. Return Result<Movie>
    Movie get_movie(const std::string &title) const;

    // 4. Callback:
    // https://cxx.rs/binding/box.html
    // void for_each_movie(void (*callback)(const Movie &)) const;
    void for_each_movie(rust::Fn<void(const Movie &)> callback) const;

    // // 5. Use rust::Vec
    void add_movies(const rust::Slice<const Movie> movies);

  private:
    std::vector<Movie> movies;
};

std::unique_ptr<MovieDatabase> create_movie_database();
