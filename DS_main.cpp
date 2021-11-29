//
// Created by Sofia Blyufer on 30/11/2021.
//
#include "PlayersManager.h"

int main() {

    PlayersManager* p1 = PlayersManager::Init();
    (*p1).addGroup(1);
    (*p1).addPlayer(2,1,0);
    (*p1).addGroup(3);
    return 0;
}

