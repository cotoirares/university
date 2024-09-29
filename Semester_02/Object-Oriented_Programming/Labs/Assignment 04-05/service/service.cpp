//
// Created by Rares-Andrei Cotoi on 26.03.2024.
//

#include "service.h"
#include <vector>

Service::Service() = default;

Service::Service(const Repo &repo) {
    this->repo = repo;
}

void Service::addMovie(const std::string &title, const std::string &genre, int year, int likes, const std::string &trailer) {
    Movie movie = Movie(title, genre, year, likes, trailer);
    this->repo.add_movie(movie);
}

void Service::deleteMovie(const std::string &title) {
    this->repo.delete_movie(title);
}

void Service::updateMovie(const std::string &title, const std::string &genre, int year, int likes, const std::string &trailer) {
    Movie movie = Movie(title, genre, year, likes, trailer);
    this->repo.update_movie(movie);
}

void Service::increaseLikes(const std::string &title) {
    this->repo.increaseLikes(title);
}

Movie* Service::getAllMovies(){
    return this->repo.get_all_movies();
}

int Service::getSizeOfArray() {
    return this->repo.getSize();
}

std::vector<Movie> Service::create_watch_list() {
    std::vector<Movie> watch_list;
    return watch_list;
}

