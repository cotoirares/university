#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator {
    friend class SortedBag;

private:
    const SortedBag &bag;

    SortedBagIterator(const SortedBag &b);

    int capacity;
    int length;
    int *sortedArray;
    int currentElement;

    void merge(int left, int mid, int right, int *aux) {
        int i = left;
        int j = mid + 1;
        int k = left;
        while (i <= mid && j <= right) {
            if (bag.r(bag.TKey[sortedArray[i]], bag.TKey[sortedArray[j]])) {
                aux[k] = sortedArray[i];
                i++;
            } else {
                aux[k] = sortedArray[j];
                j++;
            }
            k++;
        }
        while (i <= mid) {
            aux[k] = sortedArray[i];
            i++;
            k++;
        }
        while (j <= right) {
            aux[k] = sortedArray[j];
            j++;
            k++;
        }
        for (int i = left; i <= right; i++)
            sortedArray[i] = aux[i];
    };

    void mergeSort(int left, int right, int *aux) {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeSort(left, mid, aux);
            mergeSort(mid + 1, right, aux);
            merge(left, mid, right, aux);
        }
    };

    void sortArray() {
        int *aux = new int[capacity];
        mergeSort(0, length - 1, aux);
        delete[] aux;
    };

    void resizeSortedArray() {
        int *newSortedArray = new int[2 * capacity];
        for (int i = 0; i < length; i++)
            newSortedArray[i] = sortedArray[i];
        delete[] sortedArray;
        sortedArray = newSortedArray;
        capacity *= 2;
    };


public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

