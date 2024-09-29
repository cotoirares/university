//
// Created by Rares-Andrei Cotoi on 01.04.2024.
//

#include <iostream>
#include "../domain/DynamicArray.h"
#include "../domain/domain.h"

class Repo{
private:
    DynamicArray* schools;
public:
    Repo();
    ~Repo();
    bool delete_school(const std::string& name, float latitude, float longitude);
    void add_school(const std::string& name, float latitude, float longitude, const std::string& date_to_visit, bool visited);
    School* get_all_schools();
    int get_size();
    School get_school(int index);
    //int find_school(const std::string& name, float latitude, float longitude);
};