#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    this->currentIndex = 0;
    this->elements.capacity = 10;
    this->elements.length = 0;
    this->elements.pairs = new TElem[this->elements.capacity];
    inOrderTraversal(map.root);
}

void SMMIterator::first(){
    this->currentIndex = 0;
}

void SMMIterator::next(){
    this->currentIndex++;
}

bool SMMIterator::valid() const{
    return this->currentIndex < this->elements.length;
}

TElem SMMIterator::getCurrent() const{
    if (!valid()) {
        throw std::exception();
    }
    return this->elements.pairs[this->currentIndex];
}


