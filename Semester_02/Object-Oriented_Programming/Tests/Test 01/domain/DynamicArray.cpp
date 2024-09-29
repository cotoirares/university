//
// Created by Rares-Andrei Cotoi on 01.04.2024.
//

#include "DynamicArray.h"

#include "domain.h"

typedef School TElem;

DynamicArray::DynamicArray(int capacity) {
    this->size = 0;
    this->capacity = capacity;
    this->elems = new TElem[capacity];
}

DynamicArray::DynamicArray(const DynamicArray& arr) {
    this->size = arr.size;
    this->capacity = arr.capacity;
    this->elems = new TElem[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->elems[i] = arr.elems[i];
}

DynamicArray::~DynamicArray() {
    delete[] this->elems;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& arr) {
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

void DynamicArray::resize(int factor) {
    this->capacity *= factor;

    TElem* els = new TElem[this->capacity];
    for (int i = 0; i < this->size; i++)
        els[i] = this->elems[i];

    delete[] this->elems;
    this->elems = els;
}

bool DynamicArray::delete_school(const std::string &name, float latitude, float longitude) {
    for (int i = 0; i < this->size; i++) /// checking for the school with the given name, latitude and longitude
        if ((this->elems[i].getName() == name) && (this->elems[i].getLatitude() == latitude) && (this->elems[i].getLongitude() == longitude)){
            for (int j = i; j < this->size - 1; j++)
                this->elems[j] = this->elems[j + 1]; /// deplasam elementele
            this->size--; ///scade lungimea
            return true; /// true daca s a sters scoala
        }
    return false; ///false daca nu exista scoala
}

void DynamicArray::add_school(const std::string &name, float latitude, float longitude, const std::string &date_to_visit, bool visited) {
    if (this->size == this->capacity)
        this->resize();
    this->elems[this->size++] = School(name, latitude, longitude, date_to_visit, visited);
}

int DynamicArray::getSize() const {
    return this->size;
}

School* DynamicArray::get_all_schools(){
    return this->elems;
}
