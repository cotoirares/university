//
// Created by Rares-Andrei Cotoi on 23.04.2024.
//

#ifndef OOP_T2_COTOIRARES_CAR_H
#define OOP_T2_COTOIRARES_CAR_H

#include "Engine.h"
#include <string>

class Car {
private:
    std::string bodyStyle;
    Engine* engine;
public:
    Car(std::string& bodyStyle, Engine* engine);
    double computePrice();
    std::string toString();
    virtual ~Car() = default;
};

#endif //OOP_T2_COTOIRARES_CAR_H
