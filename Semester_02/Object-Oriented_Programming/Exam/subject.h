//
// Created by Rares-Andrei Cotoi on 11.07.2024.
//

#pragma once
#include <memory>
#include <vector>
#include "observer.h"
class Subject {
private:
    std::vector<Observer*> obs;

public:
    Subject() = default;
    ~Subject() = default;
    void regObs(Observer* observer) {
        obs.emplace_back(observer);
    }
    void notify() {
        for (auto& observer : obs) {
            observer->update();
        }
    }
};
