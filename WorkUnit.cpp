#include "WorkUnit.h"
#include <iostream>

WorkUnit::WorkUnit(const std::string& name, double weight)
    : name(name), baseWeight(weight) {}

WorkUnit::~WorkUnit() {}

std::string WorkUnit::getName() const {
    return name;
}

double WorkUnit::getWeight() const {
    return baseWeight;
}

void WorkUnit::add(WorkUnit* unit) {
    (void)unit;
    std::cout << "[Warning] Cannot add child to a leaf WorkUnit." << std::endl;
}

void WorkUnit::remove(WorkUnit* unit) {
    (void)unit;
    std::cout << "[Warning] Cannot remove child from a leaf WorkUnit." << std::endl;
}