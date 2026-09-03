#include "DeliveredState.h"

void DeliveredState::dispatchPackageItem(PackageItem* item){
    (void)item;
    std::cout<<"Package has already been dispatched."<<std::endl;
   
}
void DeliveredState::deliverPackageItem(PackageItem* item){
    (void)item;
    std::cout<<"Package already been delivered"<<std::endl;
    
}
std::string DeliveredState::getStateName(){
    return "Order Delivered";
}