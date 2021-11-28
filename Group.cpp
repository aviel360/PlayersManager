#include "Group.h"
    void Group::insertPlayer(int key, int PlayerID, int Level){
        Player _player(key, PlayerID, Level);
        players.insert(_player);
    }
    void Group::removePlayer(int PlayerID){
        Player _player(PlayerID);
        _player = players.find(_player)->getValue();
        players.remove(_player);
    }
    int Group::getStrongestPlayer(){
        return this->strongestPlayer.getPlayerID();
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
        return !(group_a < group_b)
    }
    bool operator!=(const Group& group_a, const Group& group_b){
        return !(group_a == group_b);
    }