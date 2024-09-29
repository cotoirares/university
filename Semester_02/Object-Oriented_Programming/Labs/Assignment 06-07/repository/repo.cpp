//
// Created by Rares-Andrei Cotoi on 26.03.2024.
//

#include "repo.h"
#include <fstream>
#include <sstream>

typedef Movie TElem;

Repo::Repo() {
    movies = new DynamicArray<Movie>();
    std::ifstream file("/Users/rares/Desktop/facultate/OOP/oop-a6-7-cotoirares/repository/repo.txt");
    std::string title;
    std::string genre;
    int year;
    int likes;
    std::string trailer;
    while (file >> title >> genre >> year >> likes >> trailer){
        Movie m(title, genre, year, likes, trailer);
        movies->add_movie(m);
    }
    file.close();
}

Repo::~Repo() {
   // delete movies;
}

void Repo::read_from_file() {
    std::ifstream file("/Users/rares/Desktop/facultate/OOP/oop-a6-7-cotoirares/repository/repo.txt");
    std::string title;
    std::string genre;
    int year;
    int likes;
    std::string trailer;
    while (file>>title>>genre>>year>>likes>>trailer){
        Movie m(title, genre, year, likes, trailer);
        movies->add_movie(m);
    }
    file.close();
}

void Repo::write_to_file() {
    std::ofstream file("/Users/rares/Desktop/facultate/OOP/oop-a6-7-cotoirares/repository/repo.txt");
    std::vector<Movie> all_movies = movies->get_all_movies();
    for (auto & all_movie : all_movies) {
        file << all_movie.getTitle() << " " << all_movie.getGenre() << " " << all_movie.getYear() << " " << all_movie.getLikes() << " " << all_movie.getTrailer() << "\n";
    }
    file.close();
}

void Repo::add_movie(const Movie& e) {
    read_from_file();
    movies->add_movie(e);
    write_to_file();
}

void Repo::update_movie(const Movie& e) {
    read_from_file();
    movies->update_movie(e);
    write_to_file();
}

void Repo::delete_movie(const std::string& title) {
    read_from_file();
    movies->delete_movie(title);
    write_to_file();
}

void Repo::increaseLikesCount(const std::string &title){
    read_from_file();
    movies->increase_likes(title);
    write_to_file();
}


int Repo::getSize() {
    return movies->getSize();
}

Movie& Repo::get_certain_movie(int pos) {
    return movies->get_certain_movie(pos);
}

std::vector<TElem> Repo::get_all_movies() {
    return movies->get_all_movies();
}
