// Extension header for manual FFI. We need to define the functions manually so that they aren't mangled by the C++
// compiler.

#pragma once

#include "db.hpp"
#include <cstring>

extern "C"
{
    MovieDatabase *new_movie_database()
    {
        return new MovieDatabase();
    }

    void delete_movie_database(MovieDatabase *db)
    {
        delete db;
    }

    int32_t TOTAL_MOVIES_ADDED = 0;
    void add_movie(MovieDatabase *db, const Movie *movie)
    {
        TOTAL_MOVIES_ADDED++;
        db->add_movie(*movie);
    }

    void add_movie_via_params(MovieDatabase *db, const char *title, size_t title_len, uint16_t year, float rating,
                              Genre genre)
    {
        Movie movie;
        strncpy(movie.title, title, title_len);
        movie.title_len = title_len;
        movie.year = year;
        movie.rating = rating;
        movie.genre = genre;

        db->add_movie(movie);
    }

    bool remove_movie(MovieDatabase *db, const char *title)
    {
        return db->remove_movie(title);
    }

    const Movie *get_movie(MovieDatabase *db, const char *title)
    {
        return db->get_movie(title);
    }

    void for_each_movie(MovieDatabase *db, void (*callback)(const Movie &))
    {
        db->for_each_movie(callback);
    }
}
