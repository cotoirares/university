#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;
/// ADT SortedBag – using a hashtable with coalesced chaining in which the elements are stored. If an element appears multiple times, it will be stored multiple times in the hashtable.
/// In the constructor of the iterator create a sorted array of the elements and use that array for iterating.
class SortedBag {
	friend class SortedBagIterator;

private:
    Relation r;
    int m;
    int capacity;
    int length;
    int* TKey;
    int* next;
    int firstEmpty;
    int hash(TComp e) const{
        if (e < 0)
            return (-e) % m;
        return e % m;
    };
    void resize(){
        int* newTKey = new int[2 * capacity];
        int* newNext = new int[2 * capacity];
        for (int i = 0; i < 2 * capacity; i++)
            newNext[i] = i + 1;
        newNext[2 * capacity - 1] = -1;
        for (int i = 0; i < capacity; i++)
            newTKey[i] = TKey[i];
        delete[] TKey;
        delete[] next;
        TKey = newTKey;
        next = newNext;
        firstEmpty = capacity;
        capacity *= 2;
    };
    void changeFirstEmpty(){
        this->firstEmpty = this->firstEmpty + 1;
        while (this->firstEmpty < this->m && this->TKey[this->firstEmpty] != -1)
            this->firstEmpty = this->firstEmpty + 1;
    };

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

    //removes completely all the elements that appear multiple times in the SortedBag. Returns the number of removed elements
    int removeAll();

	//destructor
	~SortedBag();
};