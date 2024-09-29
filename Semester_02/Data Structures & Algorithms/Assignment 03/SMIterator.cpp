#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
    this->current_node = map.head;
    this->current_index = 0;
}

void SMIterator::first(){
    this->current_node = map.head;
    this->current_index = 0;
}

void SMIterator::next(){
    if (!this->valid()) {
        throw exception();
    }
	this->current_node = this->current_node->next;
    this->current_index++;
}

bool SMIterator::valid() const{
    if (this->current_node != nullptr) {
        return true;
    }
	return false;
}

TElem SMIterator::getCurrent() const{
    if (!this->valid()) {
        throw exception();
    }
    return this->current_node->data;
}


