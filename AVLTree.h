//
// Created by Sofia Blyufer on 26/11/2021.
//

#ifndef PLAYERSMANAGER_AVLTREE_H
#define PLAYERSMANAGER_AVLTREE_H
#include "BTreeNode.h"

template<class T>
class AVLTree{
    BTreeNode<T>* source;

    int max(int x, int y){
        return x > y ? x : y;
    }
    void RR(BTreeNOde* node); // sofi
    void LL(BTreeNOde* node);

public:
    int getBalance(){
        return getHeight(source->goLeft()) - getHeight(source->goRight());
    }
    void insert(const T& value); // sofi
    void delete(const T& value);
    BTreeNode* find(const T& value);
    void inOrder(); // sofi
};
#endif //PLAYERSMANAGER_AVLTREE_H
