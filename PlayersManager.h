//
// Created by Sofia Blyufer on 29/11/2021.
//

#ifndef PROJNAME_PLAYERSMANAGER_H
#define PROJNAME_PLAYERSMANAGER_H

#include "AVLTree.h"
#include "Player.h"
#include "Group.h"
#include "Exceptions.h"

enum StatusType{
    SUCCESS,
    ALLOCATION_ERROR,
    INVALID_INPPUT,
    FAILURE
}; // here?

class PlayersManager{
    AVLTree<Group> eGroup;
    AVLTree<Group> fGroup;
    Group players;
    int strongestPlayerID;


    Group& findPlayerGroup(int player_id);
    Group& groupExists(const int group_id);

public:

//    static PlayersManager* Init();
    PlayersManager() = default;
    ~PlayersManager() = default;
    void addGroup(const int& id); //maybe void?
    void addPlayer(const int& player_id, const int& group_id, const int& level);
    void removePlayer(const int& player_id);
    void replaceGroup(const int& group_id, const int& replace_id);
    void increaseLevel(const int& player_id, const int& new_level);
    int getHighestLevel(const int group_id, const int player_id);
    void getAllPlayersByLevel(const int& group_id, int** Players, int* numOfPlayers);
    void getGroupsHighestLevel(const int& numOfGroups, int** Players);
//    void Quit();
};
#endif //PROJNAME_PLAYERSMANAGER_H
