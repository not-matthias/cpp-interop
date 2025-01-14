#include <algorithm>
#include <stdexcept>

#include "cxxgen.h"
#include "db.hpp"

void MovieDatabase::add_movie(const Movie &movie)
{
    movies.push_back(movie);
}

// returns true if the movie was removed, false otherwise
bool MovieDatabase::remove_movie(const std::string &title)
{
    const auto initial_size = movies.size();
    movies.erase(
        std::remove_if(movies.begin(), movies.end(), [title](const Movie &movie)
                       { return movie.title == title; }),
        movies.end());

    return movies.size() < initial_size;
}

Movie MovieDatabase::get_movie(const std::string &title) const
{
    for (const Movie &movie : movies)
    {
        if (movie.title == title)
        {
            return movie;
        }
    }

    throw std::runtime_error("Movie not found");
}

const std::vector<Movie> &MovieDatabase::get_movies() const
{
    return movies;
}

void MovieDatabase::for_each_movie(rust::Fn<void(const Movie &)> callback) const
{
    for (const Movie &movie : movies)
    {
        callback(movie);
    }
}

void MovieDatabase::add_movies(const rust::Vec<Movie> movies)
{
    for (const Movie &movie : movies)
    {
        this->movies.push_back(movie);
    }
}
