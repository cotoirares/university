//
// Created by Rares-Andrei Cotoi on 26.03.2024.
//

#include "repo.h"

typedef Movie TElem;

Repo::Repo() {
    movies = new DynamicArray<TElem>(20);
    Movie m1("Titanic", "Drama", 1997, 1000000, "https://www.imdb.com/title/tt0120338/");
    movies->add_movie(m1);
    Movie m2("Inception", "Action", 2010, 800000, "https://www.imdb.com/title/tt1375666/");
    movies->add_movie(m2);
    Movie m3("The Shawshank Redemption", "Drama", 1994, 900000, "https://www.imdb.com/title/tt0111161/");
    movies->add_movie(m3);
    Movie m4("The Godfather", "Crime", 1972, 950000, "https://www.imdb.com/title/tt0068646/");
    movies->add_movie(m4);
    Movie m5("The Dark Knight", "Action", 2008, 850000, "https://www.imdb.com/title/tt0468569/");
    movies->add_movie(m5);
    Movie m6("The Lord of the Rings: The Return of the King", "Adventure", 2003, 700000, "https://www.imdb.com/title/tt0167260/");
    movies->add_movie(m6);
    Movie m7("Pulp Fiction", "Crime", 1994, 950000, "https://www.imdb.com/title/tt0110912/");
    movies->add_movie(m7);
    Movie m8("The Lord of the Rings: The Fellowship of the Ring", "Adventure", 2001, 750000, "https://www.imdb.com/title/tt0120737/");
    movies->add_movie(m8);
    Movie m9("The Lord of the Rings: The Two Towers", "Adventure", 2002, 750000, "https://www.imdb.com/title/tt0167261/");
    movies->add_movie(m9);
    Movie m10("Forrest Gump", "Drama", 1994, 900000, "https://www.imdb.com/title/tt0109830/");
    movies->add_movie(m10);
    movies->resize(2);
}

Repo::~Repo() {
   // delete movies;
}

void Repo::add_movie(const Movie& e) {
    movies->add_movie(e);
}

void Repo::update_movie(const Movie& e) {
    movies->update_movie(e);
}

void Repo::delete_movie(const std::string& title) {
    movies->delete_movie(title);
}

void Repo::increaseLikes(const std::string &title){
    movies->increase_likes(title);
}


int Repo::getSize() {
    return movies->getSize();
}

Movie& Repo::get_certain_movie(int pos) {
    return movies->get_certain_movie(pos);
}

Movie* Repo::get_all_movies() {
    return movies->get_all_movies();
}
