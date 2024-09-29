//
// Created by Rares-Andrei Cotoi on 26.03.2024.
//

#include "service.h"
#include <vector>
#include <fstream>

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
    this->repo.increaseLikesCount(title);
}

std::vector<TElem> Service::getAllMovies(){
    return this->repo.get_all_movies();
}

int Service::getSizeOfArray() {
    return this->repo.getSize();
}
/*
 * The CSV file will contain each entity on one line and the attributes will be separated by comma
The HTML file will contain a table, in which each row holds the data of one entity. The columns of the table will contain the names of the data attributes.
 */
void Service::save_watch_list_csv(std::vector<Movie> watch_list) {
    std::ofstream file("/Users/rares/Desktop/facultate/OOP/oop-a6-7-cotoirares/watch_list.csv");
    for (auto & movie : watch_list) {
        file << movie.getTitle() << "," << movie.getGenre() << "," << movie.getYear() << "," << movie.getLikes() << "," << movie.getTrailer() << "\n";
    }
    file.close();
}

void Service::save_watch_list_html(std::vector<Movie> watch_list) {
    std::ofstream file("/Users/rares/Desktop/facultate/OOP/oop-a6-7-cotoirares/watch_list.html");
    file << "<!DOCTYPE html>\n";
    file << "<html>\n";
    file << "<head>\n";
    file << "<title>Watch List</title>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "<table border=\"1\">\n";
    file << "<tr>\n";
    file << "<td>Title</td>\n";
    file << "<td>Genre</td>\n";
    file << "<td>Year</td>\n";
    file << "<td>Likes</td>\n";
    file << "<td>Trailer</td>\n";
    file << "</tr>\n";
    for (auto &movie: watch_list) {
        file << "<tr>\n";
        file << "<td>" << movie.getTitle() << "</td>\n";
        file << "<td>" << movie.getGenre() << "</td>\n";
        file << "<td>" << movie.getYear() << "</td>\n";
        file << "<td>" << movie.getLikes() << "</td>\n";
        file << "<td>" << movie.getTrailer() << "</td>\n";
        file << "</tr>\n";
    }
    file << "</table>\n";
    file << "</body>\n";
    file << "</html>\n";
    file.close();
}

std::vector<Movie> Service::create_watch_list() {
    std::vector<Movie> watch_list;
    return watch_list;
}

