//
// Created by Rares-Andrei Cotoi on 11.07.2024.
//

#include <iostream>
#include <cstring>
using namespace std;

class Event{
private:
    std::string organiser;
    std::string name;
    std::string description;
    std::string date;
    std::pair<double, double> location;
public:
    Event(std::string organiser, std::string name, std::string description, std::string date, std::pair<double, double> location){
        this->organiser = organiser;
        this->name = name;
        this->description = description;
        this->date = date;
        this->location = location;
    }
    std::string getOrganiser() const{
        return organiser;
    }
    std::string getName() const{
        return name;
    }
    std::string getDescription() const{
        return description;
    }
    std::string getDate() const{
        return date;
    }
    std::pair<double, double> getLocation() const{
        return location;
    }
    void setOrganiser(std::string organiser){
        this->organiser = organiser;
    }
    void setName(std::string name){
        this->name = name;
    }
    void setDescription(std::string description){
        this->description = description;
    }
    void setDate(std::string date){
        this->date = date;
    }
    void setLocation(std::pair<double, double> location) {
        this->location = location;
    }
    void print(){
        std::cout << "Event name: " << name << std::endl;
        std::cout << "Event organiser: " << organiser << std::endl;
        std::cout << "Event description: " << description << std::endl;
        std::cout << "Event date: " << date << std::endl;
        std::cout << "Event location: " << location.first << ", " << location.second << std::endl;
    }
};

class Person{
private:
    std::string name;
    std::pair<double, double> location;
    bool orgStatus; // convention: 0 if is not organiser, 1 if is organiser
public:
    Person(std::string name, std::pair<double, double> location, bool orgStatus){
        this->name = name;
        this->location = location;
        this->orgStatus = orgStatus;
    }
    std::string getName() const{
        return name;
    }
    std::pair<double, double> getLocation() const{
        return location;
    }
    bool getOrgStatus() const{
        return orgStatus;
    }
    void setName(std::string name) {
        this->name = name;
    }
    void setLocation(std::pair<double, double> location) {
        this->location = location;
    }
    void setOrgStatus(bool orgStatus){
        this->orgStatus = orgStatus;
    }
    void print(){
        std::cout << "Person name: " << name << std::endl;
        std::cout << "Person location: " << location.first << ", " << location.second << std::endl;
        if (orgStatus == 0){
            std::cout << "Organsier status: No" << std::endl;
        }
        else{
            std::cout << "Organiser status: Yes" << std::endl;
        }
    }
};

