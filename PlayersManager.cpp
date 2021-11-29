//
// Created by Sofia Blyufer on 29/11/2021.
//

#include "PlayersManager.h"

//PlayersManager* PlayersManager::Init() {
//    PlayersManager* DS = new PlayersManager;
//    return DS;
//}

void PlayersManager::addGroup(const int& id) {
    if (id <= 0)
    {
        throw InvalidInput();
    }
    Group group(id);
    eGroup.insert(group);
}
void PlayersManager::addPlayer(const int& player_id, const int& group_id, const int& level) {
    if (player_id <= 0 || group_id <= 0 || level < 0)
    {
        throw InvalidInput();
    } //maybe take off if exists in c'tors
    Group current_group = Group(group_id);
    if (!eGroup.exists(current_group) && !fGroup.exists(current_group))
    {
        throw ValueNotExists();
    }
    Player current_player = Player(player_id, player_id, level);
    if (players.exists(current_player))
    {
        throw ValueExists();
    }
    if (eGroup.exists(current_group)) //means it's empty
    {
        fGroup.insert(current_group);
        eGroup.remove(current_group);
    }
    players.insert(current_player); //TODO maybe add more tree
    fGroup.get(current_group).insertPlayer(player_id, level);

}
void removePlayer(const int& player_id) {

}
void replaceGroup(const int& group_id, const int& replace_id) {

}
void increaseLevel(const int& player_id, const int& new_level) {

}
void getAllPlayersByLevel(const int& group_id, int** Players, int* numOfPlayers) {

}
void getGroupsHighestLevel(const int& numOfGroups, int** Players) {

}
//void Quit() {
//
//}