//
// Created by Sofia Blyufer and Aviel Cohen on 26/11/2021.
//

#ifndef PLAYERSMANAGER_AVLTREE_H
#define PLAYERSMANAGER_AVLTREE_H
#include "BTreeNode.h"

template<class T>
class AVLTree{
    BTreeNode<T>* source;

    BTreeNode<T>* rightRoll(BTreeNode<T>* _source){} // sofi

    BTreeNode<T>* leftRoll(){
        BTreeNode<T>* temp = source;
        source = source->goRight();
        temp->setRChild(source->goLeft());
        source->setLChild(temp);
        return source;
    }

    BTreeNode<T>* getMinValue(BTreeNode<T>* _source){
        while(_source->goLeft() != nullptr){
            _source = _source->goLeft();
        }
        return _source;
    }
    int getBalance(BTreeNode<T>* _source){
        return _source->getHeight(_source->goLeft()) - _source->getHeight(_source->goRight());
    }
public:

    void insert(const T& value); // sofi
    BTreeNode<T>* remove(const T& value, BTreeNode<T>* _source){
        if(_source == nullptr){
            return nullptr;
        }
        else if(value < _source->getValue()){
            _source->setLChild(remove(value, _source->goLeft()));
        }
        else if(source->getValue() < value){
            _source->setRChild(remove(value, _source->goRight()));
        }
        else{
            if(_source->goRight() == nullptr || _source->goLeft() == nullptr){
                BTreeNode<T>* temp = _source->goRight() == nullptr ? _source->goLeft() : _source->goRight();
                if(temp == nullptr){
                    temp = _source;
                    _source = nullptr;
                }
            }
            else{

            }
            
        }
        int balance = getBalance(_source);
        if(balance < -1 && getBalance(_source->goRight()) < 1){
            RR(_source);
        }
        if(balance < -1 && getBalance(_source->goRight()) > 0){
            RL(_source);
        }
        if(balance > 1 &&  getBalance(_source->goLeft()) > -1){
            LL(_source);
        }
        if(balance > 1 && getBalance(_source->goLeft()) < 0){
            LR(_source);
        }
        return _source;
    }

    BTreeNode<T>* find(const T& _value){
        class BTreeNode<T>* _source = source;
        while(_source != nullptr){
            if(source->value < _value){
                _source = _source->goRight();
            }
            else if(source->value == _value){
                return source->value;
            }
            else{
                _source = _source->goLeft();
            }
        }
        return nullptr;
    }
    void inOrder(); // sofi
};
#endif //PLAYERSMANAGER_AVLTREE_H
