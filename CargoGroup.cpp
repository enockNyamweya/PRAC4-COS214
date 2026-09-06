#include "CargoGroup.h"
#include "SnapshotIterator.h"
#include <iostream>
#include <algorithm>

CargoGroup::CargoGroup(const std::string& name)
    : WorkUnit(name, 0.0) {}

CargoGroup::~CargoGroup() {
    // Recursive polymorphic destruction of all child objects
    for (WorkUnit* child : children) {
        delete child;
    }
    children.clear();
}

void CargoGroup::execute() {
    std::cout << "[CargoGroup] Processing Group: " << name << std::endl;
    for (WorkUnit* child : children) {
        if (child) {
            child->execute();
        }
    }
}

double CargoGroup::getWeight() const {
    double totalWeight = 0.0;
    for (const WorkUnit* child : children) {
        if (child) {
            totalWeight += child->getWeight();
        }
    }
    return totalWeight;
}

void CargoGroup::add(WorkUnit* unit) {
    if (unit) {
        children.push_back(unit);
    }
}

void CargoGroup::remove(WorkUnit* unit) {
    auto it = std::find(children.begin(), children.end(), unit);
    if (it != children.end()) {
        children.erase(it);
    }
}

const std::vector<WorkUnit*>& CargoGroup::getChildren() const {
    return children;
}

WorkIterator* CargoGroup::createIterator() {
    std::vector<WorkUnit*> fullSnapshot;
    // Helper lambda to recursively collect all composite and leaf nodes
    struct Helper {
        static void collect(WorkUnit* unit, std::vector<WorkUnit*>& list) {
            if (!unit) return;
            list.push_back(unit);
            CargoGroup* group = dynamic_cast<CargoGroup*>(unit);
            if (group) {
                for (WorkUnit* child : group->getChildren()) {
                    collect(child, list);
                }
            }
        }
    };
    for (WorkUnit* child : children) {
        Helper::collect(child, fullSnapshot);
    }
    return new SnapshotIterator(fullSnapshot);
}