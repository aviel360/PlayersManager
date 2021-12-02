//
// Created by Sofia Blyufer and Aviel Cohen on 29/11/2021.
//

#include "PlayersManager.h"

//PlayersManager* PlayersManager::Init() {
//    PlayersManager* DS = new PlayersManager;
//    return DS;
//}
PlayersManager::PlayersManager() : eGroup(), fGroup(), players(-1), strongestPlayerID(-1){} 
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

void PlayersManager::replaceGroup(const int& group_id, const int& replace_id) {

    if (replace_id <= 0 || group_id <= 0)
    {
        throw InvalidInput();
    }
    if (eGroup.exists(group_id)) //if group is empty
    {
        if (groupExists(replace_id))
        {
            eGroup.remove(group_id);
            return;
        }
        else
        {
            throw ValueNotExists();
        }
    }
    else if (fGroup.exists(group_id))
    {
        if (eGroup.exists(replace_id))
        {
            eGroup.remove(replace_id);
            fGroup.insert(replace_id);
        }
        else if (!fGroup.exists(group_id))
        {
            throw InvalidInput();
        }
        Group g1 = Group(group_id);
        g1 = fGroup.get(g1);
        Group g2 = Group(replace_id);
        g2 = fGroup.get(g2);
        replace(g1,g2);
        fGroup.remove(g1);
    }

}
Group& PlayersManager::findPlayerGroup(int player_id){
    Player player = players.getPlayer(player_id);
    int groupID = player.getGroupID();
    Group _group(groupID);
    return fGroup.get(_group); 
}
bool PlayersManager::groupExists(const int group_id){
    Group current_group = Group(group_id);
    if (!eGroup.exists(current_group) && !fGroup.exists(current_group))
    {
        throw ValueNotExists();
    }
    return true;
}
void PlayersManager::increaseLevel(const int& player_id, const int& new_level) {
    players.getPlayer(player_id).setLevel(new_level);
    findPlayerGroup(player_id).getPlayer(player_id).setLevel(new_level);
}
int PlayersManager::getHighestLevel(const int group_id){
    int player_id = players.getStrongestPlayer();
    if(group_id < 0){
        return player_id;
    }
    return findPlayerGroup(player_id).getStrongestPlayer();
}

void PlayersManager::arrayMalloc(int size, int* sizePtr, int** arrayPtr){
    *sizePtr = size;
    if(size == 0){
        *arrayPtr = nullptr;
    }
    else{
        *arrayPtr = (int*)malloc(sizeof(int)*size);
    }
}
void PlayersManager::getAllPlayersByLevel(const int& group_id, int** Players, int* numOfPlayers) {
    if (Players == nullptr || numOfPlayers == nullptr || group_id == 0){
        throw InvalidInput();
    }
    if (group_id < 0 || eGroup.exists(group_id)){   
        arrayMalloc(players.getNumOfPlayers(), numOfPlayers, Players);
    }
    else if (fGroup.exists(group_id)){
        Group current_group = Group(group_id);
        arrayMalloc(current_group.getNumOfPlayers(), numOfPlayers, Players);
        array my_array(*numOfPlayers, Players);
        fGroup.get(current_group).getLevelTree().inOrder(my_array);
    }
    else{
        throw ValueNotExists();
    }
}
void PlayersManager::getGroupsHighestLevel(const int numOfGroups, int** Players) {
    int* size; //dummy pointer
    arrayMalloc(numOfGroups, size, Players);
    array my_array(numOfGroups, Players);
    try{
        fGroup.inOrder(my_array);
    }
    catch(Index& e){
        *Players = my_array.get();
        return;
    }
}
//void Quit() {
//
//}