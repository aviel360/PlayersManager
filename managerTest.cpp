#include "PlayersManager.h"
#include <iostream>
#include <assert.h>

int main() {
    PlayersManager squid = PlayersManager(); // starting new group
    int** Players;
    int* size;
    squid.getAllPlayersByLevel(-1, Players, size);
    assert(*Players == NULL && *size == 0);
    assert(squid.getHighestLevel(-1) == -1);
    try{
        squid.increaseLevel(5,2);
    }
    catch(ValueNotExists& e){
        std::cout << e.what() << std::endl;
    }
    try{
        squid.removePlayer(2);
    }
    catch(ValueNotExists& e){
        std::cout << e.what() << std::endl;
    }
    try{
        squid.addPlayer(2, 2, 0);
    }
    catch(ValueNotExists& e){
        std::cout << e.what() << std::endl;
    }
    squid.addGroup(3); // adding group 3, 0 players
    squid.getAllPlayersByLevel(3, Players, size);
    assert(*Players == NULL && size == 0);
    squid.addPlayer(3, 3, 3);
    squid.addPlayer(2,3,3);
    squid.addGroup(2);
    squid.addPlayer(1,3,0);
    squid.getAllPlayersByLevel(3, Players, size);
    assert(*size == 3 && *Players != NULL && *Players[0] == 2 && *Players[1] == 3 && *Players[2] == 1);
}
