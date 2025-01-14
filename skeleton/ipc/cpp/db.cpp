#include "db.hpp"

#include <algorithm>
#include <cstring>

void MovieDatabase::add_movie(const Movie &movie)
{
    movies.push_back(movie);
}

// returns true if the movie was removed, false otherwise
bool MovieDatabase::remove_movie(const char *title)
{
    const auto initial_size = movies.size();
    movies.erase(
        std::remove_if(movies.begin(), movies.end(), [title](const Movie &movie) { return movie.title == title; }),
        movies.end());

    return movies.size() < initial_size;
}

const Movie *MovieDatabase::get_movie(const char *title)
{
    for (const Movie &movie : movies)
    {
        if (movie.title == title)
        {
            return &movie;
        }
    }

    return nullptr;
}

void MovieDatabase::for_each_movie(void (*callback)(const Movie &))
{
    for (const Movie &movie : movies)
    {
        callback(movie);
    }
}

std::unique_ptr<MovieDatabase> create_movie_database()
{
    return std::make_unique<MovieDatabase>();
}
