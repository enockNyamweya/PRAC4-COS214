#include "PackageDecorator.h"

PackageDecorator::PackageDecorator(WorkUnit * unit) : WorkUnit(unit->getName(),unit->getWeight())
{
    wrappedUnit = unit;
}

double PackageDecorator::getWeight()
{
    return wrappedUnit->getWeight();
}

WorkIterator* PackageDecorator::createIterator()
{
    return wrappedUnit->createIterator();
}

PackageDecorator::~PackageDecorator()
{
    delete wrappedUnit;
}
