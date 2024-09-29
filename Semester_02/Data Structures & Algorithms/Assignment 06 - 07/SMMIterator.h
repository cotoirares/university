#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);
    int currentIndex;
    struct dyn_arr{
        pair<TKey, TValue>* pairs;
        int capacity;
        int length;
    };
    dyn_arr elements;
    void inOrderTraversal(SortedMultiMap::BSTNode* node){
        if(node == nullptr){
            return;
        }
        inOrderTraversal(node->left);
        for(int i = 0; i < node->valueCount; i++){
            if (this->elements.capacity == this->elements.length) {
                this->elements.capacity *= 2;
                auto* newPairs = new TElem[this->elements.capacity];
                for (int j = 0; j < this->elements.length; j++) {
                    newPairs[j] = this->elements.pairs[j];
                }
                delete[] this->elements.pairs;
                this->elements.pairs = newPairs;
            }
            this->elements.pairs[this->elements.length++] = make_pair(node->key, node->values[i]);
        }
        inOrderTraversal(node->right);
    }


public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

