//
// Created by Sofia Blyufer and Aviel Cohen on 29/11/2021.
//

#include "PlayersManager.h"
#include "Group.h"
#include "AVLTree.h"

//PlayersManager* PlayersManager::Init() {
//    PlayersManager* DS = new PlayersManager;
//    return DS;
//}
PlayersManager::PlayersManager() : eGroup(), fGroup(), players(-1), strongestPlayerID(-1){} 
void PlayersManager::addGroup(const int& id) {
    if (id <= 0){
        throw InvalidInput();
    }
    eGroup.insert(Group(id));
}
void PlayersManager::addPlayer(const int& player_id, const int& group_id, const int& level) {
    if (player_id <= 0 || group_id <= 0 || level < 0) {
        throw InvalidInput();
    } 
    Group current_group(group_id);
    Player current_player = Player(player_id, player_id, level);
    if (eGroup.exists(current_group)) //means it's empty
    {
        fGroup.insert(current_group);
        eGroup.remove(current_group);
    }
    fGroup.get(current_group).insertPlayer(player_id, group_id, level);
    players.insertPlayer(fGroup.get(current_group).getPlayer(player_id));
}
void PlayersManager::removePlayer(const int& player_id) {
    if(player_id <= 0){
        throw InvalidInput();
    }
    findPlayerGroup(player_id).removePlayer(player_id);
    players.removePlayer(player_id);
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
        int n1 = g1.getNumOfPlayers();
        int n2 = g2.getNumOfPlayers();
        int* dummy1[n1];
        int* dummy2[n2];
        array<Player> arr1(n1,dummy1);
        array<Player> arr2(n2,dummy2);
        Player joined[n1+n2];
        mergeArrays(arr1.T_get(),arr2.T_get(),n1,n2,joined);
        AVLTree<Player> empty;
        empty = empty.createEmptyTree(n1+n2); //help?
        Insert ins(joined, n1+n2);
        empty.inOrder(ins);
        g2.replacePlayers(empty); //TODO change group id
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
    if (!eGroup.exists(current_group) && !fGroup.exists(current_group)){
        return false;
    }
    return true;
}
void PlayersManager::increaseLevel(const int& player_id, const int& level_increase) {
    if (player_id <= 0 || level_increase <= 0) {
        throw InvalidInput();
    }
    const int level = players.getPlayer(player_id).getLevel();
    players.getPlayer(player_id).setLevel(level + level_increase);
    findPlayerGroup(player_id).getPlayer(player_id).setLevel(level + level_increase);
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
        array<Player> my_array(*numOfPlayers, Players);
        fGroup.get(current_group).getLevelTree().inOrder(my_array);
    }
    else{
        throw ValueNotExists();
    }
}
void PlayersManager::getGroupsHighestLevel(const int numOfGroups, int** Players) {
    int* size; //dummy pointer
    arrayMalloc(numOfGroups, size, Players);
    array<Group> my_array(numOfGroups, Players);
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