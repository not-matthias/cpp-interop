#pragma once

#include <cstdint>
#include <memory>
#include <vector>

enum Genre
{
    ACTION,
    COMEDY,
    DRAMA
};

struct Movie
{
    char title[64];
    std::size_t title_len;

    uint16_t year;
    float rating;
    Genre genre;
};

class MovieDatabase
{
  public:
    MovieDatabase() = default;
    ~MovieDatabase() = default;

    void add_movie(const Movie &movie);
    bool remove_movie(const char *title);
    const Movie *get_movie(const char *title);
    void for_each_movie(void (*callback)(const Movie &));

  private:
    std::vector<Movie> movies;
};