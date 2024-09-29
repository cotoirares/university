#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {
// ADT Matrix – represented as a sparse matrix, using a double linked list represented on array with <line, column, value> triples (value ≠ 0), ordered lexicographically considering the line and column of every element.
private:
    struct data {
        int line, column;
        TElem value;
    };
    struct Node {
        data info;
        int next;
        int prev;
    };
    Node* elements;
    int capacity;
    int head;
    int tail;
    int firstEmpty;
    int nrLinesMatrix;
    int nrColumnsMatrix;
    void resize(){
        Node* newElements = new Node[2 * capacity];
        for (int i = 0; i < capacity; i++)
            newElements[i] = elements[i];
        for (int i = capacity; i < 2 * capacity - 1; i++)
            newElements[i].next = i + 1;
        newElements[2 * capacity - 1].next = -1;
        delete[] elements;
        elements = newElements;
        firstEmpty = capacity;
        capacity *= 2;
    }

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

};
