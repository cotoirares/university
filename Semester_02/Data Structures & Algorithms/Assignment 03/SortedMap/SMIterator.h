#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

	SortedMap::Node* current_node;
    int current_index;


public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

