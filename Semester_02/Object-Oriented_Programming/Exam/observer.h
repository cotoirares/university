//
// Created by Rares-Andrei Cotoi on 11.07.2024.
//
#pragma once

class Observer {
public:
    Observer() = default;
    virtual ~Observer() = default;
    virtual void update() const = 0;
};
