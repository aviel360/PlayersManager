//
// Created by Sofia Blyufer and Aviel Cohen on 26/11/2021.
//

#ifndef PLAYERSMANAGER_AVLTREE_H
#define PLAYERSMANAGER_AVLTREE_H
#include "BTreeNode.h"

template<class T>
class AVLTree{
    BTreeNode<T>* source;

    BTreeNode* RR(BTreeNOde* _source); // sofi
    BtreeNode* LL(BTreeNode* _source){
        class BTreeNode* new_source = _source->goRight();
        class BTreeNode* r_child = new_source->goLeft();
        new_source->setLChild(_source);
        _source->setRChild(r_child);
        _source->set
        return new_source;
    }
    BtreeNode* LR(BTreeNode* _source){
        _source->setLChild(RR(source->goLeft()));
        return LL(_source);
    }
    BtreeNode* RL(BTreeNode* _source){
        _source->setRChild(LL(source->goLeft()));
        return RR(_source);
    }

public:
    int getBalance(){
        return getHeight(source->goLeft()) - getHeight(source->goRight());
    }
    void insert(const T& value); // sofi
    void remove(const T& value);
    
    BTreeNode* find(const T& _value){
        class BTreeNode* _source = source;
        while(_source != nullptr){
            if(source->value < _value){
                _source = _source->goRight());
            }
            else if(source->value == _value){
                return source->value;
            }
            else{
                _source = _source->goLeft());
            }
        }
        return nullptr;
    }
    void inOrder(); // sofi
};
#endif //PLAYERSMANAGER_AVLTREE_H
