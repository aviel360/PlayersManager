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
    Group& operator=(const Group& _group) = default;
    ~Group() = default;
    void setLevelTree(AVLTree<std::shared_ptr<Player>, Level>& tree);
    void setIDTree(AVLTree<std::shared_ptr<Player>, int>& tree);
    void insertPlayer(int PlayerID, int _groupID, int _level);
    void insertPlayer(std::shared_ptr<Player>& player);
    void removePlayer(int PlayerID);
   // void setPlayerLevel(int _player, int _level);
    void updateStrongest(Level& level);
    void setNumOfPlayers(int size);
    std::shared_ptr<Player>& getPlayer(int PlayerID);
  //  bool playerExists(int PlayerID);
    Level& getStrongestPlayer();
    int getNumOfPlayers();
   // int getReturn() const;
  //  void replacePlayers(AVLTree<std::shared_ptr<Player>>& tree);
    AVLTree<std::shared_ptr<Player>, Level>& getLevelTree();
    AVLTree<std::shared_ptr<Player>, int>& getIDTree();

//    friend bool operator==(const Group& group_a, const Group& group_b){
//        return group_a.groupID == group_b.groupID;
//    }
//    friend bool operator<(const Group& group_a, const Group& group_b){
//        return group_a.groupID < group_b.groupID;
//    }

};
//    bool operator>(const Group& group_a, const Group& group_b);
//    bool operator<=(const Group& group_a, const Group& group_b);
//    bool operator>=(const Group& group_a, const Group& group_b);
//    bool operator!=(const Group& group_a, const Group& group_b);
//

#endif