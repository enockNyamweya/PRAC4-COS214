#ifndef PACKAGEDECORATOR_H
#define PACKAGEDECORATOR_H

#include "WorkUnit.h"
#include "WorkIterator.h"

class PackageDecorator : public WorkUnit {
    private:
        WorkUnit* wrappedUnit;
    public:
        virtual void execute() = 0;
        virtual double getWeight() = 0;
        virtual WorkIterator* createIterator() = 0;   
};

#endif