#include "InTransitState.h"
#include "DeliveredState.h"

void InTransitState::dispatchPackageItem(PackageItem* item){
    (void)item;
    std::cout<<"Package has already been dispatched. Delivering..."<<std::endl;
   deliverPackageItem(item);
}
void InTransitState::deliverPackageItem(PackageItem* item){
    
    std::cout<<"Sending Package out for delivery"<<std::endl;
    item->changeState(new DeliveredState());
  
}
std::string InTransitState::getStateName(){
    return "Order In Transit";
}