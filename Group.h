#ifndef PLAYERSMANAGER_GROUP_H
#define PLAYERSMANAGER_GROUP_H
#include "Player.h"
#include "AVLTree.h"

class Group{
    int groupID;
    AVLTree<Player> players;
    Player strongestPlayer;
    int numOfPlayers;

public:
    Group(int groupID);
    Group(const Group& _group) = default;
    Group& operator=(const Group& _group) = default;
    ~Group() = default;

    void insertPlayer(int key, int PlayerID, int Level);
    void removePlayer(int PlayerID);
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