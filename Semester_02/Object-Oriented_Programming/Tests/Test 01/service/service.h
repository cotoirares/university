//
// Created by Rares-Andrei Cotoi on 01.04.2024.
//


#include "repo.h"
#include "domain.h"

class Service{
private:
    Repo repo;
public:
    Service();
    ~Service();
    void add_school(const std::string& name, float latitude, float longitude, const std::string& date_to_visit, bool visited);
    bool delete_school(const std::string& name, float latitude, float longitude);
    School* get_all_schools();
    School* get_all_schools_sorted();
    int get_size();
    School get_school(int index);
    School* mark_as_visited_by_date(const std::string& date);
    //int find_school(const std::string& name, float latitude, float longitude);
};

