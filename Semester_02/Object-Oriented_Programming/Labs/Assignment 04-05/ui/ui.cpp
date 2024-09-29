//
// Created by Rares-Andrei Cotoi on 26.03.2024.
//

#include "ui.h"
#include "dynamic_array.h"
#include "movie.h"
#include "repo.h"
#include "service.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

void UI::general_menu() {
    cout << "1. Admin mode\n";
    cout << "2. User mode\n";
    cout << "0. Exit\n";
}

void UI::admin_menu(){
    cout<<"1. Add movie\n";
    cout<<"2. Remove movie\n";
    cout<<"3. Update movie\n";
    cout<<"4. Display all movies\n";
    cout<<"0. Exit\n";
}

void UI::user_menu(){
    cout<<"1. Display all movies with certain genre one by one\n";
    cout<<"2. See the watch list\n";
    cout<<"3. Delete or update a movie from the watch list\n";
    cout<<"0. Exit\n";
}

void UI::submenu_for_watchlist(){
    cout<<"1. Add movie to watch list\n";
    cout<<"2. Next\n";
    cout<<"0. Exit preview mode\n";
}

void UI::admin_mode(){
    int UserOption;
    while (true) {
        admin_menu();
        cin >> UserOption;
        if (UserOption == 0)
            return;
        if (UserOption == 1) {
            string title, genre, trailer, init_year, init_likes;
            int year, likes;
            cout << "Title: ";
            cin >> title;
            cout << "Genre: ";
            cin >> genre;
            while (true) {
                cout << "Year: ";
                cin >> init_year;
                std::istringstream iss(init_year);
                if (iss >> year && iss.eof()) {
                    break;
                } else {
                    std::cout << "Invalid input. Please enter an integer.\n";
                }
            }
            while (true) {
                cout << "Likes: ";
                cin >> init_likes;
                std::istringstream iss(init_likes);
                if (iss >> likes && iss.eof()) {
                    break;
                } else {
                    std::cout << "Invalid input. Please enter an integer.\n";
                }
            }
            cout << "Trailer: ";
            cin >> trailer;
            service.addMovie(title, genre, year, likes, trailer);
        }
        if (UserOption == 2) {
            string title;
            cout << "Title: ";
            cin >> title;
            service.deleteMovie(title);
        }
        if (UserOption == 3) {
            string title, genre, trailer, init_year, init_likes;
            int year, likes;
            cout << "Title: ";
            cin >> title;
            cout << "Updated Genre: ";
            cin >> genre;
            while (true) {
                cout << "Updated Year: ";
                cin >> init_year;
                std::istringstream iss(init_year);
                if (iss >> year && iss.eof()) {
                    break;
                } else {
                    std::cout << "Invalid input. Please enter an integer.\n";
                }
            }
            while (true) {
                cout << "Updated Likes: ";
                cin >> init_likes;
                std::istringstream iss(init_likes);
                if (iss >> likes && iss.eof()) {
                    break;
                } else {
                    std::cout << "Invalid input. Please enter an integer.\n";
                }
            }
            cout << "Updated Trailer: ";
            cin >> trailer;
            service.updateMovie(title, genre, year, likes, trailer);
        }
        if (UserOption == 4) {
            Movie *movies = service.getAllMovies();
            for (int i = 0; i < service.getSizeOfArray(); i++)
                cout <<"Title: "<< movies[i].getTitle() << " | Genre: " << movies[i].getGenre() << " | Year: " << movies[i].getYear() << " | Likes: "
                     << movies[i].getLikes() << " | Trailer: " << movies[i].getTrailer() << "\n";
        }
    }
}

void UI::user_mode() {
    int FirstOption;
    vector<Movie> watch_list = service.create_watch_list();
    while(true){
        user_menu();
        cout<<"Choose your option: ";
        cin>>FirstOption;
        if (FirstOption == 0)
            return;
        else{
             if (FirstOption == 1){
                string genre;
                cout<<"Genre: ";
                cin>>genre;
                int i = 0;
                while (i<service.getSizeOfArray()) {
                    if (service.getAllMovies()[i].getGenre() != genre)
                        i++;
                    else{
                        cout<<"Movie number "<<i+1<<":\n";
                        cout << "Title: " << service.getAllMovies()[i].getTitle() << " | Genre: "
                                 << service.getAllMovies()[i].getGenre() << " | Year: "
                                 << service.getAllMovies()[i].getYear() << " | Likes: "
                                 << service.getAllMovies()[i].getLikes() << " | Trailer: Played in browser\n";
                            string url = service.getAllMovies()[i].getTrailer();
                            string command = "open " + url;
                            system(command.c_str());
                        submenu_for_watchlist();
                        int SecondOption;
                        cout<<"Choose your option: ";
                        cin>>SecondOption;
                        if (SecondOption == 0)
                            break;
                        if (SecondOption == 1){
                            bool inList = false;
                            for (const auto& it: watch_list)
                                if (it.getTitle() == service.getAllMovies()[i].getTitle()){
                                    cout<<"Movie already in watch list!\n";
                                    inList = true;
                                }
                            if (!inList) {
                                watch_list.push_back(service.getAllMovies()[i]);
                                cout << "Movie added to watch list!\n";
                            }
                            cout<<"Showing the next movie...\n";
                            i++;
                        }
                        if (SecondOption == 2){
                            i++;
                        }
                        if (i == service.getSizeOfArray())
                            i = 0;
                    }
                }
            }
            if (FirstOption == 2){
                cout<<"Your current watch list:\n";
                for (const auto & i : watch_list)
                    cout <<"Title: "<< i.getTitle() << " | Genre: " << i.getGenre() << " | Year: " << i.getYear() << " | Likes: "
                         << i.getLikes() << " | Trailer: " << i.getTrailer() << "\n";
            }
            if (FirstOption == 3){
                string movie_title;
                bool validName = false;
                cout<<"Enter the movie title you have watched: ";
                cin>>movie_title;
                for (const auto& i: watch_list){
                    if (i.getTitle() == movie_title) {
                        validName = true;
                        cout<<"Found 1 movie with the title "<<movie_title<<".\n";
                        cout <<"Title: "<< i.getTitle() << " | Genre: " << i.getGenre() << " | Year: " << i.getYear() << " | Likes: "
                             << i.getLikes() << " | Trailer: " << i.getTrailer() << "\n";
                        cout<<"Would you also rate this movie with a like? (yes/no)\n";
                        string answer;
                        cin>>answer;
                        if (answer == "yes"){
                            service.increaseLikes(movie_title);
                            cout<<"Movie rated successfully!\n";
                        }
                        if (answer == "no")
                            cout<<"Movie not rated.\n";
                        for (int j = 0; j < watch_list.size(); j++)
                            if (watch_list[j].getTitle() == movie_title)
                                watch_list.erase(watch_list.begin() + j);
                        cout<<"Movie deleted successfully from the watch list!\n";
                    }
                }
                if (!validName) cout<<"The movie you entered is not in your watch list!\n";
            }
        }

    }
}

void UI::run() {
    int option;
    general_menu();
    cout<<"Select your option: ";
    cin >> option;
    if (option == 0)
        return;
    if (option == 1)
        admin_mode();
    if (option == 2)
        user_mode();
}

