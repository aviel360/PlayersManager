#include <iostream>
#include "AVLTree.h"
#include "BTreeNode.h"
#include "Player.h"

int main() {
    AVLTree<int> test(1);
    test.inOrder();
    test.insert(1);
    test.insert(2);
    test.insert(3);
    test.insert(4);
    test.inOrder();
    test.insert(1);
    test.inOrder();
    test.remove(1);
    test.inOrder();
    test.remove(4);
    test.inOrder();
    test.insert(4);
    test.insert(7);
    test.insert(6);
    test.insert(5);
    test.insert(15);
    test.insert(12);
    test.insert(11);
    test.inOrder();
    test.remove(7);
    test.remove(11);
    test.remove(12);
    test.remove(15);
    test.inOrder();
    return 0;
}
