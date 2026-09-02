#ifndef PRIORITYFILTEREDITERATOR_H
#define PRIORITYFILTEREDITERATOR_H

#include "WorkIterator.h"

class PriorityFilteredIterator : public WorkIterator{
    private:
        WorkIterator* inneriterator;
    public:
        void first();
        void next();
        bool isDone();
        WorkUnit* currentItem();
};

#endif