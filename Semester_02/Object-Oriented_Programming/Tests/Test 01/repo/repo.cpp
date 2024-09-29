//
// Created by Rares-Andrei Cotoi on 01.04.2024.
//

#include "repo.h"


Repo::Repo() {
    schools = new DynamicArray();
    this->schools->add_school("Avram_Iancu", 46.77, 23.60, "2023.04.15", true);
    this->schools->add_school("George_Cosbuc", 46.77, 23.58, "2023.04.08", false);
    this->schools->add_school("Alexandru_Vaida_Voievod", 46.77, 23.63, "2023.04.23", false);
    this->schools->add_school("Romulus_Guga", 46.53, 24.57, "2023.05.04", false);
    this->schools->add_school("Colegiul_Transilvania", 46.54, 24.57, "2023.05.03", false);
}

Repo::~Repo() {
    delete[] this->schools->get_all_schools();
}

void Repo::add_school(const std::string &name, float latitude, float longitude, const std::string &date_to_visit, bool visited) {
    this->schools->add_school(name, latitude, longitude, date_to_visit, visited);
}

bool Repo::delete_school(const std::string &name, float latitude, float longitude) {
    return this->schools->delete_school(name, latitude, longitude);
}

School* Repo::get_all_schools() {
    return this->schools->get_all_schools();
}

int Repo::get_size() {
    return this->schools->getSize();
}

School Repo::get_school(int index) {
    return this->schools->get_all_schools()[index];
}

