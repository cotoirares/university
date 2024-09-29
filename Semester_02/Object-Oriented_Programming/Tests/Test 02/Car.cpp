//
// Created by Rares-Andrei Cotoi on 23.04.2024.
//

#include "Car.h"

Car::Car(std::string& bodyStyle, Engine* engine) {
    this->bodyStyle = bodyStyle;
    this->engine = engine;
}

double Car::computePrice() {
    if (this->bodyStyle == "Sedan") {
        return 8000 + this->engine->getPrice();
    }
    else{
        if (this->bodyStyle == "Convertible")
            return 9000 + this->engine->getPrice();
    }
    return -1;
}

std::string Car::toString() {
    return "Car with body style " + this->bodyStyle + " and engine " + this->engine->toString();
}