//
// Created by Rares-Andrei Cotoi on 01.04.2024.
//

#pragma once
#include <string>


class School{
private:
    std::string name;
    float latitude;
    float longitude;
    std::string date_to_visit;
    bool visited;

public:
    School();
    School(const std::string& address, float latitude, float longitude, const std::string& date_to_visit, bool visited);
    std::string getName() const;
    std::string getDateToVisit() const;
    float getLatitude() const;
    float getLongitude() const;
    bool checkIfVisited() const;

    void setName(const std::string& new_name);
    void setDateToVisit(const std::string& new_date_to_visit);
    void setLatitude(float new_latitude);
    void setLongitude(float new_longitude);
    void setVisited(bool new_visited);

    ~School();
};
