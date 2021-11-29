//
// Created by Sofia Blyufer on 29/11/2021.
//

#include "PlayersManager.h"

PlayersManager* PlayersManager::Init() {
    try {
        PlayersManager* DS = new PlayersManager;
        return DS;
    }
    catch (const std::bad_alloc& e)
    {
        return nullptr;
    }
}

void PlayersManager::addGroup(const int& id) {
    try {
        Group group(id);
        eGroup.insert(group);
    }
    catch (const InvalidInput& e) {
        return ;
    }
    catch (const ValueExists& e) {
        return ;
    }

}
void addPlayer(const int& player_id, const int& group_id, const int& level);
void removePlayer(const int& player_id);
void replaceGroup(const int& group_id, const int& replace_id);
void increaseLevel(const int& player_id, const int& new_level);
void getAllPlayersByLevel(const int& group_id, int** Players, int* numOfPlayers);
void getGroupsHighestLevel(const int& numOfGroups, int** Players);
void Quit();