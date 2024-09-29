#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

#include <exception>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
    /// sortedBag - having elements of type TComp, represented as a dynamic array of <element, frequency> pairs, sorted using a relation on the elements

    std::pair<TComp, int>* sortedBag;
    int capacity;
    int length;
    Relation relation;

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;
    int get_index_to_insert(TComp e);
    int removeAllOccurrences(TComp elem);

	//destructor
	~SortedBag();
};