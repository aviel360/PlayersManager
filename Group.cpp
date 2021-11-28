#include "Group.h"

    Group::Group(int _groupID) : groupID(_groupID), players(), strongestPlayerLevel(-1), 
                                strongestPlayerID(-1), numOfPlayers(0) {}
    void Group::insertPlayer(int key, int PlayerID, int Level){
        Player _player(key, PlayerID, Level);
        players.insert(_player);
        if(Level < strongestPlayerLevel){
            return;
        }
        int old_level = strongestPlayerLevel;
        strongestPlayerLevel = Level > strongestPlayerLevel ? Level : strongestPlayerLevel;
        strongestPlayerID = old_level < strongestPlayerLevel ? 
                            PlayerID : PlayerID < strongestPlayerID ? PlayerID : strongestPlayerID;
    }
    void Group::removePlayer(int PlayerID){
        Player _player(PlayerID);
        _player = players.find(_player)->getValue();
        players.remove(_player);
    }
    int Group::getStrongestPlayer(){
        return this->strongestPlayerID;
    }
    int Group::getNumOfPlayers(){
        return this->numOfPlayers;
    }
    bool operator>(const Group& group_a, const Group& group_b){
        return group_b < group_a;
    }
    bool operator<=(const Group& group_a, const Group& group_b){
        return !(group_a > group_b);
    }
    bool operator>=(const Group& group_a, const Group& group_b){
        return !(group_a < group_b);
    }
    bool operator!=(const Group& group_a, const Group& group_b){
        return !(group_a == group_b);
    }