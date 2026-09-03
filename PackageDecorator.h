#ifndef PACKAGEDECORATOR_H
#define PACKAGEDECORATOR_H

#include "WorkUnit.h"
#include "WorkIterator.h"

#include <iostream>
#include <string>
using namespace std;

class PackageDecorator : public WorkUnit {
    protected:
        WorkUnit* wrappedUnit;
    public:
        PackageDecorator(WorkUnit*);
        virtual void execute() = 0;
        virtual double getWeight();
        virtual WorkIterator* createIterator();   
        virtual ~PackageDecorator();
};

#endif