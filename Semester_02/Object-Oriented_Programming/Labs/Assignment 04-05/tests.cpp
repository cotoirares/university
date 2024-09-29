//
// Created by Rares-Andrei Cotoi on 26.03.2024.
//

/// short tests for all non-UI functions

#include <assert.h>
#include <iostream>
#include "service.h"
#include "movie.h"
#include "repo.h"

/// tests for the Movie class

void test_movie() {
    Movie m1;
    assert(m1.getTitle() == "");
    assert(m1.getGenre() == "");
    assert(m1.getYear() == 0);
    assert(m1.getLikes() == 0);
    assert(m1.getTrailer() == "");

    Movie m2("title", "genre", 2000, 100, "trailer");
    assert(m2.getTitle() == "title");
    assert(m2.getGenre() == "genre");
    assert(m2.getYear() == 2000);
    assert(m2.getLikes() == 100);
    assert(m2.getTrailer() == "trailer");

    m1.setTitle("title");
    m1.setGenre("genre");
    m1.setYear(2000);
    m1.setLikes(100);
    m1.setTrailer("trailer");
    assert(m1.getTitle() == "title");
    assert(m1.getGenre() == "genre");
    assert(m1.getYear() == 2000);
    assert(m1.getLikes() == 100);
    assert(m1.getTrailer() == "trailer");
    std::cout<<"Movie tests passed!"<<std::endl;
}

/// tests for the Repo class

void test_repo() {
    Repo r;
    assert(r.getSize() == 10);

    Movie m1("title1", "genre1", 2000, 100, "trailer1");
    r.add_movie(m1);
    assert(r.getSize() == 11);

    Movie m2("title2", "genre2", 2001, 101, "trailer2");
    r.add_movie(m2);
    assert(r.getSize() == 12);

    r.delete_movie("title1");
    assert(r.getSize() == 11);

    Movie m3("title3", "genre3", 2002, 102, "trailer3");
    r.update_movie(m3);
    assert(r.getSize() == 11);

    r.increaseLikes("title2");
    assert(r.get_all_movies()[10].getLikes() == 102);
    assert(r.get_certain_movie(11).getTitle() == "title2");
    std::cout<<"Repo tests passed!"<<std::endl;
}

/// tests for the Service class

void test_service() {
    Repo r;
    Service s(r);
    assert(s.getSizeOfArray() == 10);

    s.addMovie("title1", "genre1", 2000, 100, "trailer1");
    assert(s.getSizeOfArray() == 11);

    s.deleteMovie("title1");
    assert(s.getSizeOfArray() == 10);

    s.addMovie("title2", "genre2", 2001, 101, "trailer2");
    s.updateMovie("title2", "genre3", 2002, 102, "trailer3");
    assert(s.getAllMovies()[10].getGenre() == "genre3");

    s.increaseLikes("title2");
    assert(s.getAllMovies()[10].getLikes() == 103);
    //test create watch list function
    std::vector<Movie> watch_list = s.create_watch_list();
    assert(watch_list.empty());
    std::cout<<"Service tests passed!"<<std::endl;
}

void testing_main() {
    test_movie();
    test_repo();
    test_service();
}