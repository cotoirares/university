#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    this->nrLinesMatrix = nrLines;
    this->nrColumnsMatrix = nrCols;
    this->capacity = 10;
    this->elements = new Node[capacity];
    for (int i = 0; i < capacity - 1; i++)
        elements[i].next = i + 1;
    elements[capacity - 1].next = -1;
    this->firstEmpty = 0;
    this->head = -1;
    this->tail = -1;
}


int Matrix::nrLines() const {
    return this->nrLinesMatrix;
}


int Matrix::nrColumns() const {
    return this->nrColumnsMatrix;
}


TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= this->nrLinesMatrix || j < 0 || j >= this->nrColumnsMatrix)
        throw exception();
    int current = this->head;
    while (current != -1) {
        if (this->elements[current].info.line == i && this->elements[current].info.column == j)
            return this->elements[current].info.value;
        current = this->elements[current].next;
    }
    return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= this->nrLinesMatrix || j < 0 || j >= this->nrColumnsMatrix)
        throw exception();
    int current = this->head;
    while (current != -1) {
        if (this->elements[current].info.line == i && this->elements[current].info.column == j) {
            TElem oldValue = this->elements[current].info.value;
            this->elements[current].info.value = e;
            return oldValue;
        }
        current = this->elements[current].next;
    }
    if (this->firstEmpty == -1)
        this->resize();
    int newEmpty = this->firstEmpty;
    this->firstEmpty = this->elements[firstEmpty].next;
    this->elements[newEmpty].info.line = i;
    this->elements[newEmpty].info.column = j;
    this->elements[newEmpty].info.value = e;
    this->elements[newEmpty].next = -1;
    if (this->head == -1) {
        this->head = newEmpty;
        this->tail = newEmpty;
        this->elements[newEmpty].prev = -1;
    }
    else {
        this->elements[tail].next = newEmpty;
        this->elements[newEmpty].prev = tail;
        this->tail = newEmpty;
    }
    return NULL_TELEM;
}


