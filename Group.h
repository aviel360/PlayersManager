#ifndef PLAYERSMANAGER_GROUP_H
#define PLAYERSMANAGER_GROUP_H
#include "Player.h"
#include "AVLTree.h"

class Group{
    int groupID;
    AVLTree<Player> playersID;
    AVLTree<Player> playersLevel;
    int strongestPlayerLevel;
    int strongestPlayerID;
    int numOfPlayers;

    void updateStrongest(int _playerID, int _playerLevel);

public:
    Group(int _groupID);
    Group(const Group& _group) = default;
    Group& operator=(const Group& _group) = default;
    ~Group() = default;

    void insertPlayer(int PlayerID, int _groupID, int Level);
    void removePlayer(int PlayerID);
    Player getPlayer(int PlayerID);
    bool playerExists(int PlayerID);
    int getStrongestPlayer();
    int getNumOfPlayers();

    friend bool operator==(const Group& group_a, const Group& group_b){
        return group_a.groupID == group_b.groupID;
    }
    friend bool operator<(const Group& group_a, const Group& group_b){
        return group_a.groupID < group_b.groupID;
    }
};
    bool operator>(const Group& group_a, const Group& group_b);
    bool operator<=(const Group& group_a, const Group& group_b);
    bool operator>=(const Group& group_a, const Group& group_b);
    bool operator!=(const Group& group_a, const Group& group_b);

#endif