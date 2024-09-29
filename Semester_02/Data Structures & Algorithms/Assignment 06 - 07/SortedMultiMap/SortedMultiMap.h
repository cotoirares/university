#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);
typedef TValue(*Transformer)(TKey, TValue);

class SortedMultiMap {
	friend class SMMIterator;
    private:
        struct BSTNode{
            TKey key;
            TValue* values;
            int valueCount;
            int capacity;
            BSTNode* left;
            BSTNode* right;
            void addValue(TValue value){
                if(valueCount == capacity){
                    capacity *= 2;
                    auto* newValues = new TValue[capacity];
                    for(int i = 0; i < valueCount; i++){
                        newValues[i] = values[i];
                    }
                    delete[] values;
                    values = newValues;
                }
                values[valueCount++] = value;
            };
            bool removeValue(TValue value){
                for(int i = 0; i < valueCount; i++){
                    if(values[i] == value){
                        for(int j = i; j < valueCount - 1; j++){
                            values[j] = values[j + 1];
                        }
                        valueCount--;
                        return true;
                    }
                }
                return false;
            };
        };
        BSTNode* root;
        Relation r;
        int length;
        // O(n)
        BSTNode* insertRecursively(BSTNode* node, TKey key, TValue value){
            if(node == nullptr){
                auto* newNode = new BSTNode;
                newNode->key = key;
                newNode->values = new TValue[1];
                newNode->values[0] = value;
                newNode->valueCount = 1;
                newNode->capacity = 1;
                newNode->left = nullptr;
                newNode->right = nullptr;
                this->length++;
                return newNode;
            }
            if(r(node->key, key)){
                node->left = insertRecursively(node->left, key, value);
            }else if(r(key, node->key)){
                node->right = insertRecursively(node->right, key, value);
            }else{
                node->addValue(value);
                this->length++;
            }
            return node;
        };
        // search -> complexitate O(h)
        BSTNode* searchRecursively(BSTNode* node, TKey key) const{
            if(node == nullptr){
                return nullptr;
            }
            if(node->key == key){
                return node;
            }
            if(r(node->key, key)){
                return searchRecursively(node->left, key);
            }
            else
                return searchRecursively(node->right, key);
        };
        BSTNode* findMin(BSTNode* node){
            if(node == nullptr){
                return nullptr;
            }
            if(node->left == nullptr){
                return node;
            }
            return findMin(node->left);
        };
        // O(n)
        BSTNode* findParent(BSTNode* node){
            if(node == nullptr){
                return nullptr;
            }
            BSTNode* parent = nullptr;
            BSTNode* current = this->root;
            while(current != node){
                if(r(node->key, current->key)){
                    parent = current;
                    current = current->left;
                }else{
                    parent = current;
                    current = current->right;
                }
            }
            return parent;
        };
        BSTNode* findSuccessor(BSTNode* node){
            if(node == nullptr){
                return nullptr;
            }
            if(node->right != nullptr){
                return findMin(node->right);
            }
            BSTNode* parent = nullptr;
            BSTNode* current = this->root;
            while(current != node){
                if(r(node->key, current->key)){
                    parent = current;
                    current = current->left;
                }else{
                    current = current->right;
                }
            }
            return parent;
        };
        BSTNode* removeRecursively(BSTNode* node, TKey key, TValue value){
            if(node == nullptr){
                return nullptr;
            }
            if(node->key == key){
                if(node->valueCount == 1){
                    if(node->left == nullptr && node->right == nullptr){
                        delete[] node->values;
                        delete node;
                        this->length--;
                        return nullptr;
                    }
                    if(node->left == nullptr){
                        BSTNode* right = node->right;
                        delete[] node->values;
                        delete node;
                        this->length--;
                        return right;
                    }
                    if(node->right == nullptr){
                        BSTNode* left = node->left;
                        delete[] node->values;
                        delete node;
                        this->length--;
                        return left;
                    }
                    BSTNode* successor = findSuccessor(node->right);
                    node->key = successor->key;
                    node->values = successor->values;
                    node->valueCount = successor->valueCount;
                    node->capacity = successor->capacity;
                    node->right = removeRecursively(node->right, successor->key, successor->values[0]);
                    return node;
                }
                if(node->removeValue(value)){
                    this->length--;
                }
                return node;
            }
            if(r(node->key, key)){
                node->left = removeRecursively(node->left, key, value);
            }else{
                node->right = removeRecursively(node->right, key, value);
            }
            return node;
        };
        BSTNode* formNewBSTNode(BSTNode* node){
            if(node == nullptr){
                return nullptr;
            }
            auto* newNode = new BSTNode;
            newNode->key = node->key;
            newNode->values = new TValue[node->valueCount];
            for(int i = 0; i < node->valueCount; i++){
                newNode->values[i] = node->values[i];
            }
            newNode->valueCount = node->valueCount;
            newNode->capacity = node->capacity;
            newNode->left = formNewBSTNode(node->left);
            newNode->right = formNewBSTNode(node->right);
            return newNode;
        };


    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // replaces the value of every key, with the result given by a function invoked on the pair
    void replaceAll(Transformer t);

    // destructor
    ~SortedMultiMap();
};
