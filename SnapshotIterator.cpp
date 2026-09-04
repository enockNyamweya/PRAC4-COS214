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
    //iterator just references item
    snapshot.clear();
}
