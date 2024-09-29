//
// Created by Rares-Andrei Cotoi on 11.07.2024.
//

#pragma once
#include <iostream>
#include "domain.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "observer.h"
using namespace std;

class Repository{
private:
    std::vector<Event> events;
    std::vector<Person> persons;
    vector<pair<Event, Person>> participantsAtEvents;
public:
    Repository(){
        readEvents();
        readPersons();
    }
    // events are in the file events.txt
    void readEvents(){
        std::ifstream in("/Users/rares/Desktop/facultate/OOP/oop-e-retake-cotoirares/events.txt");
        std::string organiser, name, description, date, line;
        double x, y;
        while (getline(in, line)){
            std::istringstream iss(line);
            getline(iss, organiser, '|');
            getline(iss, name, '|');
            getline(iss, description, '|');
            getline(iss, date, '|');
            iss >> x;
            iss.ignore();
            iss >> y;
            events.emplace_back(organiser, name, description, date, std::make_pair(x, y));
        }
    }
    // persons are in persons.txt

    void readPersons(){
        std::ifstream fin("/Users/rares/Desktop/facultate/OOP/oop-e-retake-cotoirares/persons.txt");
        std::string name, line;
        double x, y;
        bool orgStatus;
        while (getline(fin, line)){
            std::istringstream iss(line);
            getline(iss, name, '|');
            iss >> x;
            iss.ignore();
            iss >> y;
            iss.ignore();
            iss >> orgStatus;
            persons.emplace_back(name, std::make_pair(x, y), orgStatus);
        }
    }

    void addEvent(string organiser, string name, string description, string date, pair<double, double> location){
        Event event(organiser, name, description, date, location); // creating an event object
        events.push_back(event);
    }
    void addPerson(string name, pair<double, double> location, bool orgStatus){
        Person person(name, location, orgStatus); // creating a person object
        persons.push_back(person);
    }

    std::vector<Event> getEvents(){
        return this->events;
    }
    std::vector<Person> getPersons(){
        return this->persons;
    }
    void saveFile(){ //method for task 9
        std::ofstream out("/Users/rares/Desktop/facultate/OOP/oop-e-retake-cotoirares/saved_events.txt");
        for(auto event : events){
            out << event.getOrganiser() << "|" << event.getName() << "|" << event.getDescription() << "|" << event.getDate() << "|" << event.getLocation().first << " " << event.getLocation().second << "|" <<"Attending persons: ";
            for (auto& it: participantsAtEvents)
                if (it.first.getName() == event.getName())
                    out << it.second.getName() << ", ";
            out << "\n";
        }
        out.close();
    }

    int getIndexEvent(Event event){ //get an event by its index
        int index = 0;
        for(auto e : events){
            if(e.getName() == event.getName() && e.getLocation() == event.getLocation()){
                return index;
            }
            index++;
        }
        return -1;
    }

    void updateEvent(string name, string description, string date, pair<double, double> location){
        for(auto& event : events){
            if(event.getName() == name){
                event.setDescription(description);
                event.setDate(date);
                event.setLocation(location);
            }
        }
    }
    void addParticipant(Event event, Person person){
        participantsAtEvents.push_back(make_pair(event, person));
    }
    vector<pair<Event, Person>> getParticipantsAtEvents(){
        return participantsAtEvents;
    }
    ~Repository(){
        saveFile();
    }
};