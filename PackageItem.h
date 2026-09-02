#ifndef PACKAGEITEM_H
#define PACKAGEITEM_H

#include "WorkUnit.h"
#include <string>

class DeliveryState;

/**
 * @brief PackageItem: Leaf class representing individual parcels.
 * Acts as the Context in the State Pattern.
 */
class PackageItem : public WorkUnit {
private:
    std::string trackingId;
    DeliveryState* state;

public:
    PackageItem(const std::string& name, double weight, const std::string& trackingId, DeliveryState* initialState);
    virtual ~PackageItem(); // Deletes current state pointer

    void execute() override;
    void changeState(DeliveryState* newState);

    DeliveryState* getState() const;
    std::string getTrackingId() const;

    WorkIterator* createIterator() override;
};

#endif // PACKAGEITEM_H