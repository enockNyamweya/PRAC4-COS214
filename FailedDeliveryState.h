#ifndef  ORDERPLACEDSTATE_H
#define ORDERPLACEDSTATE_H
#include <iostream>
#include <string>
#include "DeliveryState.h"
#include "PackageItem.h"


class OrderPlacedState : public DeliveryState{


    public:
    void dispatchPackageItem(PackageItem* item);
    void deliverPackageItem(PackageItem* item);
    std::string getStateName();
    
private:
int failCount = 0;

};


#endif