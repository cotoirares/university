//
// Created by Rares-Andrei Cotoi on 26.03.2024.
//

#include "repo.h"
#include "movie.h"

class Service{
private:
    Repo repo;
public:
    Service();
    Service(const Repo &repo);
    void addMovie(const std::string &title, const std::string &genre, int year, int likes, const std::string &trailer);
    void deleteMovie(const std::string &title);
    void updateMovie(const std::string &title, const std::string &genre, int year, int likes, const std::string &trailer);
    void increaseLikes(const std::string &title);
    int getSizeOfArray();
    Movie* getAllMovies();
    std::vector<Movie> create_watch_list();
};