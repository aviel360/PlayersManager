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
    void RR(BTreeNOde* node);
    void LL(BTreeNOde* node);

public:
    int getBalance(BTreeNode* node){
        int l,r;
        if (node -> goLeft() == nulptr)
        {
            l = 0;
        }
        else{
            l = node -> getLHeight();
        }
        if (node -> goRight() == nullptr)
        {
            r = 0;
        }
        else{
            r = node -> getRHeight();
        }

        return (l-r);
    }
    void insert(const T& value);
    void delete(const T& value);
    BTreeNode* find(const T& value);
    void inOrder();
};
#endif //PLAYERSMANAGER_AVLTREE_H
