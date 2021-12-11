//
// Created by Sofia Blyufer and Aviel Cohen on 29/11/2021.
//

#include "PlayersManager.h"
#include "Group.h"
#include "AVLTree.h"
#include <memory>

PlayersManager::PlayersManager() : eGroup(), fGroup(), players(-1){} 
void PlayersManager::addGroup(int id) {
    if (id <= 0){
        throw InvalidInput();
    }
    if(groupExists(id)){
        throw ValueExists();
    }
    std::shared_ptr<Group> group = std::make_shared<Group>(id);
    eGroup.insert(group, id);
}
void PlayersManager::addPlayer(const int player_id, const int group_id, const int level) {
    if (player_id <= 0 || group_id <= 0 || level < 0) {
        throw InvalidInput();
    }
    if(!groupExists(group_id)){
        throw ValueNotExists();
    }
    players.insertPlayer(player_id, group_id, level);
    if (eGroup.exists(group_id)) //means it's empty
    {
        fGroup.insert(eGroup.get((group_id)), group_id);
        eGroup.remove(group_id);
    }
    fGroup.get(group_id)->insertPlayer(players.getPlayer(player_id));
}
void PlayersManager::removePlayer(const int player_id) {
    if(player_id <= 0){
        throw InvalidInput();
    }
    int group_id = findPlayerGroup(player_id);
    std::shared_ptr<Group> current_group = fGroup.get(group_id);
    current_group->removePlayer(player_id);
    if(current_group->getNumOfPlayers() == 0){
        eGroup.insert(current_group, group_id);
        fGroup.remove(group_id);
    }
    players.removePlayer(player_id);
}

void PlayersManager::replaceGroup(const int group_id, const int replace_id) {
    if (replace_id <= 0 || group_id <= 0 || group_id == replace_id)
    {
        throw InvalidInput();
    }
  //  std::shared_ptr<Group> g1 = Group(group_id);
 //   Group g2 = Group(replace_id);
    if (eGroup.exists(group_id)){
        if (groupExists(replace_id)){
            eGroup.remove(group_id);
            return;
        }
        else{
            throw ValueNotExists();
        }
    }
    else if (fGroup.exists(group_id)){
        std::shared_ptr<Group> g1 = fGroup.get(group_id);
        if (eGroup.exists(replace_id)){
            std::shared_ptr<Group> g2 = eGroup.get(replace_id);
            fGroup.insert(g2, replace_id);
            eGroup.remove(replace_id);
        }
        std::shared_ptr<Group> g2 = fGroup.get(replace_id);
        int n1 = g1->getNumOfPlayers();
        int n2 = g2->getNumOfPlayers();
        auto playerIDTree = AVLTree<std::shared_ptr<Player>, int>();
        auto playerLevelTree = AVLTree<std::shared_ptr<Player>, Level>();
        playerIDTree.createEmptyTree(n1+n2);
        playerLevelTree.createEmptyTree(n1+n2);
        g2->setIDTree(createMergeTree<int>(g1->getIDTree(), g2->getIDTree(), n1, n2, replace_id, playerIDTree));
        g2->setLevelTree(createMergeTree<Level>(g1->getLevelTree(), g2->getLevelTree(), n1, n2, replace_id, playerLevelTree));
        std::shared_ptr<Player> _player = g2->getLevelTree().getMaxValue();
        g2->updateStrongest(_player->getLevel());
        g2->setNumOfPlayers(n1+n2);
        fGroup.remove(group_id);
    }
    else{
        throw ValueNotExists();
    }
}
template<class T>
AVLTree<std::shared_ptr<Player>, T>& PlayersManager::createMergeTree(AVLTree<std::shared_ptr<Player>, T>& tree1,
               AVLTree<std::shared_ptr<Player>, T>& tree2, int n1, int n2, int replace_id,
               AVLTree<std::shared_ptr<Player>, T>& playerTree){
   arrayMerge<T> arr1(n1, replace_id);
   arrayMerge<T> arr2(n2, replace_id);
   auto joinedValue = new std::shared_ptr<Player>[n1+n2];
   T* joinedKey = new T[n1+n2];
   for(int i = 0; i < n1+n2; i++){
       joinedValue[i] = std::make_shared<Player>(Player());
   }
   tree1.inOrder(arr1);
   tree2.inOrder(arr2);
   mergeArrays<T>(arr1.getArr(),arr2.getArr(), arr1.getKeys(), arr2.getKeys(),n1,n2,joinedValue, joinedKey);
   arrayInsert<T> to_insert(joinedValue, joinedKey, n1+n2);
   playerTree.inOrder(to_insert);
   delete[] joinedValue;
   delete[] joinedKey;
   return playerTree;
}
template<class T>
void PlayersManager::mergeArrays(std::shared_ptr<Player>* arr1, std::shared_ptr<Player>* arr2,
                                 T* keys1, T* keys2, int n1, int n2,
                                 std::shared_ptr<Player>* arr3, T* keys3){
    int i = 0, j = 0, k = 0;
    while (i<n1 && j <n2){
        if (keys1[i] < keys2[j]){
            keys3[k] = keys1[i];
            arr3[k++] = arr1[i++];
        }
        else{
            keys3[k] = keys2[j];
            arr3[k++] = arr2[j++];
        }
    }
    while (i < n1){
        keys3[k] = keys1[i];
        arr3[k++] = arr1[i++];
    }

    while (j < n2){
        keys3[k] = keys2[j];
        arr3[k++] = arr2[j++];
    }
}
int PlayersManager::findPlayerGroup(int player_id){
    std::shared_ptr<Player> player = players.getPlayer(player_id);
    return player->getGroupID();
}
bool PlayersManager::groupExists(const int group_id){
    if (!eGroup.exists(group_id) && !fGroup.exists(group_id)){
        return false;
    }
    return true;
}
void PlayersManager::increaseLevel(const int player_id, const int level_increase) {
    if (player_id <= 0 || level_increase <= 0) {
        throw InvalidInput();
    }
    std::shared_ptr<Player> current_player = players.getPlayer(player_id);
    Level level = current_player->getLevel();
    int group_id = current_player->getGroupID();
    removePlayer(player_id);
    addPlayer(level.PlayerID, group_id, level.PlayerLevel + level_increase);
}
int PlayersManager::getHighestLevel(const int group_id){
    if(group_id < 0){
        return players.getStrongestPlayer().PlayerID;
    }
    if(eGroup.exists(group_id)){
        return -1;
    }
    return fGroup.get(group_id)->getStrongestPlayer().PlayerID;
}

void PlayersManager::arrayMalloc(int size, int* sizePtr, int** arrayPtr){
    *sizePtr = size;
    if(size == 0){
        (*arrayPtr) = nullptr;
    }
    else{
        (*arrayPtr) = (int*)malloc(sizeof(int)*size);
    }
}
void PlayersManager::getAllPlayersByLevel(const int group_id, int** Players, int* numOfPlayers) {
    if (Players == nullptr || numOfPlayers == nullptr || group_id == 0){
        throw InvalidInput();
    }
   // Group current_group = Group(group_id);
    if(eGroup.exists(group_id)){
        arrayMalloc(0, numOfPlayers, Players);
    }
    else if (group_id < 0){   
        arrayMalloc(players.getNumOfPlayers(), numOfPlayers, Players);
        arrayPtr<Player, Level> my_array(*numOfPlayers, Players);
        players.getLevelTree().inOrder(my_array);
    }
    else if (fGroup.exists(group_id)){
        std::shared_ptr<Group> current_group = fGroup.get(group_id);
        arrayMalloc(current_group->getNumOfPlayers(), numOfPlayers, Players);
        arrayPtr<Player, Level> my_array(*numOfPlayers, Players);
        current_group->getLevelTree().inOrder(my_array);
    }
    else{
        throw ValueNotExists();
    }
}
void PlayersManager::getGroupsHighestLevel(const int numOfGroups, int** Players) {
   if(Players == nullptr || numOfGroups <= 0){
       throw InvalidInput();
   }
   int dummy = 0;
   int* size = &dummy;
   arrayMalloc(numOfGroups, size, Players);
   arrayPtr<Group, int> my_array(numOfGroups, Players);
   try{
       fGroup.inOrder(my_array);
   }
   catch(Index& e){}
   if(numOfGroups > my_array.getIter()){
       free(*Players);
       throw ValueNotExists();
   }
}
