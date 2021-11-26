#ifndef BTREENODE_H_
#define BTREENODE_H_

template <class T>
class BTreeNode{
    T value;
    BTreeNode* r_child, l_child;
    int height;
public:
    explicit BTreeNode(const T& _value) : value(_value), r_child(nullptr), l_child(nullptr), height(1);
    ~BTreeNode() = default;
    BTreeNode(const BTreeNode& node) = default;
    BTreeNode* goLeft(){
        return l_child;
    }
    BTreeNode* goRight(){
        return r_child;
    }
    void setHeight(int _height){
        height = _height;
    }
    int getHeight(){
        return height;
    void setLChild(BTreeNode* _l_child){
        l_child = _l_child;
    }
    void setRChild(BTreeNode* _r_child){
        r_child = r_child;
    }
};

#endif