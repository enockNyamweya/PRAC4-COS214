#ifndef EXPRESSSHIPPINGDECORATOR_H
#define EXPRESSSHIPPINGDECORATOR_H

#include "PackageDecorator.h"

class ExpressShippingDecorator : public PackageDecorator{
    private:
        double expressFee;
        int priorityLevel;
    public:
        ExpressShippingDecorator(WorkUnit*, double, int);
        void execute(); 
        double getWeight();
        WorkIterator* createIterator();   
};

#endif