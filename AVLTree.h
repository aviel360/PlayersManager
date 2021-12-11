//
// Created by Sofia Blyufer and Aviel Cohen on 26/11/2021.
//

#ifndef PLAYERSMANAGER_AVLTREE_H
#define PLAYERSMANAGER_AVLTREE_H

#include "BTreeNode.h"
#include "Exceptions.h"
#include <cmath>

template<class T, class K>
class AVLTree{
    BTreeNode<T,K>* source;

        /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T,K>* getMinValue(BTreeNode<T,K>* _source){
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
    BTreeNode<T,K>* getMaxValue(BTreeNode<T,K>* _source){
        while(_source->goRight() != nullptr){
            _source = _source->goRight();
        }
        return _source;
    }
    /**
     *
     * @param node
     */
    void removeBTreeNode(BTreeNode<T,K>* node)
    {
        if (node != nullptr)
        {
            removeBTreeNode(node->goRight());
            removeBTreeNode(node->goLeft());
            delete node;
            node = nullptr;
        }
    }
    /**
     *
     * @param node
     * @return
     */
    BTreeNode<T,K>* copy(BTreeNode<T,K>* node) {
        if( node  != nullptr )
        {
            BTreeNode<T,K>* base = new BTreeNode<T,K>(node->getValue(), node->getKey());
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
    BTreeNode<T,K>* insertRecursive(const T& _value, const K& _key, BTreeNode<T,K>* _source){
        if(_source == nullptr)
        {
            BTreeNode<T,K>* node = new BTreeNode<T,K>(_value, _key);
            _source = node;
            return _source;
        }
        if (_key < _source ->getKey())
        {
            _source -> setLChild(insertRecursive(_value, _key, _source -> goLeft())) ;
        }
        else if (_key > _source -> getKey()){
            _source -> setRChild(insertRecursive(_value, _key, _source -> goRight()));
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
    BTreeNode<T,K>* removeRecursive(const K& _key, BTreeNode<T,K>* _source){
        if(_source == nullptr){
            return nullptr;
        }
        if(_key < _source->getKey()){
            _source->setLChild(removeRecursive(_key, _source->goLeft()));
        }
        else if(_source->getKey() < _key){
            _source->setRChild(removeRecursive(_key, _source->goRight()));
        }
        else{
            if(_source->goRight() == nullptr || _source->goLeft() == nullptr){
                BTreeNode<T,K>* temp = _source->goRight() == nullptr ? _source->goLeft() : _source->goRight();
                if(temp == nullptr){
                    temp = _source;
                    _source = nullptr;
                }
                else{
                    *_source = *temp;
                }
                delete temp;
            }
            else{
                BTreeNode<T,K>* temp = getMinValue(_source->goRight());
                T _value = temp->getValue();
                _source->setValue(_value);
                _source->setKey(temp->getKey());
                _source->setRChild(removeRecursive(temp->getKey(), _source->goRight()));
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
    int getBalance(BTreeNode<T,K>* _source){
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
    BTreeNode<T,K>* leftRoll(BTreeNode<T,K>* _source){
        BTreeNode<T,K>* new_root = _source->goRight();
        _source->setRChild(new_root->goLeft());
        new_root->setLChild(_source);
        return new_root;
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T,K>* rightRoll(BTreeNode<T,K>* _source){
        BTreeNode<T,K>* new_root = _source->goLeft();
        _source->setLChild(new_root->goRight());
        new_root->setRChild(_source);
        return new_root;
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T,K>* LL(BTreeNode<T,K>* _source){
        return rightRoll(_source);
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T,K>* LR(BTreeNode<T,K>* _source){
        _source->setLChild(leftRoll(_source->goLeft()));
        return rightRoll(_source);
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T,K>* RR(BTreeNode<T,K>* _source){
        return leftRoll(_source);
    }
    /**
     *
     * @param _source
     * @return
     */
    BTreeNode<T,K>* RL(BTreeNode<T,K>* _source){
        _source->setRChild(rightRoll(_source->goRight()));
        return leftRoll(_source);
    }

    template <class Func>
    void inOrderRecursive(BTreeNode<T,K>* _source, Func& func)
    {
        if(_source != nullptr)
        {
            inOrderRecursive(_source->goLeft(), func);
            func(_source->getValue(), _source->getKey());
            inOrderRecursive(_source->goRight(), func);
        }
    }
    void completeTree(BTreeNode<T,K>* _source, int h) {
        if (h <= 0){
            return;
        }
        BTreeNode<T,K>* tmp1 = new BTreeNode<T,K>(T(),K(-1));
        _source->setRChild(tmp1);
        BTreeNode<T,K>* tmp2 = new BTreeNode<T,K>(T(),K(-1));
        _source->setLChild(tmp2);
        h--;
        completeTree(tmp1, h);
        completeTree(tmp2, h);
    }

    void reverseInOrder(BTreeNode<T,K>* _source, BTreeNode<T,K>* dad, int& n)
    {
        if(n > 0 && _source != nullptr){
            reverseInOrder(_source->goRight(), _source, n);
            if ( _source->goLeft() == nullptr && _source->goRight() == nullptr)
            {
                if(dad->goRight() == _source){
                    dad->setRChild(nullptr);
                }
                else{
                    dad->setLChild(nullptr);
                }
                delete _source;
                _source = nullptr;
                n--;
                return;
            }
            reverseInOrder(_source->goLeft(), _source, n);
        }
    }

public:

    AVLTree(): source(nullptr){}

    AVLTree(const T& _value,const K& _key) : source(new BTreeNode<T,K>(_value,_key)) {}

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
    BTreeNode<T,K>* getSource(){
        return this->source;
    }
//    void setSource(BTreeNode<T,K>* other){
//        removeBTreeNode(source);
//        source = other;
//    }
    void insert(const T& _value, const K& _key){
        if (find(_key) != nullptr)
        {
            throw ValueExists();
        }
        source = insertRecursive(_value, _key, source);
    }

    void remove(const K& _key){
        if (find(_key) == nullptr)
        {
            throw ValueNotExists();
        }
        source = removeRecursive(_key, source);
    }
    template <class Func>
    void inOrder(Func& f) {
        inOrderRecursive(source, f);
    }

    bool exists(const K& _key){
        BTreeNode<T,K>* result = find(_key);
        if (result == nullptr)
        {
            return false;
        }
        return true;
    }

    BTreeNode<T,K>* find(const K& _key){
        BTreeNode<T,K>* _source = source;
        while(_source != nullptr){
            if(_source->getKey() < _key){
                _source = _source->goRight();
            }
            else if(_source->getKey() == _key){
                return _source;
            }
            else{
                _source = _source->goLeft();
            }
        }
        return nullptr;
    }

    T& get(const K& _key){
        BTreeNode<T,K>* node = find(_key);
        if (node == nullptr)
        {
            throw ValueNotExists();
        }
        return node->getValue();
    }
//    std::shared_ptr<T>& getValue(const K& _key){
//        BTreeNode<T,K>* node = find(_key);
//        if (node == nullptr)
//        {
//            throw ValueNotExists();
//        }
//        return node->getValue();
//    }
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

    void createEmptyTree(const int n) {
        int h = ceil(log2(n+1)) -1;
        insert(T(), K(-1));
        completeTree(source,h);
        int tmp = pow(2,h+1)-n-1;
        reverseInOrder(source, source,tmp);
    }

    
};

#endif //PLAYERSMANAGER_AVLTREE_H
