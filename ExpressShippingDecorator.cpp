#include "ExpressShippingDecorator.h"

void ExpressShippingDecorator::execute()
{
    wrappedUnit->execute();
    wrappedUnit->getWeight() + 3;
    cout<<"[Express] The priority level for "<<wrappedUnit->getName()<<" is: "<<priorityLevel<<endl;
    cout<<"The express is R"<<expressFee<<endl;
}