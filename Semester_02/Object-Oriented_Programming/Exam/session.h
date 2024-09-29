//
// Created by Rares-Andrei Cotoi on 11.07.2024.
//
#pragma once

#include "repository.h"
#include "subject.h"
#include <algorithm>
#include <fstream>

class Session : public Subject {
private:
    Repository &repository;
public:
    Session(Repository &repository) : repository(repository) {};
    ~Session() = default;
    void addEvent(string organiser, string name, string description, string date, pair<double, double> location){
        if (organiser.empty() || name.empty() || description.empty() || date.empty())
            throw std::invalid_argument("Invalid input!");
        if (repository.getIndexEvent(Event(organiser, name, description, date, location)) != -1)
            throw std::invalid_argument("Event is already in the list!");
        repository.addEvent(organiser, name, description, date, location);
        notify();
    }

    void addParticipant(const Event& event, const Person& person){
        repository.addParticipant(event, person);
        notify();
    }

    void updateEvent(string name, string description, string date, pair<double, double> location){
        if (name.empty() || description.empty() || date.empty())
            throw std::invalid_argument("Invalid input!");
        repository.updateEvent(name, description, date, location);
        notify();
    }
    vector<Event> getEvents(){
        vector<Event> events = repository.getEvents();
        sort(events.begin(), events.end(), [](const Event& event1, const Event& event2){
            return event1.getDate() < event2.getDate();
        });
        return events;
    }
    vector<pair<Event, int>> mostPopularEvents(){
        vector<pair<Event, int>> mostPopular;
        vector<pair<Event, Person>> participantsAtEvents = repository.getParticipantsAtEvents();
        for (auto& it: participantsAtEvents){
            bool found = false;
            for (auto& it2: mostPopular){
                if (it.first.getName() == it2.first.getName()){
                    it2.second++;
                    found = true;
                    break;
                }
            }
            if (!found)
                mostPopular.push_back(make_pair(it.first, 1));
        }
        sort(mostPopular.begin(), mostPopular.end(), [](const pair<Event, int>& event1, const pair<Event, int>& event2){
            return event1.second > event2.second;
        });
        return mostPopular;
    }
    bool isPersonGoingToCertainEvent(Event event, Person person){
        vector<pair<Event, Person>> participantsAtEvents = repository.getParticipantsAtEvents();
        for (auto& it: participantsAtEvents)
            if (it.first.getName() == event.getName() && it.second.getName() == person.getName())
                return true;
        return false;
    }
    vector<Person> getPersonsGoingToEvent(Event event){
        vector<Person> persons;
        vector<pair<Event, Person>> participantsAtEvents = repository.getParticipantsAtEvents();
        for (auto& it: participantsAtEvents)
            if (it.first.getName() == event.getName())
                persons.push_back(it.second);
        return persons;
    }
};
