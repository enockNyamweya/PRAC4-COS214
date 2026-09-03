#ifndef DELIVERYSTATE_H
#define DELIVERYSTATE_H
#include <iostream>
#include <string>
#include "PackageItem.h"

class DeliveryState{


    public:
    DeliveryState();
    virtual ~DeliveryState();
     
    virtual void dispatchPackageItem(PackageItem* item) =0;
    virtual void deliverPackageItem(PackageItem* item) =0;
    virtual std::string getStateName() =0;
    


};


#endif