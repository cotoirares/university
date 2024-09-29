//
// Created by Rares-Andrei Cotoi on 01.04.2024.
//

#pragma once

#include <iostream>
#include <string>
#include "domain.h"

class DynamicArray
{
private:
    int size;
    int capacity;
    School* elems;

public:
    // default constructor for a DynamicArray
    DynamicArray(int capacity = 20);

    // copy constructor for a DynamicArray
    DynamicArray(const DynamicArray& v);

    // destructor for a DynamicArray
    ~DynamicArray();

    // assignment operator for a DynamicArray
    DynamicArray& operator=(const DynamicArray& v);

    // Resizes the current DynamicArray, multiplying its capacity by a given factor.
    void resize(int factor = 2);

    // Deletes an element from the current DynamicArray.
    bool delete_school(const std::string& name, float latitude, float longitude);

    // Adds a school to the current DynamicArray.
    void add_school(const std::string& name, float latitude, float longitude, const std::string& date_to_visit, bool visited);

    // Returns the size of the current DynamicArray.
    int getSize() const;

    School* get_all_schools();
};
