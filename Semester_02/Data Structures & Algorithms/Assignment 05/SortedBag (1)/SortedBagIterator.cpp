#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    this->capacity = this->bag.capacity;
    this->length = this->bag.length;
    this->sortedArray = new int[this->capacity];
    for (int i = 0; i < this->length; i++)
        this->sortedArray[i] = -1;
    this->currentElement = 0;
    int current = 0;
    for (int i = 0; i < this->capacity; i++)
        if (this->bag.TKey[i] != -1){
            this->sortedArray[current] = i;
            current++;
        }
    this->sortArray();

}

TComp SortedBagIterator::getCurrent() {
    if (!this->valid())
        throw exception();
    return this->bag.TKey[this->sortedArray[this->currentElement]];
}

bool SortedBagIterator::valid() {
    return this->currentElement < this->length;
}

void SortedBagIterator::next() {
    if (!this->valid())
        throw exception();
    this->currentElement++;
}

void SortedBagIterator::first() {
    this->currentElement = 0;
}

