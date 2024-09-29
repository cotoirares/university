//
// Created by Rares-Andrei Cotoi on 26.03.2024.
//

#include "movie.h"

Movie::Movie() {
    this->title = "";
    this->genre = "";
    this->year = 0;
    this->likes = 0;
    this->trailer = "";
}

Movie::Movie(const std::string &title, const std::string &genre, int year, int likes, const std::string &trailer) {
    this->title = title;
    this->genre = genre;
    this->year = year;
    this->likes = likes;
    this->trailer = trailer;
}

std::string Movie::getTitle() const {
    return this->title;
}

std::string Movie::getGenre() const {
    return this->genre;
}

int Movie::getYear() const {
    return this->year;
}

int Movie::getLikes() const {
    return this->likes;
}

std::string Movie::getTrailer() const {
    return this->trailer;
}

void Movie::setTitle(const std::string &title) {
    this->title = title;
}

void Movie::setGenre(const std::string &genre) {
    this->genre = genre;
}

void Movie::setYear(int year) {
    this->year = year;
}

void Movie::setLikes(int likes) {
    this->likes = likes;
}

void Movie::setTrailer(const std::string &trailer) {
    this->trailer = trailer;
}

Movie::~Movie() = default;


