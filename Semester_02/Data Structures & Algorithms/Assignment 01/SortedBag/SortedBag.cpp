#include "SortedBag.h"
#include "SortedBagIterator.h"
using namespace std;
#include <utility>
#include <algorithm>

SortedBag::SortedBag(Relation r) {
    this->relation = r;
    this->capacity = 10;
    this->length = 0;
    this->sortedBag = new std::pair<TComp, int>[this->capacity];
}

int SortedBag::get_index_to_insert(TComp e) {
    if (this->relation(2, 3) == true){
        int left = 0;
        int right = this->length - 1;
        while (left <= right){
            int mid = (left + right) / 2;
            if (this->sortedBag[mid].first == e)
                return mid;
            if (this->relation(this->sortedBag[mid].first, e) == true)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }
    else{
        int left = 0;
        int right = this->length - 1;
        while (left <= right){
            int mid = (left + right) / 2;
            if (this->sortedBag[mid].first == e)
                return mid;
            if (this->relation(this->sortedBag[mid].first, e) == true)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;

    }

}

void SortedBag::add(TComp e) {
    int index_to_insert;
    bool inBag = false;
    for (int i = 0; i < this->length; ++i)
        if (this->sortedBag[i].first == e){
            this->sortedBag[i].second++;
            this->length++;
            inBag = true;
            break;
        }
    if (!inBag){
        if (this->length >= this->capacity) {
            this->capacity *= 2;
            std::pair<TComp, int>* newSortedBag = new std::pair<TComp, int>[this->capacity];
            for (int i = 0; i < this->length; ++i)
                newSortedBag[i] = this->sortedBag[i];
            delete[] this->sortedBag;
            this->sortedBag = newSortedBag;
        }
        index_to_insert = get_index_to_insert(e);
        for (int i = this->length; i > index_to_insert; --i)
            this->sortedBag[i] = this->sortedBag[i - 1];
        this->sortedBag[index_to_insert] = make_pair(e, 1);
        this->length++;
    }
}


bool SortedBag::remove(TComp e) {
    if (this->length == 0)
        return false;
    int index = -1;
    bool oneapp = false;
    for (int i = 0; i < this->length;++i)
        if (this->sortedBag[i].first == e) {
            index = i;
            if (this->sortedBag[i].second <= 1)
                oneapp = true;
        }
    if (index == -1)
	    return false;
    else{
        if (!oneapp){
            this->sortedBag[index].second--;
        }
        else {
            for (int i = index; i < this->length - 1; ++i)
                this->sortedBag[i] = this->sortedBag[i + 1];
        }
        this->length--;
        return true;
    }
}


bool SortedBag::search(TComp elem) const {
    if (this->length == 0)
        return false;
	for (int i=0;i<this->length;++i)
        if (this->sortedBag[i].first == elem)
            return true;
    return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
    for (int i=0;i<this->length;++i)
        if (this->sortedBag[i].first == elem)
            return this->sortedBag[i].second;
	return 0;
}



int SortedBag::size() const {
    return this->length;
}


bool SortedBag::isEmpty() const {
	if (this->length == 0)
        return true;
	return false;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

int SortedBag::removeAllOccurrences(TComp elem) {
    int count = 0;
    for (int i = 0; i < this->length; ++i)
        if (this->sortedBag[i].first == elem) {
            count += this->sortedBag[i].second;
            for (int j = i; j < this->length - 1; ++j)
                this->sortedBag[j] = this->sortedBag[j + 1];
            this->length-=count;
            break;
        }
    return count;
}


SortedBag::~SortedBag() {
	delete sortedBag;
}
