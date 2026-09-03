#include "PackageItem.h"
#include "DeliveryState.h"
#include "SnapshotIterator.h"
#include <iostream>

PackageItem::PackageItem(const std::string& name, double weight, const std::string& trackingId, DeliveryState* initialState)
    : WorkUnit(name, weight), trackingId(trackingId), state(initialState) {}

PackageItem::~PackageItem() {
    delete state;
    state = nullptr;
}

void PackageItem::execute() {
    std::cout << "[PackageItem] Parcel (" << trackingId << ": " << name << ", Weight: " << baseWeight << "kg)" << std::endl;
    if (state) {
        state->dispatchPackageItem(this);
    }
}

void PackageItem::changeState(DeliveryState* newState) {
    if (newState && newState != state) {
        delete state;
        state = newState;
    }
}

DeliveryState* PackageItem::getState() const {
    return state;
}

std::string PackageItem::getTrackingId() const {
    return trackingId;
}

WorkIterator* PackageItem::createIterator() {
    std::vector<WorkUnit*> singleItem;
    singleItem.push_back(this);
    return new SnapshotIterator(singleItem);
}