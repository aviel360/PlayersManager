#ifndef PLAYERSMANAGER_GROUP_H
#define PLAYERSMANAGER_GROUP_H
#include "Player.h"
#include "AVLTree.h"
#include <memory>

class Group{
    int groupID;
    AVLTree<std::shared_ptr<Player>, int> playersID;
    AVLTree<std::shared_ptr<Player>, Level> playersLevel;
    Level strongestPlayer;
    int numOfPlayers;

public:
    Group();
    Group(int _groupID);
    Group(const Group& _group) = default;
    Group& operator=(const Group& _group) = delete;
    ~Group() = default;
    void setLevelTree(AVLTree<std::shared_ptr<Player>, Level>& tree);
    void setIDTree(AVLTree<std::shared_ptr<Player>, int>& tree);
    void insertPlayer(int PlayerID, int _groupID, int _level);
    void insertPlayer(std::shared_ptr<Player>& player);
    void removePlayer(int PlayerID);
    void updateStrongest(Level& level);
    void setNumOfPlayers(int size);
    std::shared_ptr<Player>& getPlayer(int PlayerID);
    Level& getStrongestPlayer();
    int getNumOfPlayers();
    AVLTree<std::shared_ptr<Player>, Level>& getLevelTree();
    AVLTree<std::shared_ptr<Player>, int>& getIDTree();
};
#endif