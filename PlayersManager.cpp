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
void PlayersManager::addGroup(const int id) {
    if (id <= 0){
        throw InvalidInput();
    }
    if(groupExists(id)){
        throw ValueExists();
    }
    eGroup.insert(Group(id));
}
void PlayersManager::addPlayer(const int player_id, const int group_id, const int level) {
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
void PlayersManager::removePlayer(const int player_id) {
    if(player_id <= 0){
        throw InvalidInput();
    }
    findPlayerGroup(player_id).removePlayer(player_id);
    players.removePlayer(player_id);
}

void PlayersManager::replaceGroup(const int group_id, const int replace_id) {
    if (replace_id <= 0 || group_id <= 0)
    {
        throw InvalidInput();
    }
    Group g1 = Group(group_id);
    g1 = fGroup.get(g1);
    Group g2 = Group(replace_id);
    g2 = fGroup.get(g2);
    if (eGroup.exists(g1)){
        if (groupExists(replace_id)){
            eGroup.remove(g1);
            return;
        }
        else{
            throw ValueNotExists();
        }
    }
    else if (fGroup.exists(g1)){
        if (eGroup.exists(g2)){
            eGroup.remove(g2);
            fGroup.insert(g2);
        }
        else if (!fGroup.exists(g1)){
            throw InvalidInput();
        }
        int n1 = g1.getNumOfPlayers();
        int n2 = g2.getNumOfPlayers();
        AVLTree<Player> playerIDTree = AVLTree<Player>();
        AVLTree<Player> playerLevelTree = AVLTree<Player>();
        playerIDTree.createEmptyTree(n1+n2);
        playerLevelTree.createEmptyTree(n1+n2);
        g2.setIDTree(createMergeTree(g1.getIDTree(), g2.getIDTree(), n1, n2, replace_id, playerIDTree));
        g2.setLevelTree(createMergeTree(g1.getLevelTree(), g2.getLevelTree(), n1, n2, replace_id, playerLevelTree));
        fGroup.remove(g1);
    }
}
AVLTree<Player>& PlayersManager::createMergeTree(AVLTree<Player>& tree1, AVLTree<Player>& tree2, int n1,
                                            int n2, int replace_id, AVLTree<Player>& playerTree){
//    arrayMerge arr1(n1, replace_id);
//    arrayMerge arr2(n2, replace_id);
//    Player* joined = new Player[n1+n2];
//    tree1.inOrder(arr1);
//    tree2.inOrder(arr2);
//    mergeArrays(arr1.get(),arr2.get(),n1,n2,joined);
//    arrayInsert to_insert(joined, n1+n2);
//    playerTree.inOrder(to_insert);
//    delete[] joined;
//    return playerTree;
}
void PlayersManager::mergeArrays(Player* arr1, Player* arr2, int n1, int n2, Player* arr3){
    int i = 0, j = 0, k = 0;
    while (i<n1 && j <n2){
        if (arr1[i] < arr2[j])
            arr3[k++] = arr1[i++];
        else
            arr3[k++] = arr2[j++];
    }
    while (i < n1)
        arr3[k++] = arr1[i++];

    while (j < n2)
        arr3[k++] = arr2[j++];
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
void PlayersManager::increaseLevel(const int player_id, const int level_increase) {
    if (player_id <= 0 || level_increase <= 0) {
        throw InvalidInput();
    }
    const int level = players.getPlayer(player_id).getLevel();
    players.getPlayer(player_id).setLevel(level + level_increase);
    findPlayerGroup(player_id).getPlayer(player_id).setLevel(level + level_increase);
}
int PlayersManager::getHighestLevel(const int group_id){
    int player_id = players.getStrongestPlayer();
    Group group = Group(group_id);
    if(group_id < 0){
        return player_id;
    }
    if(eGroup.exists(group)){
        return -1;
    }
    return fGroup.get(group).getStrongestPlayer();
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
void PlayersManager::getAllPlayersByLevel(const int group_id, int** Players, int* numOfPlayers) {
    if (Players == nullptr || numOfPlayers == nullptr || group_id == 0){
        throw InvalidInput();
    }
    Group current_group;
    if (group_id >=0)
    {
        current_group = Group(group_id);
        if (eGroup.exists(current_group)){
            *Players = nullptr;
            *numOfPlayers = 0;
            return;
        }
        else{
            if (!fGroup.exists(current_group))
            {
                throw ValueNotExists();
            }
        }
    }
    else
    {
        current_group = this->players;
    }
    *numOfPlayers = current_group.getNumOfPlayers();
    ID_array ids(*numOfPlayers);
    current_group.getLevelTree().inOrder(ids);
    *Players = ids.get_ids();
}
void PlayersManager::getGroupsHighestLevel(const int numOfGroups, int** Players) {
//    if(Players == nullptr || numOfGroups < 0){
//        throw InvalidInput();
//    }
//    int dummy = 0;
//    int* size = &dummy;
//    arrayMalloc(numOfGroups, size, Players);
//    arrayPtr<Group> my_array(numOfGroups, Players);
//    try{
//        fGroup.inOrder(my_array);
//    }
//    catch(Index& e){}
//    if(numOfGroups > my_array.getIter()){
//        throw ValueNotExists();
//    }
}

