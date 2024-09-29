
#pragma once
#include <string>

class Movie{
private:
    std::string title;
    std::string genre;
    int year;
    int likes;
    std::string trailer;

public:
    Movie();
    Movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);

    std::string getTitle() const;
    std::string getGenre() const;
    int getYear() const;
    int getLikes() const;
    std::string getTrailer() const;

    void setTitle(const std::string& title);
    void setGenre(const std::string& genre);
    void setYear(int year);
    void setLikes(int likes);
    void setTrailer(const std::string& trailer);
    bool operator==(const Movie& other) const {
        return this->title == other.title && this->genre == other.genre && this->year == other.year && this->likes == other.likes && this->trailer == other.trailer;
    }
    void increaseLikes() {
        this->likes++;
    }
    ~Movie();
};
