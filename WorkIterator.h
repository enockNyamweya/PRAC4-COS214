#ifndef WORKITERATOR_H
#define WORKITERATOR_H

#include "WorkUnit.h"

class WorkIterator{
    public:
        virtual void first() = 0;
        virtual void next() = 0;
        virtual bool isDone() = 0;
        virtual WorkUnit* currentItem() = 0;
};

#endif