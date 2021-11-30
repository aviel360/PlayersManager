//
// Created by Sofia Blyufer and Aviel Cohen on 29/11/2021.
//

#include "PlayersManager.h"

//PlayersManager* PlayersManager::Init() {
//    PlayersManager* DS = new PlayersManager;
//    return DS;
//}

void PlayersManager::addGroup(const int& id) {
    // if (id <= 0) *** maybe only check in library for values? :O maybe idk
    // {
    //     throw InvalidInput();
    // }
    eGroup.insert(Group(id));
}
void PlayersManager::addPlayer(const int& player_id, const int& group_id, const int& level) {
    // if (player_id <= 0 || group_id <= 0 || level < 0) *** maybe only check in library for values? :O maybe idk
    // {
    //     throw InvalidInput();
    // } 
    Group current_group = groupExists(group_id);
    Player current_player = Player(player_id, player_id, level);
    // if (players.playerExists(player_id))  ***we already do this in .insert
    // {
    //     throw ValueExists();
    // }
    if (eGroup.exists(current_group)) //means it's empty
    {
        fGroup.insert(current_group);
        eGroup.remove(current_group);
    }
    fGroup.get(current_group).insertPlayer(player_id, group_id, level);
    players.insertPlayer(player_id, group_id, level);

}
void PlayersManager::removePlayer(const int& player_id) {
    findPlayerGroup(player_id).removePlayer(player_id);
}

void replaceGroup(const int& group_id, const int& replace_id) {

}
Group& PlayersManager::findPlayerGroup(int player_id){
    Player player = players.getPlayer(player_id);
    int groupID = player.getGroupID();
    Group _group(groupID);
    return fGroup.get(_group); 
}
Group& PlayersManager::groupExists(const int group_id){
    Group current_group = Group(group_id);
    if (!eGroup.exists(current_group) && !fGroup.exists(current_group))
    {
        throw ValueNotExists();
    }
    return current_group;
}
void PlayersManager::increaseLevel(const int& player_id, const int& new_level) {
    players.getPlayer(player_id).setLevel(new_level);
    findPlayerGroup(player_id).getPlayer(player_id).setLevel(new_level);
}
int PlayersManager::getHighestLevel(const int group_id, const int player_id){
    if(group_id < 0){
        return players.getStrongestPlayer();
    }
    return findPlayerGroup(player_id).getStrongestPlayer();
}

void PlayersManager::getAllPlayersByLevel(const int& group_id, int** Players, int* numOfPlayers) {
    if (Players == nullptr || numOfPlayers == nullptr || group_id == 0)
    {
        throw InvalidInput();
    }
    if (group_id < 0)
    {
        int n = players.getNumOfPlayers();
        if (n==0)
        {
            *numOfPlayers = 0;
            Players = nullptr;
            return;
        }
        array<int> my_array(n);
        players.getLevelTree().inOrder(add<int> (my_array));
        *Players = my_array.get();
        numOfPlayers = &n;
        return;
    }
    if (eGroup.exists(group_id))
    {
        *numOfPlayers = 0;
        Players = nullptr;
        return;
    }
    if (fGroup.exists(group_id))
    {
        Group current = Group(group_id);
        int n = fGroup.get(current).getNumOfPlayers();
        *numOfPlayers = n;
        array<int> my_array(n);
        fGroup.get(current).getLevelTree().inOrder(add<int> (my_array));
        *Players = my_array.get();
        return;
    }

    throw ValueNotExists();

}
void getGroupsHighestLevel(const int& numOfGroups, int** Players) {

}
//void Quit() {
//
//}