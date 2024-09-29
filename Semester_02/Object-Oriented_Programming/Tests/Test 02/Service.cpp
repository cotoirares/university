//
// Created by Rares-Andrei Cotoi on 23.04.2024.
//
#include <iostream>
#include "Car.h"
#include "Service.h"
#include <vector>

Service::Service() {
    this->cars = std::vector<Car*>();
}

void Service::addCar(std::string bodyStyle, std::string engineType, int autonomy) {
    Engine *engine;
    if (engineType == "Electric") {
        engine = new ElectricEngine(autonomy);
    } else if (engineType == "Turbo") {
        engine = new TurboEngine();
    } else {
        std::cout << "Invalid engine type!" << std::endl;
        return;
    }
    Car* car = new Car(bodyStyle, engine);
    this->cars.push_back(car);
    std::cout << "Car added successfully!" << std::endl;
    std::cout<<"Price: "<<car->computePrice()<<std::endl;
}

std::vector<Car*> Service::getCars() {
    return this->cars;
}

std::vector<Car*> Service::getCarsWithMaxPrice(double maxPrice) {
    std::vector<Car*> carsWithMaxPrice;
    for (Car* car : this->cars){
        if (car->computePrice() <= maxPrice){
            carsWithMaxPrice.push_back(car);
        }
    }
    return carsWithMaxPrice;
}

void Service::writeToFile(std::string fileName, double MaxPrice){
    std::ofstream file(fileName);
    std::vector<Car*> carsMaxPrice = getCarsWithMaxPrice(MaxPrice);
    std::sort(carsMaxPrice.begin(), carsMaxPrice.end(), [](Car* car1, Car* car2){
        return car1->computePrice() < car2->computePrice();
    });
    for (Car* car : carsMaxPrice){
        file << car->toString() << std::endl;
    }
    file.close();
}

Service::~Service() {
    for (Car* car : this->cars){
        delete car;
    }
}