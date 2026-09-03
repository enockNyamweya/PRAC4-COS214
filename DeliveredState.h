#ifndef DELIVEREDSTATE_H
#define DELIVEREDSTATE_H
#include <iostream>
#include <string>
#include "DeliveryState.h"
#include "PackageItem.h"

class DeliveredState : public DeliveryState{


    public:
    void dispatchPackageItem(PackageItem* item);
    void deliverPackageItem(PackageItem* item);
    std::string getStateName();


};


#endif