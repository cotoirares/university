#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

SortedBag::SortedBag(Relation r) {
    this->m = 13;
    this->r = r;
    this->capacity = 13;
    this->length = 0;
    this->TKey = new int[capacity];
    this->next = new int[capacity];
    for (int i = 0; i < this->capacity; i++)
        this->next[i] = -1;
    this->firstEmpty = 0;
    for (int i = 0;i < this->capacity; i++)
        this->TKey[i] = -1;
}

void SortedBag::add(TComp e) {
    if (this->firstEmpty == this->capacity)
        this->resize();
    int pos = this->hash(e);
    if (this->TKey[pos] == -1){
        this->TKey[pos] = e;
        this->next[pos] = -1;
        if (pos == this->firstEmpty)
            this->changeFirstEmpty();
        this->length++;
    }
    else{
        int current = pos;
        while (this->next[current] != -1)
            current = this->next[current];
        this->TKey[this->firstEmpty] = e;
        this->next[this->firstEmpty] = -1;
        this->next[current] = this->firstEmpty;
        this->changeFirstEmpty();
        this->length++;
    }
}


bool SortedBag::remove(TComp e) {
    if (this->length == 0)
        return false;
    int pos = this->hash(e);
    int previous = -1;
    while (pos != -1 && this->TKey[pos] != e){
        previous = pos;
        pos = this->next[pos];
    }
    if (pos == -1)
        return false;
    else{
        bool over = false;
        do{
            int p = this->next[pos];
            int pp = pos;
            while (p != -1 && this->hash(this->TKey[p]) != pos){
                pp = p;
                p = this->next[p];
            }
            if (p == -1)
                over = true;
            else{
                this->TKey[pos] = this->TKey[p];
                previous = pp;
                pos = p;
            }
        }while (!over);
        if (previous == -1){
            int index = 0;
            while (index < this->m && previous == -1){
                if (this->next[index] == pos)
                    previous = index;
                else
                    index++;
            }
        }
        if (previous != -1)
            this->next[previous] = this->next[pos];
        this->TKey[pos] = -1;
        this->next[pos] = -1;
        if (pos < this->firstEmpty)
            this->firstEmpty = pos;
    }
    this->length--;
    return true;
}


bool SortedBag::search(TComp elem) const {
    if (this->length == 0)
        return false;
    int pos = this->hash(elem);
    while (pos != -1) {
        if (this->TKey[pos] == elem) {
            return true;
        }
        pos = this->next[pos];
    }
    return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
    if (this->length == 0)
        return 0;
    int pos = this->hash(elem);
    int count = 0;
    while (pos != -1) {
        if (this->TKey[pos] == elem) {
            count++;
        }
        pos = this->next[pos];
    }
    return count;
}


int SortedBag::size() const {
    return this->length;
}


bool SortedBag::isEmpty() const {
    return this->length == 0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

int SortedBag::removeAll(){
    int count = 0;
    for (int i = 0; i < this->capacity; i++)
        if (this->next[i] != -1){
            count += this->nrOccurrences(this->TKey[i]);
            this->remove(this->TKey[i]);
        }
    return count;
}

SortedBag::~SortedBag() {
    delete[] this->TKey;
    delete[] this->next;
}
