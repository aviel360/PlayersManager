#include "Group.h"
#include "Exceptions.h"

    Group::Group(int _groupID) : groupID(_groupID), playersID(), playersLevel(), strongestPlayerLevel(-1), 
                                strongestPlayerID(-1), numOfPlayers(0) {}
    void Group::insertPlayer(int PlayerID, int Level){
        Player _playerID(PlayerID, PlayerID, Level);
        Player _playerLevel(Level, PlayerID, Level);
        playersID.insert(_playerID);
        playersLevel.insert(_playerLevel);
        updateStrongest(PlayerID, Level);
        numOfPlayers++;
    }
    void Group::removePlayer(int PlayerID){
        Player _player(PlayerID, PlayerID);
        auto player_exists = playersID.find(_player);
        if(player_exists == nullptr){
            throw ValueNotExists();
        }
        _player = player_exists->getValue();
        Player _playerLevel(_player.getLevel(), PlayerID, _player.getLevel());
        playersID.remove(_player);
        playersLevel.remove(_playerLevel);

        strongestPlayerID = -1;
        strongestPlayerLevel = 0;
        _player = playersLevel.getMaxValue();
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