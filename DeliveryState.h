#ifndef DELIVERYSTATE_H
#define DELIVERYSTATE_H
#include <iostream>
#include <string>
#include "PackageItem.h"

class DeliveryState{


    public:
    DeliveryState();
    virtual ~DeliveryState();
     
    virtual void dispatchPackageItem(PackageItem* item);
    virtual void deliverPackageItem(PackageItem* item);
    virtual std::string getStateName();
    


};


#endif