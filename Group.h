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
    Group();
    Group(int _groupID);
    Group(const Group& _group) = default;
    Group& operator=(const Group& _group) = default;
    ~Group() = default;
    void setLevelTree(AVLTree<Player>& tree);
    void setIDTree(AVLTree<Player>& tree);
    void insertPlayer(int PlayerID, int _groupID, int Level = 0);
    void insertPlayer(std::shared_ptr<Player> player);
    void removePlayer(int PlayerID);
    std::shared_ptr<Player> getPlayer(int PlayerID);
    bool playerExists(int PlayerID);
    int getStrongestPlayer();
    int getNumOfPlayers();
    int getReturn() const;
    void replacePlayers(AVLTree<Player>& tree);
    AVLTree<Player>& getLevelTree();
    AVLTree<Player>& getIDTree();

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