#include "PriorityFilteredIterator.h"
#include "PackageDecorator.h"

PriorityFilteredIterator::PriorityFilteredIterator(WorkIterator * it)
{
    inneriterator = it;
}

void PriorityFilteredIterator::first()
{
    inneriterator->first();
    while (!inneriterator->isDone() &&
        dynamic_cast<PackageDecorator*>(inneriterator->currentItem()) == nullptr) {
        inneriterator->next();
    }
}

void PriorityFilteredIterator::next()
{
    inneriterator->next();
    while (!inneriterator->isDone() &&
        dynamic_cast<PackageDecorator*>(inneriterator->currentItem()) == nullptr) {
        inneriterator->next();
    }
}

bool PriorityFilteredIterator::isDone()
{
    return inneriterator->isDone();
}

WorkUnit *PriorityFilteredIterator::currentItem()
{
    return inneriterator->currentItem();
}

PriorityFilteredIterator::~PriorityFilteredIterator()
{
    delete inneriterator;
}
