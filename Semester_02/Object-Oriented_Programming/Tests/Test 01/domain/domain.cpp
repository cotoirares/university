//
// Created by Rares-Andrei Cotoi on 01.04.2024.
//

#include "domain.h"


School::School() {
    this->name = "";
    this->latitude = 0;
    this->longitude = 0;
    this->date_to_visit = "";
    this->visited = false;
}

School::School(const std::string& name, float latitude, float longitude, const std::string& date_to_visit, bool visited) {
    this->name = name;
    this->latitude = latitude;
    this->longitude = longitude;
    this->date_to_visit = date_to_visit;
    this->visited = visited;
}


std::string School::getName() const {
    return this->name;
}

std::string School::getDateToVisit() const {
    return this->date_to_visit;
}

float School::getLatitude() const {
    return this->latitude;
}

float School::getLongitude() const {
    return this->longitude;
}

bool School::checkIfVisited() const {
    return this->visited;
}

void School::setName(const std::string &new_name) {
    this->name = new_name;
}

void School::setDateToVisit(const std::string &new_date_to_visit) {
    this->date_to_visit = new_date_to_visit;
}

void School::setLatitude(float new_latitude) {
    this->latitude = new_latitude;
}

void School::setLongitude(float new_longitude) {
    this->longitude = new_longitude;
}

void School::setVisited(bool new_visited) {
    this->visited = new_visited;
}

School::~School() = default;
