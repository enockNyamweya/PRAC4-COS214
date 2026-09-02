#ifndef SNAPSHOTITERATOR_H
#define SNAPSHOTITERATOR_H

#include <vector>

#include "WorkIterator.h"

using namespace std;

class SnapshotIterator : public WorkIterator{
    private:
        vector<WorkUnit*> snapshot;
        int index;
    public:
        void first();
        void next();
        bool isDone();
        WorkUnit* currentItem();    
};

#endif