#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    this->r = r;
    this->root = nullptr;
    this->length = 0;
}

void SortedMultiMap::add(TKey c, TValue v) {
    if(this->root == nullptr){
        this->root = new BSTNode;
        this->root->key = c;
        this->root->values = new TValue[1];
        this->root->values[0] = v;
        this->root->valueCount = 1;
        this->root->capacity = 1;
        this->root->left = nullptr;
        this->root->right = nullptr;
        this->length++;
        return;
    }
    BSTNode* node = this->root;
    while(true){
        if(node->key == c){
            if(node->valueCount == node->capacity){
                node->capacity *= 2;
                auto* newValues = new TValue[node->capacity];
                for(int i = 0; i < node->valueCount; i++){
                    newValues[i] = node->values[i];
                }
                delete[] node->values;
                node->values = newValues;
            }
            node->values[node->valueCount] = v;
            node->valueCount++;
            this->length++;
            return;
        }
        if(r(node->key, c)){
            if(node->right == nullptr){
                node->right = new BSTNode;
                node->right->key = c;
                node->right->values = new TValue[1];
                node->right->values[0] = v;
                node->right->valueCount = 1;
                node->right->capacity = 1;
                node->right->left = nullptr;
                node->right->right = nullptr;
                this->length++;
                return;
            }
            node = node->right;
        }else{
            if(node->left == nullptr){
                node->left = new BSTNode;
                node->left->key = c;
                node->left->values = new TValue[1];
                node->left->values[0] = v;
                node->left->valueCount = 1;
                node->left->capacity = 1;
                node->left->left = nullptr;
                node->left->right = nullptr;
                this->length++;
                return;
            }
            node = node->left;
        }
    }
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> values;
    BSTNode* node = this->root;
    while(node != nullptr){
        if(node->key == c){
            for(int i = 0; i < node->valueCount; i++){
                values.push_back(node->values[i]);
            }
            return values;
        }
        if(r(node->key, c)){
            node = node->right;
        }else{
            node = node->left;
        }
    }
    return values;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    BSTNode* node = this->root;
    BSTNode* parent = nullptr;
    while(node != nullptr){
        if(node->key == c){
            if(node->removeValue(v)){
                this->length--;
                if(node->valueCount == 0){
                    if(parent == nullptr){
                        this->root = nullptr;
                    }else{
                        if(parent->left == node){
                            parent->left = nullptr;
                        }else{
                            parent->right = nullptr;
                        }
                    }
                    delete[] node->values;
                    delete node;
                }
                return true;
            }
            return false;
        }
        parent = node;
        if(r(node->key, c)){
            node = node->right;
        }else{
            node = node->left;
        }
    }
    return false;
}


int SortedMultiMap::size() const {
    return this->length;
}

bool SortedMultiMap::isEmpty() const {
    return this->length == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

void SortedMultiMap::replaceAll(Transformer t) {
    vector<BSTNode*> nodes;
    nodes.push_back(this->root);
    while(!nodes.empty()){
        BSTNode* node = nodes.back();
        nodes.pop_back();
        if(node->left != nullptr){
            nodes.push_back(node->left);
        }
        if(node->right != nullptr){
            nodes.push_back(node->right);
        }
        for(int i = 0; i < node->valueCount; i++){
            node->values[i] = t(node->key, node->values[i]);
        }
    }

}

SortedMultiMap::~SortedMultiMap() {
    if (this->root == nullptr){
        return;
    }
    vector<BSTNode*> nodes;
    nodes.push_back(this->root);
    while(!nodes.empty()){
        BSTNode* node = nodes.back();
        nodes.pop_back();
        if(node->left != nullptr){
            nodes.push_back(node->left);
        }
        if(node->right != nullptr){
            nodes.push_back(node->right);
        }
        delete[] node->values;
        delete node;
    }
}
