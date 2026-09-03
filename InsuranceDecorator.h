#ifndef INSURANCEDECORATOR_H
#define INSURANCEDECORATOR_H

#include <string>
using namespace std;

#include "PackageDecorator.h"

class InsuranceDecorator : public PackageDecorator{
    private:
        double CoverageAmount;
        string policyNumber;
    public:
        InsuranceDecorator(WorkUnit*,double,string);
        void execute();    
        double getWeight();
        WorkIterator* createIterator();
};

#endif