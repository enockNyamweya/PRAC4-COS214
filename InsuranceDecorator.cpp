#include "InsuranceDecorator.h"

void InsuranceDecorator::execute()
{
    wrappedUnit->execute();
    wrappedUnit->getWeight() + 3;
    cout<<"[Insurance] The policy number is: "<<policyNumber<<endl;
    cout<<"The insurance amount is R"<<CoverageAmount<<endl;
}