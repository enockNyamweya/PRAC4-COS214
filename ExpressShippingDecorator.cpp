#include "ExpressShippingDecorator.h"

ExpressShippingDecorator::ExpressShippingDecorator(WorkUnit * unit, double f, int p) : PackageDecorator(unit)
{
    wrappedUnit = unit;
    expressFee = f;
    priorityLevel = p;
}

void ExpressShippingDecorator::execute()
{
    wrappedUnit->execute();
    wrappedUnit->getWeight() + 3;
    cout<<"[Express] The priority level for "<<wrappedUnit->getName()<<" is: "<<priorityLevel<<endl;
    cout<<"The express is R"<<expressFee<<endl;
}

double ExpressShippingDecorator::getWeight()
{
    return wrappedUnit->getWeight();
}

WorkIterator *ExpressShippingDecorator::createIterator()
{
    return wrappedUnit->createIterator();
}
