#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "rust/cxx.h"

struct Movie;

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
  void for_each_movie(rust::Fn<void(const Movie &)> callback) const;

  // 5. Use rust::Vec
  void add_movies(const rust::Vec<Movie> movies);

private:
  std::vector<Movie> movies;
};

std::unique_ptr<MovieDatabase> create_movie_database();
