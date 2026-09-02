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
        void execute();    
};

#endif