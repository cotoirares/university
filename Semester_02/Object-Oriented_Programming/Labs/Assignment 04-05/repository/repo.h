
#pragma once

#include <iostream>
#include "../domain/dynamic_array.h"
#include "../domain/movie.h"

class Repo{
private:
    DynamicArray<Movie>* movies;
public:
    // default constructor for a Repo
    Repo();

    // destructor for a Repo
    ~Repo();

    // Adds an element to the current Repo.
    void add_movie(const Movie& e);

    // Updates an element from the current Repo.
    void update_movie(const Movie& e);

    void increaseLikes(const std::string &title);

    // Deletes an element from the current Repo.
    void delete_movie(const std::string& title);

    // Returns the size of the current Repo.
    int getSize();

    // Returns the element from a given position.
    Movie& get_certain_movie(int pos);
    // Returns all the elements from the current Repo.
    Movie* get_all_movies();

};
