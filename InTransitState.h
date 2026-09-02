#ifndef  INTRANSITSTATE_H
#define INTRANSITSTATE_H
#include <iostream>
#include <string>
#include "DeliveryState.h"
#include "PackageItem.h"


class InTransitState : public DeliveryState{


    public:
    void dispatchPackageItem(PackageItem* item);
    void deliverPackageItem(PackageItem* item);
    std::string getStateName();
    


};


#endif