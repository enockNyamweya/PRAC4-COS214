#ifndef PRIORITYFILTEREDITERATOR_H
#define PRIORITYFILTEREDITERATOR_H

#include "WorkIterator.h"

class PriorityFilteredIterator : public WorkIterator{
    private:
        WorkIterator* inneriterator;
    public:
        PriorityFilteredIterator(WorkIterator*);
        void first();
        void next();
        bool isDone();
        WorkUnit* currentItem();
        ~PriorityFilteredIterator();
};

#endif