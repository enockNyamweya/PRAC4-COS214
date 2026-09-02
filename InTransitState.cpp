#include "InTransitState.h"

void InTransitState::dispatchPackageItem(PackageItem* item){
    std::cout<<"Package has already been dispatched."<<std::endl;
   
}
void InTransitState::deliverPackageItem(PackageItem* item){
    std::cout<<"Sending Package out for delivery"<<std::endl;
    item->ChangeState(new DeliveredState());
}
std::string InTransitState::getStateName(){
    return "Order In Transit";
}