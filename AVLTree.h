//
// Created by Sofia Blyufer and Aviel Cohen on 26/11/2021.
//

#ifndef PLAYERSMANAGER_AVLTREE_H
#define PLAYERSMANAGER_AVLTREE_H
#include "BTreeNode.h"
template<class T>
BTreeNode<T>* insert(const T& value, BTreeNode<T>* _source);

template<class T>
class AVLTree{
    BTreeNode<T>* source;

public:
    AVLTree(){
        source = nullptr;
    }
    explicit AVLTree(const T& _value) : source(new BTreeNode<T>(_value)) {}
    ~AVLTree() = default;
    AVLTree(const AVLTree& tree); // we need to do this !
    void insert(const T& value){
        source = insertRecursive(value, source);
    }

    void remove(const T& value){
        source = removeRecursive(value, source);
    }
    void inOrder(){
        inOrderRecursive(source);
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
};
    template<class T>
    BTreeNode<T>* getMinValue(BTreeNode<T>* _source){
        while(_source->goLeft() != nullptr){
            _source = _source->goLeft();
        }
        return _source;
    }
    template<class T>
    int getBalance(BTreeNode<T>* _source){
        if(_source == nullptr){
            return 0;
        }
        return _source->getHeight(_source->goLeft()) - _source->getHeight(_source->goRight());
    }
    template<class T>
    BTreeNode<T>* leftRoll(BTreeNode<T>* _source){
        BTreeNode<T>* new_root = _source->goRight();
        _source->setRChild(new_root->goLeft());
        new_root->setLChild(_source);
        return new_root;
    }
    template<class T>
    BTreeNode<T>* rightRoll(BTreeNode<T>* _source){
        BTreeNode<T>* new_root = _source->goLeft();
        _source->setLChild(new_root->goRight());
        new_root->setRChild(_source);
        return new_root;
    }
    template<class T>
    BTreeNode<T>* LL(BTreeNode<T>* _source){
        return rightRoll(_source);
    } 
    template<class T>
    BTreeNode<T>* LR(BTreeNode<T>* _source){
        _source = rightRoll(_source);
        return leftRoll(_source);
    } 
    template<class T>
    BTreeNode<T>* RR(BTreeNode<T>* _source){
        return leftRoll(_source);
    }
    template<class T>
    BTreeNode<T>* RL(BTreeNode<T>* _source){
        _source = leftRoll(_source);
        return rightRoll(_source);
    }
    template<class T>
    BTreeNode<T>* removeRecursive(const T& value, BTreeNode<T>* _source){
        if(_source == nullptr){
            return nullptr;
        }
        else if(value < _source->getValue()){
            _source->setLChild(removeRecursive(value, _source->goLeft()));
        }
        else if(_source->getValue() < value){
            _source->setRChild(removeRecursive(value, _source->goRight()));
        }
        else{
            if(_source->goRight() == nullptr || _source->goLeft() == nullptr){
                BTreeNode<T>* temp = _source->goRight() == nullptr ? _source->goLeft() : _source->goRight();
                if(temp == nullptr){
                    temp = _source;
                    _source = nullptr;
                }
                else{
                   *_source = *temp;
                    _source->setHeight();
                }
                delete temp;
            }
            else{
                BTreeNode<T>* temp = getMinValue(_source->goRight());
                _source->setValue(temp->getValue());
                _source->setRChild(removeRecursive(temp->getValue(), _source->goRight()));
            }
        }
        if(_source == nullptr){
            return _source;
        }
        _source->setHeight();
        int balance = getBalance(_source);
        if(balance < -1 && getBalance(_source->goRight()) < 1){
            return RR(_source);
        }
        if(balance < -1 && getBalance(_source->goRight()) > 0){
            return RL(_source);
        }
        if(balance > 1 &&  getBalance(_source->goLeft()) > -1){
            return LL(_source);
        }
        if(balance > 1 && getBalance(_source->goLeft()) < 0){
            return LR(_source);
        }
        return _source;
    }
    template<class T>
    BTreeNode<T>* insertRecursive(const T& value, BTreeNode<T>* _source){
        if(_source == nullptr)
        {
            BTreeNode<T>* node = new BTreeNode<T>(value);
            _source = node;
            return _source;
        }
        if (value < _source -> getValue())
        {
            _source -> setLChild(insertRecursive(value, _source -> goLeft())) ;
        }
        else if (value > _source -> getValue()){
            _source -> setRChild(insertRecursive(value, _source -> goRight()));
        }
        else {
            return _source;
        }
        int new_balance = getBalance(_source);
        if(new_balance < -1 && getBalance(_source->goRight()) < 1){
            return RR(_source);
        }
        if(new_balance < -1 && getBalance(_source->goRight()) > 0){
            return RL(_source);
        }
        if(new_balance > 1 &&  getBalance(_source->goLeft()) > -1){
            return LL(_source);
        }
        if(new_balance > 1 && getBalance(_source->goLeft()) < 0){
            return LR(_source);
        }
        return _source;
    }
    template<class T>
    void inOrderRecursive(BTreeNode<T>* _source){
        if(_source != nullptr){
            inOrderRecursive(_source->goLeft());
            std::cout << _source->getValue() << " ";
            inOrderRecursive(_source->goRight());
        }
    }

#endif //PLAYERSMANAGER_AVLTREE_H
