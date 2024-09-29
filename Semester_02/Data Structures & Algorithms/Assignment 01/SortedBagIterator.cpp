#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <utility>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    this->currentIndex = 0;
    this->currentEl = bag.sortedBag[this->currentIndex];
}

TComp SortedBagIterator::getCurrent() {
    if (!this->valid())
        throw exception();
    return this->currentEl.first;
}

bool SortedBagIterator::valid() {
    return this->currentIndex < this->bag.length;
}

void SortedBagIterator::next() {
    if (!this->valid())
        throw exception();
    this->currentIndex++;
    this->currentEl = this->bag.sortedBag[this->currentIndex];
}

void SortedBagIterator::first() {
    this->currentIndex = 0;
    this->currentEl = this->bag.sortedBag[0];
}

