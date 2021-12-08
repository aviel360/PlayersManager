#ifndef PLAYERSMANAGER_BTREENODE_H_
#define PLAYERSMANAGER_BTREENODE_H_

#include <iostream>

template <class T>
class BTreeNode{
    std::shared_ptr<T> value;
    BTreeNode<T>* r_child;
    BTreeNode<T>* l_child;
    int height;

    int max(const int x, const int y){
        return x > y ? x : y;
    }

public:
    explicit BTreeNode(const T& _value) : value(std::make_shared(_value)), r_child(nullptr), l_child(nullptr), height(0) {}
    ~BTreeNode() = default;
    BTreeNode(const BTreeNode& node) = default;
    BTreeNode* goLeft(){
        return l_child;
    }
    BTreeNode* goRight(){
        return r_child;
    }
    T& getValue(){
        return *(this->value);
    }
    std::shared_ptr<T> getPointer(){
        return this->value;
    }
    void setValue(const T& _value){
        value = _value;
    }
    void setHeight(){
        height = max(getHeight(l_child), getHeight(r_child)) + 1;
    }
    void setLChild(BTreeNode* _l_child){
        l_child = _l_child;
        setHeight();
    }
    void setRChild(BTreeNode* _r_child){
        r_child = _r_child;
        setHeight();
    }
    int getHeight() const{
        return height;
    }
    int getHeight(BTreeNode const * const node) const{
        if (node == nullptr){
            return -1;
        }
        return node->getHeight();
    }
    
};


#endif