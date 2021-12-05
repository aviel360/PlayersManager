//
// Created by Sofia Blyufer and Aviel Cohen on 26/11/2021.
//

#ifndef PLAYERSMANAGER_AVLTREE_H
#define PLAYERSMANAGER_AVLTREE_H

#include "BTreeNode.h"
#include "Exceptions.h"
#include <math.h>

template<class T>
class AVLTree{
    BTreeNode<T>* source;

        /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T>* getMinValue(BTreeNode<T>* _source){
        while(_source->goLeft() != nullptr){
            _source = _source->goLeft();
        }
        return _source;
    }
        /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T>* getMaxValue(BTreeNode<T>* _source){
        while(_source->goRight() != nullptr){
            _source = _source->goRight();
        }
        return _source;
    }
    /**
     *
     * @param node
     */
    void removeBTreeNode(BTreeNode<T>* node)
    {
        if (node != nullptr)
        {
            removeBTreeNode(node->goRight());
            removeBTreeNode(node->goLeft());
            delete node;
        }
    }
    /**
     *
     * @param node
     * @return
     */
    BTreeNode<T>* copy(BTreeNode<T>* node) {
        if( node  != nullptr )
        {
            BTreeNode<T>* base = new BTreeNode<T>(node->getValue());
            base->setLChild(copy(node->goLeft()));
            base->setRChild(copy(node->goRight()));
            return base ;
        }

        return nullptr ;
    }
    /**
     *
     * @param value
     * @param _source
     * @return
     */
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
    /**
     *
     * @param value
     * @param _source
     * @return
     */
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
    /**
     *
     * @param _source
     * @return
     */
    int getBalance(BTreeNode<T>* _source){
        if(_source == nullptr){
            return 0;
        }
        return _source->getHeight(_source->goLeft()) - _source->getHeight(_source->goRight());
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T>* leftRoll(BTreeNode<T>* _source){
        BTreeNode<T>* new_root = _source->goRight();
        _source->setRChild(new_root->goLeft());
        new_root->setLChild(_source);
        return new_root;
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T>* rightRoll(BTreeNode<T>* _source){
        BTreeNode<T>* new_root = _source->goLeft();
        _source->setLChild(new_root->goRight());
        new_root->setRChild(_source);
        return new_root;
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T>* LL(BTreeNode<T>* _source){
        return rightRoll(_source);
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T>* LR(BTreeNode<T>* _source){
        _source = rightRoll(_source);
        return leftRoll(_source);
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T>* RR(BTreeNode<T>* _source){
        return leftRoll(_source);
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T>* RL(BTreeNode<T>* _source){
        _source = leftRoll(_source);
        return rightRoll(_source);
    }
    /**
     *
     * @param _source
     */
    void inOrderToArrayRecursive(BTreeNode<T>* _source, int* array, int i){
        if(_source != nullptr){
            inOrderRecursive(_source->goLeft(), array, i);
            array[i++] = _source->getValue();
            inOrderRecursive(_source->goRight(), array, i);
        }
    }
    template <class Func>
    void inOrderRecursive(BTreeNode<T>* _source, Func func)
    {
        if(_source != nullptr)
        {
            inOrderRecursive(_source->goLeft(), func);
            func(_source->getValue());
            inOrderRecursive(_source->goRight(), func);
        }
    }
    AVLTree<T> completeTree(BTreeNode<T> _source, int h) {
        if (h < 0)
        {
            return;
        }
        BTreeNode<T>* tmp1 = new BTreeNode<T>;
        _source.setRChild(tmp1);
        BTreeNode<T>* tmp2 = new BTreeNode<T>;
        _source.setRChild(tmp2);
        h--;
        completeTree(tmp1, h);
        completeTree(tmp2, h); //TODO
    }

    int reverseInOrder(BTreeNode<T>* _source, int n)
    {
        if(_source != nullptr || n==0)
        {
            n = inOrderRecursive(_source->goRight(), n);
            if ( _source->goLeft() == nullptr)
            {
                //remove - source disappears issue

            }
            inOrderRecursive(_source->goLeft(), n);
            return n-1;
        }
        return n;
    }

public:

    AVLTree(): source(nullptr){}

    explicit AVLTree(const T& _value) : source(new BTreeNode<T>(_value)) {}

    ~AVLTree() {
        if(source != nullptr)
        {
            removeBTreeNode(source);
        }
    }

    AVLTree(const AVLTree& other) {

        source = copy(other.source);

    }

    AVLTree& operator=(const AVLTree& other)
    {
        if (this != &other)
        {
            removeBTreeNode(source);
            source = copy(other.source);
        }
        return *this;
    }

    void insert(const T& value){
        if (find(value) != nullptr)
        {
            throw ValueExists();
        }
        source = insertRecursive(value, source);
    }

    void remove(const T& value){
        if (find(value) == nullptr)
        {
            throw ValueNotExists();
        }
        source = removeRecursive(value, source);
    }
    void inOrderToArray(int* array){
        if(array == nullptr){
            throw InvalidInput();
        }
        inOrderToArrayRecursive(source, array, 0);
    }
    template <class Func>
    void inOrder(const Func& f) {
        inOrderRecursive(source, f);
    }

    bool exists(const T& _value){
        BTreeNode<T>* result = find(_value);
        if (result == nullptr)
        {
            return false;
        }
        return true;
    }

    BTreeNode<T>* find(const T& _value){
        BTreeNode<T>* _source = source;
        while(_source != nullptr){
            if(_source->getValue() < _value){
                _source = _source->goRight();
            }
            else if(_source->getValue() == _value){
                return source;
            }
            else{
                _source = _source->goLeft();
            }
        }
        return nullptr;
    }

    T& get(const T& _value){
        BTreeNode<T>* node = find(_value);
        if (node == nullptr)
        {
            throw ValueNotExists();
        }
        return node->getValue();
    }
        /**
     *
     * @param _source
     * @return
     */
    T& getMinValue(){
        return getMinValue(source)->getValue();
    }
        /**
     *
     * @param _source
     * @return
     */
    T& getMaxValue(){
        return getMaxValue(source)->getValue();
    }

    AVLTree& createEmptyTree(const int& n) {
        int h = ceil(log2(n+1)) -1;
        AVLTree<T> empty;
        empty = empty.completeTree(h);
        reverseInOrder(empty.source, pow(2,h+1)-1-n);
        return empty;
    }
};

#endif //PLAYERSMANAGER_AVLTREE_H
