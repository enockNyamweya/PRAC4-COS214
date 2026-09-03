#include "InsuranceDecorator.h"

InsuranceDecorator::InsuranceDecorator(WorkUnit * unit, double c, string p) : PackageDecorator(unit)
{
    wrappedUnit = unit;
    CoverageAmount = c;
    policyNumber = p;
}

void InsuranceDecorator::execute()
{
    wrappedUnit->execute();
    wrappedUnit->getWeight() + 3;
    cout<<"[Insurance] The policy number is: "<<policyNumber<<endl;
    cout<<"The insurance amount is R"<<CoverageAmount<<endl;
}

double InsuranceDecorator::getWeight()
{
    return wrappedUnit->getWeight();
}

WorkIterator *InsuranceDecorator::createIterator()
{
    return wrappedUnit->createIterator();
}
