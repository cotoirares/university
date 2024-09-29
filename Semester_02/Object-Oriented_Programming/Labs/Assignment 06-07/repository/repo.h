
#pragma once

#include <iostream>
#include "../domain/dynamic_array.h"
#include "../domain/movie.h"
typedef Movie TElem;
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

    void read_from_file();

    void write_to_file();

    // Updates an element from the current Repo.
    void update_movie(const Movie& e);

    void increaseLikesCount(const std::string &title);

    // Deletes an element from the current Repo.
    void delete_movie(const std::string& title);

    // Returns the size of the current Repo.
    int getSize();

    // Returns the element from a given position.
    Movie& get_certain_movie(int pos);
    // Returns all the elements from the current Repo.
    std::vector<TElem> get_all_movies();

};
