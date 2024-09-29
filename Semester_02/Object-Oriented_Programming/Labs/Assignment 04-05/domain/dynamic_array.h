//
// Created by Rares-Andrei Cotoi on 26.03.2024.
//

#pragma once

#include <iostream>
#include <string>
#include "movie.h"

template <typename TElem> class DynamicArray{
private:
    int size{};
    int capacity{};
    TElem* elems;

public:
    // default constructor for a DynamicArray
    DynamicArray(int capacity) {
        this->size = 0;
        this->capacity = capacity;
        this->elems = new TElem[capacity];
    }

    // copy constructor for a DynamicArray
    DynamicArray(const DynamicArray& arr) {
        this->size = arr.size;
        this->capacity = arr.capacity;
        this->elems = new TElem[this->capacity];
        for (int i = 0; i < this->size; i++)
            this->elems[i] = arr.elems[i];
    }

    // destructor for a DynamicArray
    ~DynamicArray() {
        delete[] this->elems;
    }

    // assignment operator for a DynamicArray
    DynamicArray& operator=(const DynamicArray& arr) {
        if (this == &arr)
            return *this;

        this->size = arr.size;
        this->capacity = arr.capacity;

        delete[] this->elems;
        this->elems = new TElem[this->capacity];
        for (int i = 0; i < this->size; i++)
            this->elems[i] = arr.elems[i];

        return *this;
    }

    // Resizes the current DynamicArray, multiplying its capacity by a given factor.
    void resize(int factor) {
        this->capacity *= factor;

        TElem* els = new TElem[this->capacity];
        for (int i = 0; i < this->size; i++)
            els[i] = this->elems[i];

        delete[] this->elems;
        this->elems = els;
    }

    // Adds an element to the current DynamicArray.
    void add_movie(const TElem &e){
        for (int i = 0; i < this->size; i++)
            if (this->elems[i].getTitle() == e.getTitle()) {
                std::cout << "Movie already exists!" << std::endl;
                return;
            }

        if (this->size == this->capacity)
            this->resize(2);

        this->elems[this->size++] = e;
        std::cout<<"Movie added successfully!"<<std::endl;
    }

    // Updates an element from the current DynamicArray.
    void update_movie(const TElem &e) {
        bool ok = false;
        for (int i = 0; i < this->size; i++)
            if (this->elems[i].getTitle() == e.getTitle()) {
                ok = true;
                this->elems[i] = e;
            }
        if (!ok)
            std::cout<<"Movie does not exist!"<<std::endl;
        else std::cout<<"Movie updated successfully!"<<std::endl;
    }

    // Deletes an element from the current DynamicArray.
    void delete_movie(const std::string &title) {
        bool ok = false;
        for (int i = 0; i < this->size; i++)
            if (this->elems[i].getTitle() == title) {
                ok = true;
                for (int j = i; j < this->size - 1; j++)
                    this->elems[j] = this->elems[j + 1];
                this->size--;
                break;
            }
        if (!ok)
            std::cout<<"Movie does not exist!"<<std::endl;
        else std::cout<<"Movie deleted successfully!"<<std::endl;
    }

    void increase_likes(const std::string &title) {
        bool ok = false;
        for (int i = 0; i < this->size; i++)
            if (this->elems[i].getTitle() == title) {
                ok = true;
                this->elems[i].setLikes(this->elems[i].getLikes() + 1);
            }
        if (!ok)
            std::cout<<"Movie does not exist!"<<std::endl;
        else std::cout<<"Likes increased successfully!"<<std::endl;
    }

    // Returns the size of the current DynamicArray.
    int getSize() const {
        return this->size;
    }

    // Returns the element from a given position.
    TElem& get_certain_movie(int pos) {
        return this->elems[pos];
    }

    TElem* get_all_movies(){
        return this->elems;
    }
};
