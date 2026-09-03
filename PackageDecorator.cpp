#include "PackageDecorator.h"

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
