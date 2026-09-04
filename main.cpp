#include <iostream>
//composite
#include "WorkUnit.h"
#include "CargoGroup.h"
#include "PackageItem.h"
//state
#include "DeliveryState.h"
#include "OrderPlacedState.h"
#include "InTransitState.h"
#include "FailedDeliveryState.h"
//decorator
#include "PackageDecorator.h"
#include "ExpressShippingDecorator.h"
#include "InsuranceDecorator.h"
//iterator
#include "WorkIterator.h"
#include "SnapshotIterator.h"
#include "PriorityFilteredIterator.h"

using namespace std;

int main(){
    cout<<"SCENARIO I: NORMAL DISPATCH & DECORATORS\n"<<endl;

    //creating root warehouse & subgroups
    WorkUnit* warehouse=new CargoGroup("Johannesburg Main Warehouse");
    WorkUnit* hub=new CargoGroup("Air Freight Sector");
    WorkUnit* pallet=new CargoGroup("Pallet A1");

    //building the composite hierarchy
    warehouse->add(hub);
    hub->add(pallet);

    //creating leaf parcels with initial state
    WorkUnit* parcel1=new PackageItem("Electronics Parcel", 4.5, "TRK-101", new OrderPlacedState());
    WorkUnit* parcel2=new PackageItem("Clothing Parcel", 2.0, "TRK-102", new OrderPlacedState());

    //adding decorators to parcel1
    WorkUnit* decoratedParcel1=new InsuranceDecorator(new ExpressShippingDecorator(parcel1, 50.0, 1), 500.0, "POL-991");

    //adding items to Pallet A1
    pallet->add(decoratedParcel1);
    pallet->add(parcel2);

    //TRAVERSING & PROCESSING WAREHOUSE
    cout<<"... Starting Warehouse Traversal & Execution\n"<<endl;
    WorkIterator* it1=warehouse->createIterator();

    for(it1->first(); !it1->isDone(); it1->next()){
        WorkUnit* current=it1->currentItem();
        if(current){
            current->execute();
        }
    }

    delete it1; //cleaning up the iterator we created

    cout<<"\n\nSCENARIO II: DYNAMIC & MID-TRAVERSAL SAFETY"<<endl;

    //new iterator
    WorkIterator* it2=warehouse->createIterator();

    //iterating halfway
    it2->first();
    if(it2->currentItem()){
        cout<<"Step 1 visiting: "<<it2->currentItem()->getName()<<endl;
    }
    it2->next();
    if(it2->currentItem()){
        cout<<"Step 2 visiting: "<<it2->currentItem()->getName()<<endl;
    }

    //performing a runtime structure change to the composite mid-loop
    cout<<"\n\n[DYNAMIC CHANGE] Adding new Pallet B2 and moving parcel..."<<endl;
    WorkUnit* palletB2=new CargoGroup("Pallet B2");
    hub->add(palletB2);

    //continuing iteration now
    cout<<"\n... Resuming Traversal to the end..."<<endl;
    while(!it2->isDone()){
        cout<<"Safe Snapshot Visiting: "<<it2->currentItem()->getName()<<endl;
        it2->next();
    }

    delete it2; //cleaning up iterator 2

    cout << "\nSCENARIO III: SEEING IT IN ACTION (STATES, GUARDS & PRIORITY FILTERED TRAVERSAL)" << endl;

    // macpro parcel lifecycle
    cout << "\nParcel 1 Lifecycle: Standard Successful Delivery \n" << endl;
    PackageItem* macbook = new PackageItem("MacBook Pro 16\"", 2.5, "TRK-888", new OrderPlacedState());
    cout << "Tracking ID: " << macbook->getTrackingId() << ", Initial State: " << macbook->getState()->getStateName() << endl;

    // dispatching macpro parcel from Warehouse
    macbook->execute(); // Transitions OrderPlacedState -> InTransitState
    cout << "Updated State: " << macbook->getState()->getStateName() << endl;

    // delivering macpro parcel to customer address
    macbook->getState()->deliverPackageItem(macbook); // Transitions InTransitState -> DeliveredState
    cout << "Updated State: " << macbook->getState()->getStateName() << endl;

    // testing Guard - testing dispatch/deliver an already delivered parcel
    cout << "\n[Guard Protection Test] Attempting duplicate dispatch on delivered parcel:" << endl;
    macbook->execute();
    macbook->getState()->deliverPackageItem(macbook);


    //failed scenario
    cout << "\n Parcel 2 Lifecycle: Failed Delivery & Retry Attempt \n" << std::endl;
    PackageItem* laptop = new PackageItem("Gaming Laptop", 3.8, "TRK-777", new OrderPlacedState());
    
    // dispatching laptop from Warehouse
    laptop->execute(); // OrderPlacedState -> InTransitState

    // recipient absent -> Transition to FailedDeliveryState
    cout << "\n[Delivery Exception] Recipient absent at delivery address!" << endl;
    laptop->changeState(new FailedDeliveryState());
    cout << "Updated State: " << laptop->getState()->getStateName() << endl;

    // attempt invalid dispatch on failed package
    laptop->getState()->dispatchPackageItem(laptop);

    // retry delivery next day -> Transitions to DeliveredState!
    cout << "\n[Delivery Retry] Retrying package delivery next morning..." << endl;
    laptop->getState()->deliverPackageItem(laptop);
    cout << "Final State: " << laptop->getState()->getStateName() << endl;


    
    // Priority Filtered Traversal 
    cout << "\n Priority Filtered Traversal \n" << std::endl;
    
    cout << "Current Warehouse Total Weight: " << warehouse->getWeight() << " kg" << endl;

    WorkIterator* baseIt = warehouse->createIterator();
    WorkIterator* priorityIt = new PriorityFilteredIterator(baseIt);

    for (priorityIt->first(); !priorityIt->isDone(); priorityIt->next()) {
        WorkUnit* priorityItem = priorityIt->currentItem();
        if (priorityItem) {
            cout << "Found Express/Insured Package: " << priorityItem->getName() 
                 << " (Weight: " << priorityItem->getWeight() << " kg)" << endl;
        }
    }

    // Cleanup dynamic objects for scenario 3
    delete priorityIt; 
    delete macbook;
    delete laptop;

    delete warehouse;

    cout<<"\nExecution complete"<<endl;


    return 0;
}

