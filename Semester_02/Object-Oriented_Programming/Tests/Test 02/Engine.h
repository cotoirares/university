//
// Created by Rares-Andrei Cotoi on 23.04.2024.
//

#ifndef OOP_T2_COTOIRARES_ENGINE_H
#define OOP_T2_COTOIRARES_ENGINE_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

class Engine {
protected:
    double basePrice;
public:
    Engine();
    virtual double getPrice() = 0;
    virtual std::string toString() = 0;

    virtual ~Engine() = default;
};

class ElectricEngine : public Engine {
private:
    int autonomy;
public:
    ElectricEngine();
    ElectricEngine(int autonomy);
    double getPrice() override;
    std::string toString() override;

    ~ElectricEngine() override = default;
};

class TurboEngine : public Engine {
public:
    TurboEngine();
    double getPrice() override;
    std::string toString() override;

    ~TurboEngine() override = default;
};

#endif //OOP_T2_COTOIRARES_ENGINE_H
