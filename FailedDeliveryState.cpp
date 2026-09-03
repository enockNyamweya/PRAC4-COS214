#include "FailedDeliveryState.h"
#include "DeliveredState.h"

void FailedDeliveryState::dispatchPackageItem(PackageItem* item){
    (void)item;
    std::cout<<"Package has already been dispatched."<<std::endl;
   
}
void FailedDeliveryState::deliverPackageItem(PackageItem* item){
    failCount++;
    if(failCount > 4){
        std::cout<<"Package has failed too many times."<<std::endl;
    }else{
        std::cout<<"Package has failed to be delivered, trying again"<<std::endl;
        item->changeState(new DeliveredState());
    }
    
    
}
std::string FailedDeliveryState::getStateName(){
    return "Order Failed";
}