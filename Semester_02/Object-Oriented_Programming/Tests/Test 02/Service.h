//
// Created by Rares-Andrei Cotoi on 23.04.2024.
//

#ifndef OOP_T2_COTOIRARES_SERVICE_H
#define OOP_T2_COTOIRARES_SERVICE_H

#include "Car.h"
#include <vector>
#include <string>

class Service{
private:
    std::vector<Car*> cars;
public:
    Service();
    void addCar(std::string bodyStyle, std::string engineType, int autonomy);
    std::vector<Car*> getCarsWithMaxPrice(double maxPrice);
    std::vector<Car*> getCars();
    void writeToFile(std::string fileName, double MaxPrice);
    ~Service();
};

#endif //OOP_T2_COTOIRARES_SERVICE_H
