#pragma once
#include "SortedBag.h"
#include <utility>

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

    std::pair<TComp, int> currentEl;
    int currentIndex;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

