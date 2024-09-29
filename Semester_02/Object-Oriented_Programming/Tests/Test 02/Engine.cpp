//
// Created by Rares-Andrei Cotoi on 23.04.2024.
//

#include "Engine.h"

Engine::Engine(){
    this->basePrice = 3000;
}

ElectricEngine::ElectricEngine() : Engine(){
    this->autonomy = 0;
}

ElectricEngine::ElectricEngine(int autonomy) : Engine(){
    this->autonomy = autonomy;
}

double ElectricEngine::getPrice(){
    return this->basePrice + this->autonomy * 0.01;
}

std::string ElectricEngine::toString(){
    return "Electric engine with autonomy " + std::to_string(this->autonomy) + " km";
}

TurboEngine::TurboEngine() : Engine(){
}

double TurboEngine::getPrice(){
    return this->basePrice + 100;
}

std::string TurboEngine::toString(){
    return "Turbo engine";
}
