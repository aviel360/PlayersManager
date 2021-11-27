#ifndef BTREENODE_H_
#define BTREENODE_H_

int max(int x, int y);

template <class T>
class BTreeNode{
    T value;
    BTreeNode<T>* r_child;
    BTreeNode<T>* l_child;
    int height;

public:
    explicit BTreeNode(const T& _value) : value(_value), r_child(nullptr), l_child(nullptr), height(0) {}
    ~BTreeNode() = default;
    BTreeNode(const BTreeNode& node) = default;
    BTreeNode* goLeft(){
        return l_child;
    }
    BTreeNode* goRight(){
        return r_child;
    }
    T getValue(){
        return value;
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
    int getHeight() {
        return height;
    }
    int getHeight(BTreeNode* node){
        if (node == nullptr){
            return -1;
        }
        return node->getHeight();
    }
    
};
int max(int x, int y){
    return x > y ? x : y;
}

#endif