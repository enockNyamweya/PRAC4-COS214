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
    cout<<"Step 1 visiting: "<<it2->currentItem()->getName()<<endl;
    it2->next();
    cout<<"Step 2 visiting: "<<it2->currentItem()->getName()<<endl;

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

    cout<<"\n\nSCENARIO III: STATES LIFECYCLE & USING FILTERED ITERATOR"<<endl;
    
    //testing full state transitions from
    //orderplaced -> intransit -> delivered/failed
    WorkUnit* testParcel=new PackageItem("Test Parcel", 1.5, "TRK-999", new OrderPlacedState());
    testParcel->execute(); //placed -> transit
    testParcel->execute(); //transit -> delivered
    testParcel->execute(); //testing invalid guard action on delivered state

    //using the filter iterator
    cout<<"...Priority Filtered Iteration"<<endl;
    WorkIterator* baseIt=warehouse->createIterator();
    WorkIterator* priorityIt=new PriorityFilteredIterator(baseIt);

    for(priorityIt->first(); !priorityIt->isDone(); priorityIt->next()){
        cout<<"Filtered Priority Item: "<<priorityIt->currentItem()->getName()<<endl;
    }

    delete priorityIt;
    delete baseIt;
    delete testParcel;

    delete warehouse;

    cout<<"Execution complete"<<endl;


    return 0;
}

