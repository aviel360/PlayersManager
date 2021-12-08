#include "Group.h"
#include <iostream>
#include <assert.h>

int main() {
    Group group1(1);
    Group group2(2);
    Group group3(3);
    
    assert(group1.getStrongestPlayer() == -1);
    group1.insertPlayer(552, 2); // insert 552
    try{
        group1.insertPlayer(552, 3); // 552 already exists
    }
    catch(ValueExists& ve){
        std::cout << ve.what() << std::endl;
    }
    group1.insertPlayer(221, 3); // insert 221, strongest player
    assert(group1.getStrongestPlayer() == 221);
    group1.insertPlayer(200, 3); // insert 200
    assert(group1.getStrongestPlayer() == 200);
    group1.insertPlayer(51, 1); // insert 51
    group1.insertPlayer(555, 2); // insert 555
    try{
        group1.removePlayer(2); // player doesnt exist
    }
    catch(ValueNotExists& ve){
        std::cout << ve.what() << std::endl;
    }
    assert(group1.getNumOfPlayers() == 5);
    group2 = group1;
    group1.removePlayer(200);
    assert(group2.getStrongestPlayer() == 200);
    assert(group1.getNumOfPlayers() == 4);
    assert(group1.getStrongestPlayer() == 221);
    assert(group2.getNumOfPlayers() == 5);
}