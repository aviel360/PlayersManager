#ifndef BTREENODE_H_
#define BTREENODE_H_

template <class T>
class BTreeNode{
    T value;
    BTreeNode* r_child, l_child;
    int height;

    int max(int x, int y){
        return x > y ? x : y;
    }
public:
    explicit BTreeNode(const T& _value) : value(_value), r_child(nullptr), l_child(nullptr), height(0);
    ~BTreeNode() = default;
    BTreeNode(const BTreeNode& node) = default;
    BTreeNode* goLeft(){
        return l_child;
    }
    BTreeNode* goRight(){
        return r_child;
    }
    void setHeight(){
        height = max(getLHeight(), getRHeight()) + 1;
    }
    void setLChild(BTreeNode* _l_child){
        l_child = _l_child;
        setHeight();
    }
    void setRChild(BTreeNode* _r_child){
        r_child = _r_child;
        setHeight();
    }
    int getHeight() {
        return node->height;
    }
    int getHeight(BTreeNode* node){
        if (node == nullptr){
            return 0;
        }
        return node->getHeight();
    }
};

#endif