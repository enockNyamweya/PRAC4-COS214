#include "SnapshotIterator.h"

//

SnapshotIterator::SnapshotIterator(const vector<WorkUnit *> &items)
{
    snapshot = items;
    index = 0;
}

void SnapshotIterator::first()
{
    index = 0;
}

void SnapshotIterator::next()
{
    if(!isDone()){
        index++;
    }
}

bool SnapshotIterator::isDone()
{
    return index >= static_cast<int>(snapshot.size());
}

WorkUnit *SnapshotIterator::currentItem()
{
    if(isDone()){
        return nullptr;
    }
    return snapshot[index];
}

SnapshotIterator::~SnapshotIterator()
{
    for(WorkUnit* ptr : snapshot){
        delete ptr;
    } //iterator just references itea
    snapshot.clear();
}
