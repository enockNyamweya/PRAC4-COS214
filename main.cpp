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

int main() {
    cout << "\nTASKFORGE LOGISTICS SYSTEM DEMONSTRATION\n" << endl;

    // SCENARIO I
    cout << "SCENARIO I: COMPOSITE WAREHOUSE HIERARCHY & STACKED DECORATORS DISPATCH\n" << endl;

    cout << "[Step 1] Constructing 3-Level Composite Warehouse Tree..." << endl;
    WorkUnit* warehouse = new CargoGroup("Johannesburg Main Warehouse");
    WorkUnit* hub       = new CargoGroup("Air Freight Sector");
    WorkUnit* pallet    = new CargoGroup("Pallet A1");

    cout << "  Linking Containers: [Warehouse] -> [Air Freight Sector] -> [Pallet A1]" << endl;
    warehouse->add(hub);
    hub->add(pallet);

    cout << "\n[Step 2] Registering Leaf PackageItems & Applying Stacked Decorators..." << endl;
    WorkUnit* parcel1 = new PackageItem("Electronics Parcel", 4.5, "TRK-101", new OrderPlacedState());
    WorkUnit* parcel2 = new PackageItem("Clothing Parcel", 2.0, "TRK-102", new OrderPlacedState());

    cout << "  Stacking Decorators on TRK-101: InsuranceDecorator(ExpressShippingDecorator(PackageItem))" << endl;
    WorkUnit* decoratedParcel1 = new InsuranceDecorator(
                                    new ExpressShippingDecorator(parcel1, 50.0, 1), 
                                    500.0, "POL-991"
                                );

    cout << "  Storing parcels inside Container [Pallet A1]..." << endl;
    pallet->add(decoratedParcel1);
    pallet->add(parcel2);

    cout << "\n[Step 3] Initializing SnapshotIterator & Traversing Entire Warehouse Hierarchy..." << endl;
    WorkIterator* it1 = warehouse->createIterator();

    int stepCount = 1;
    for (it1->first(); !it1->isDone(); it1->next()) {
        WorkUnit* current = it1->currentItem();
        if (current) {
            cout << "\n[Node " << stepCount++ << "] Executing Unit: " << current->getName() << endl;
            current->execute();
        }
    }
    delete it1;


    // SCENARIO II
    cout << "\n\nSCENARIO II: DYNAMIC MID-TRAVERSAL SAFETY (STRUCTURAL TREE MODIFICATION)\n" << endl;

    cout << "[Step 1] Creating new SnapshotIterator over live Warehouse..." << endl;
    WorkIterator* it2 = warehouse->createIterator();

    it2->first();
    if (it2->currentItem()) {
        cout << "  Step 1 Visiting Node: " << it2->currentItem()->getName() << endl;
    }
    it2->next();
    if (it2->currentItem()) {
        cout << "  Step 2 Visiting Node: " << it2->currentItem()->getName() << endl;
    }

    cout << "\n[Step 2] [DYNAMIC RUNTIME CHANGE] Adding new Container 'Pallet B2' mid-loop..." << endl;
    WorkUnit* palletB2 = new CargoGroup("Pallet B2");
    hub->add(palletB2);
    cout << "  'Pallet B2' successfully attached to 'Air Freight Sector' while iterator is active!" << endl;

    cout << "\n[Step 3] Resuming Iterator Traversal to Completion (Verifying Snapshot Safety)..." << endl;
    while (!it2->isDone()) {
        if (it2->currentItem()) {
            cout << "  Safe Snapshot Visiting: " << it2->currentItem()->getName() << endl;
        }
        it2->next();
    }
    delete it2;


    // SCENARIO III
    cout << "\n\nSCENARIO III: REAL-WORLD STATE LIFECYCLE, GUARDS & FILTERED TRAVERSAL\n" << endl;

    cout << "Parcel Lifecycle A: Successful Delivery Stream" << endl;
    PackageItem* macbook = new PackageItem("MacBook Pro 16\"", 2.5, "TRK-888", new OrderPlacedState());
    cout << "  [Initial Setup] Tracking ID: " << macbook->getTrackingId() 
         << " | Base Weight: " << macbook->getWeight() << " kg"
         << " | State: " << macbook->getState()->getStateName() << endl;

    cout << "  Action 1: Warehouse Manager dispatches parcel..." << endl;
    macbook->execute();
    cout << "  Updated State: " << macbook->getState()->getStateName() << endl;

    cout << "  Action 2: Courier delivers parcel to recipient..." << endl;
    macbook->getState()->deliverPackageItem(macbook);
    cout << "  Updated State: " << macbook->getState()->getStateName() << endl;

    cout << "\n  [Protection Guard Test] Attempting duplicate dispatch on delivered parcel:" << endl;
    macbook->execute();
    macbook->getState()->deliverPackageItem(macbook);


    cout << "\n\nParcel Lifecycle B: Delivery Failure & Retry Stream" << endl;
    PackageItem* laptop = new PackageItem("Gaming Laptop", 3.8, "TRK-777", new OrderPlacedState());
    cout << "  [Initial Setup] Tracking ID: " << laptop->getTrackingId() 
         << " | State: " << laptop->getState()->getStateName() << endl;

    cout << "  Action 1: Warehouse Manager dispatches parcel..." << endl;
    laptop->execute();

    cout << "\n  [Delivery Exception] Customer absent at delivery address!" << endl;
    laptop->changeState(new FailedDeliveryState());
    cout << "  Updated State: " << laptop->getState()->getStateName() << endl;

    cout << "  Action 2: Attempting invalid dispatch on failed package..." << endl;
    laptop->getState()->dispatchPackageItem(laptop);

    cout << "\n  Action 3: Courier retries delivery next morning..." << endl;
    laptop->getState()->deliverPackageItem(laptop);
    cout << "  Final State: " << laptop->getState()->getStateName() << endl;


    cout << "\n\nFiltered Traversal Strategy: Priority & Express Items Only" << endl;
    cout << "  Warehouse Calculated Recursive Total Weight: " << warehouse->getWeight() << " kg" << endl;

    WorkIterator* baseIt = warehouse->createIterator();
    WorkIterator* priorityIt = new PriorityFilteredIterator(baseIt);

    cout << "  Scanning Warehouse for Express/Insured Packages..." << endl;
    int priorityCount = 1;
    for (priorityIt->first(); !priorityIt->isDone(); priorityIt->next()) {
        WorkUnit* priorityItem = priorityIt->currentItem();
        if (priorityItem) {
            cout << "  [" << priorityCount++ << "] Found Priority Package: " << priorityItem->getName() 
                 << " (Total Weight: " << priorityItem->getWeight() << " kg)" << endl;
        }
    }

    delete priorityIt;
    delete macbook;
    delete laptop;
    delete warehouse;

    cout << "\n\nTaskForge Logistics Engine Completed Execution Cleanly." << endl;

    return 0;
}

