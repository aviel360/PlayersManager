#include <iostream>
#include "AVLTree.h"
#include "BTreeNode.h"
#include "Player.h"
#include "Group.h"
#include "Exceptions.h"

void check(AVLTree<int> tree)
{
    printf("hi ");
    try{
        tree.insert(6);
    }
    catch(ValueExists& ve){
        std::cout << ve.what() << std::endl;
    }
}

int main() {
    AVLTree<int> test(1);
    try{
        test.insert(1);
    }
    catch(ValueExists& ve){
        std::cout << ve.what() << std::endl;
    }
    test.insert(2);
    test.insert(3);
    test.insert(4);
    try{
        test.insert(1);
    }
    catch(ValueExists& ve){
        std::cout << ve.what() << std::endl;
    }
    test.remove(1);
    test.remove(4);
    test.insert(4);
    test.insert(7);
    test.insert(6);
    test.insert(5);
    test.insert(15);
    test.insert(12);
    test.insert(11);
    test.remove(7);
    test.remove(11);
    test.remove(12);
    test.remove(15);
    check(test);
    
    Group group1(1);
    std::cout << group1.getNumOfPlayers() << " " << group1.getStrongestPlayer();
    return 0;
}
