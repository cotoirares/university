#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
    this->length = 0;
    this->capacity = 10;
    this->head = nullptr;
    this->relation = r;
}

TValue SortedMap::add(TKey k, TValue v) {
    Node* newNode = createNode(make_pair(k, v));
    if (head == nullptr) {
        head = newNode;
        length++;
        return NULL_TVALUE;
    }
    else{
        Node* current = head;
        Node* previous = nullptr;
        /// parcurg lista - complexitate O(n)
        while ((current != nullptr && relation(current->data.first, k)) && current->data.first != k){
            previous = current;
            current = current->next;
        }
        if (current == nullptr) {
            previous->next = newNode;
            length++;
            return NULL_TVALUE;
        }
        else if (current->data.first == k) {
            TValue oldValue = current->data.second;
            current->data.second = v;
            return oldValue;
        }
        else {
            if (previous == nullptr) {
                newNode->next = head;
                head = newNode;
                length++;
                return NULL_TVALUE;
            }
            else {
                previous->next = newNode;
                newNode->next = current;
                length++;
                return NULL_TVALUE;
            }
        }
    }
}

TValue SortedMap::search(TKey k) const {
    Node* current = head;
    /// caut in lista - complexitate O(n)
    while (current != nullptr) {
        if (current->data.first == k) {
            return current->data.second;
        }
        current = current->next;
    }
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
    Node* current = head;
    Node* previous = nullptr;
    /// caut in lista - complexitate O(n)
    while (current != nullptr && current->data.first != k) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) {
        return NULL_TVALUE;
    }
    else {
        if (previous == nullptr) {
            head = head->next;
            TValue oldValue = current->data.second;
            delete current;
            length--;
            return oldValue;
        }
        else {
            previous->next = current->next;
            TValue oldValue = current->data.second;
            delete current;
            length--;
            return oldValue;
        }
    }
}

int SortedMap::size() const {
    return this->length;
}

bool SortedMap::isEmpty() const {
	return this->length == 0;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

/// complexitatea O(n)
void SortedMap::filter(Condition cond) {
    Node* current = head;
    Node* previous = nullptr;
    while (current != nullptr) {
        if (!cond(current->data.first)) {
            if (previous == nullptr) {
                head = head->next;
                delete current;
                current = head;
                length--;
            }
            else{
                previous->next = current->next;
                delete current;
                current = previous->next;
                length--;
            }
        }
        else{
            previous = current;
            current = current->next;
        }
    }
}

SortedMap::~SortedMap() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
