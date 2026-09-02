#include "OrderPlacedState.h"

void OrderPlacedState::dispatchPackageItem(PackageItem* item){
    std::cout<<"Order Placed, Dispatching..."<<std::endl;
    item.ChangeState(new InTransitState*);
}
void OrderPlacedState::deliverPackageItem(PackageItem* item){
    std::cout<<"Can not deliver an Item before its been dispatched."<<std::endl;
}
std::string OrderPlacedState::getStateName(){
    return "Order Placed";
}