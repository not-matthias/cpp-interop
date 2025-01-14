#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "include/shared.hpp" // Contains the Movie struct
using Movie = ipc::Movie;

class MovieDatabase
{
  public:
    MovieDatabase() = default;
    ~MovieDatabase() = default;

    void add_movie(const Movie &movie);
    bool remove_movie(const char *title);

    // - Error Handling (Exceptions, Result, Option, etc.)
    const Movie *get_movie(const char *title);

    // - Callbacks und Function Pointers
    void for_each_movie(void (*callback)(const Movie &));

  private:
    std::vector<Movie> movies;
};

std::unique_ptr<MovieDatabase> create_movie_database();
