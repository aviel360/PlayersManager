#include "Group.h"

    Group::Group(int _groupID) : groupID(_groupID), playersID(), playersLevel(), strongestPlayerLevel(-1), 
                                strongestPlayerID(-1), numOfPlayers(0) {}
    void Group::insertPlayer(int PlayerID, int Level){
        Player _playerID(PlayerID, PlayerID, Level);
        playersID.insert(_playerID);
        Player _playerLevel(Level, PlayerID, Level);
        playersLevel.insert(_playerLevel);
        updateStrongest(PlayerID, Level);
        numOfPlayers++;
    }
    void Group::removePlayer(int PlayerID){
        Player _player(PlayerID);
        _player = playersID.find(_player)->getValue();
        playersID.remove(_player);
        _player = playersLevel.find(_player)->getValue();
        playersLevel.remove(_player);
        _player = playersLevel.getMaxValue();
        strongestPlayerID = -1;
        strongestPlayerLevel = 0;
        updateStrongest(_player.getPlayerID(), _player.getLevel());
        numOfPlayers--;
    }
    int Group::getStrongestPlayer(){
        return this->strongestPlayerID;
    }
    int Group::getNumOfPlayers(){
        return this->numOfPlayers;
    }
    void Group::updateStrongest(int PlayerID, int Level){
        if(Level < strongestPlayerLevel){
            return;
        }
        int old_level = strongestPlayerLevel;
        strongestPlayerLevel = Level > strongestPlayerLevel ? Level : strongestPlayerLevel;
        strongestPlayerID = old_level < strongestPlayerLevel ? 
                            PlayerID : PlayerID < strongestPlayerID ? PlayerID : strongestPlayerID;
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