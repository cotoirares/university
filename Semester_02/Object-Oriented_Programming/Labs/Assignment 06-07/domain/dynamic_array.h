//
// Created by Rares-Andrei Cotoi on 26.03.2024.
//

#pragma once

#include <iostream>
#include <string>
#include "movie.h"
#include <vector>
#include <algorithm>

template <typename TElem> class DynamicArray{
private:
    std::vector<TElem> elems;

public:
    // default constructor for the vector
    DynamicArray() {
        this->elems = std::vector<TElem>();
    }

    // copy constructor for a DynamicArray
    DynamicArray(const DynamicArray& arr) {
        this->elems = arr.elems;
    }

    // destructor for a DynamicArray
    ~DynamicArray() {
        this->elems.clear();
    }

    // assignment operator for a DynamicArray
    DynamicArray& operator=(const DynamicArray& arr) {
        this->elems = arr.elems;
        return *this;
    }


    // Add movie to the current DynamicArray if it does not exist. Check its presence without using the for loop, only with STL algorithms.
    void add_movie(const TElem &e){
        if (std::find(this->elems.begin(), this->elems.end(), e) != this->elems.end()) {
            throw std::exception();
        } else {
            this->elems.push_back(e);
            std::cout << "Movie added successfully!" << std::endl;
        }
    }

    // Updates an element from the current DynamicArray. Check its presence without using the for loop, only with STL algorithms.
    void update_movie(const TElem &e) {
        // search for the movie, if it is not in the array, then print a message
        std::string title = e.getTitle();
        auto it = std::find_if(this->elems.begin(), this->elems.end(), [title](const TElem& e) { return e.getTitle() == title; });
        if (it != this->elems.end()) {
            int index = std::distance(this->elems.begin(), it);
            this->elems[index] = e;
            std::cout << "Movie updated successfully!" << std::endl;
        }
        else
            throw std::exception();
    }

    // Deletes an element from the current DynamicArray.
    void delete_movie(const std::string &title) {
        // search in the vector without the for loop
        auto it = std::find_if(this->elems.begin(), this->elems.end(), [title](const TElem& e) { return e.getTitle() == title; });
        if (it != this->elems.end()) {
            this->elems.erase(std::distance(this->elems.begin(), it) + this->elems.begin());
            std::cout << "Movie deleted successfully!" << std::endl;
        }
        else
            throw std::exception();
    }

    void increase_likes(const std::string &title) {
        // search in the vector without the for loop
        auto it = std::find_if(this->elems.begin(), this->elems.end(), [title](const TElem& e) { return e.getTitle() == title; });
        if (it != this->elems.end()) {
            it->increaseLikes();
            std::cout << "Likes increased successfully!" << std::endl;
        }
        else
            throw std::exception();
    }

    // Returns the size of the current DynamicArray.
    int getSize() const {
        return this->elems.size();
    }

    // Returns the element from a given position.
    TElem& get_certain_movie(int pos) {
        return this->elems[pos];
    }

    std::vector<TElem> get_all_movies(){
        return this->elems;
    }
};
