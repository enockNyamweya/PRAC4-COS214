#include "FailedDeliveredState.h"

void FailedDeliveredState::dispatchPackageItem(PackageItem* item){
    std::cout<<"Package has already been dispatched."<<std::endl;
   
}
void FailedDeliveredState::deliverPackageItem(PackageItem* item){
    failCount++;
    if(failCount > 4){
        std::cout<<"Package has failed too many times."<<std::endl;
    }else{
        std::cout<<"Package has failed to be delivered, trying again"<<std::endl;
        item->ChangeState(new DeliveredState());
    }
    
    
}
std::string FailedDeliveredState::getStateName(){
    return "Order Failed";
}