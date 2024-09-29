//
// Created by Rares-Andrei Cotoi on 01.04.2024.
//

#include "service.h"

Service::Service() = default;

Service::~Service() {
    delete[] this->repo.get_all_schools();
}

void Service::add_school(const std::string &name, float latitude, float longitude, const std::string &date_to_visit, bool visited) {
    this->repo.add_school(name, latitude, longitude, date_to_visit, visited);
}

bool Service::delete_school(const std::string &name, float latitude, float longitude) {
    return this->repo.delete_school(name, latitude, longitude);
}

School* Service::get_all_schools() {
    return this->repo.get_all_schools();
}

School* Service::get_all_schools_sorted() {
    School* schools = this->repo.get_all_schools();
    int size = this->repo.get_size();
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (schools[i].getName() > schools[j].getName()) {
                School aux = schools[i];
                schools[i] = schools[j];
                schools[j] = aux;
            }
        }
    }
    return schools;
}

School* Service::mark_as_visited_by_date(const std::string &date) {
    School* schools_left_to_visit = new School[this->repo.get_size()]; /// array nou pt scolile ramase nevizitate
    int size = this->repo.get_size();
    for (int i = 0; i < size; i++) {
        if (schools_left_to_visit[i].getDateToVisit() > date) {
            schools_left_to_visit[i] = this->repo.get_school(i); /// daca nu e inainte de data d, o punem in vector
        }
        else {
            this->repo.get_school(i).setVisited(true);/// daca e inainte de data d, marcam visited cu 1
        }
    }
    return schools_left_to_visit;
}

int Service::get_size() {
    return this->repo.get_size();
}

School Service::get_school(int index) {
    return this->repo.get_school(index);
}

