#include "Group.h"
#include "Exceptions.h"
    Group::Group() : groupID(0), playersID(), playersLevel(), strongestPlayerLevel(-1), 
                                strongestPlayerID(-1), numOfPlayers(0) {}
    Group::Group(int _groupID) : groupID(_groupID), playersID(), playersLevel(), strongestPlayerLevel(-1), 
                                strongestPlayerID(-1), numOfPlayers(0) {}
    void Group::insertPlayer(int PlayerID, int _groupID, int Level){
        
        std::shared_ptr<Player> _playerID = std::make_shared<Player>(PlayerID, _groupID, PlayerID, Level);
        std::shared_ptr<Player> _playerLevel = std::make_shared<Player>(Level, _groupID, PlayerID, Level);
        playersID.insert(_playerID);
        playersLevel.insert(_playerLevel);
        updateStrongest(PlayerID, Level);
        numOfPlayers++;
    }

    void Group::insertPlayer(std::shared_ptr<Player>& player){
        playersID.insert(player);
        std::shared_ptr<Player> _playerLevel = std::make_shared<Player>((*player).getLevel(), 
                                (*player).getGroupID(), (*player).getPlayerID(), (*player).getLevel());
        playersLevel.insert(_playerLevel);
    }
    void Group::removePlayer(int PlayerID){
        std::shared_ptr<Player> _player = getPlayer(PlayerID);
        std::shared_ptr<Player> _playerLevel = std::make_shared<Player>((*_player).getLevel(), 
                                                (*_player).getGroupID(), PlayerID, (*_player).getLevel());
        playersID.remove(_player);
        playersLevel.remove(_playerLevel);

        strongestPlayerID = -1;
        strongestPlayerLevel = 0;
        _player = playersLevel.getMaxValue();
        updateStrongest((*_player).getPlayerID(), (*_player).getLevel());

        numOfPlayers--;
    }
    std::shared_ptr<Player>& Group::getPlayer(int PlayerID){
        std::shared_ptr<Player> _player = std::make_shared<Player>(PlayerID, -1, PlayerID);
        return playersID.get(_player);
    }
    bool Group::playerExists(int PlayerID){
        try{
            getPlayer(PlayerID);
        }
        catch(ValueNotExists& e){
            return false;
        }
        return true;
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
    int Group::getReturn() const {
        return this->groupID;
    }
    AVLTree<std::shared_ptr<Player>>& Group::getLevelTree() {
        return this->playersLevel;
    }
    AVLTree<std::shared_ptr<Player>>& Group::getIDTree() {
        return this->playersID;
    }
    void Group::setLevelTree(AVLTree<std::shared_ptr<Player>>& tree) {
        this->playersLevel = tree;
    }
    void Group::setIDTree(AVLTree<std::shared_ptr<Player>>& tree) {
       this->playersID = tree;
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
