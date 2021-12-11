#include "Group.h"
#include "Exceptions.h"
    Group::Group() : groupID(0), playersID(), playersLevel(), 
    strongestPlayer(Level(-1,-1)), numOfPlayers(0) {}
    Group::Group(int _groupID) : groupID(_groupID), playersID(), playersLevel(),
    strongestPlayer(Level(-1,-1)), numOfPlayers(0) {}
    void Group::insertPlayer(int player_id, int group_id, int level){
        std::shared_ptr<Player> player = std::make_shared<Player>(group_id, player_id, level);
        std::shared_ptr<Player> playerLevel = player;
        playersID.insert(player, player_id);
        playersLevel.insert(playerLevel, player->getLevel());
        updateStrongest(player->getLevel());
        numOfPlayers++;
    }
    void Group::insertPlayer(std::shared_ptr<Player>& _player){
        std::shared_ptr<Player> player = _player;
        std::shared_ptr<Player> playerLevel = _player;
        playersID.insert(player, player->getPlayerID());
        playersLevel.insert(playerLevel, player->getLevel());
        updateStrongest(player->getLevel());
        numOfPlayers++;
    }
    void Group::removePlayer(int player_id){
      //  Player p = Player(PlayerID,PlayerID,PlayerID,0);
        if (!playersID.exists(player_id))
        {
            throw ValueNotExists();
        }
        std::shared_ptr<Player> _player = playersID.get(player_id);
        Level level = _player->getLevel();
     //   Player _playerLevel(_player.getLevel(), _player.getGroupID(), PlayerID, _player.getLevel());
        playersID.remove(player_id);
        playersLevel.remove(level);
        strongestPlayer = Level(-1,-1);
        if(playersLevel.getSource() != nullptr){
            _player = playersLevel.getMaxValue();
            updateStrongest(_player->getLevel());
        }
        numOfPlayers--;
    }
//    bool Group::playerExists(int PlayerID){
//        try{
//            getPlayer(PlayerID);
//        }
//        catch(ValueNotExists& e){
//            return false;
//        }
//        return true;
//    }
    
    Level& Group::getStrongestPlayer(){
        return this->strongestPlayer;
    }
    int Group::getNumOfPlayers(){
        return this->numOfPlayers;
    }
    void Group::updateStrongest(Level& level){
        if(level < strongestPlayer){
            return;
        }
        strongestPlayer = level;
    }
    std::shared_ptr<Player>& Group::getPlayer(int PlayerID){
        return playersID.get(PlayerID);
    }
//    void Group::setPlayerLevel(int player_id, int _level){
//        (*getPlayer(player_id)).setLevel(_level);
//        updateStrongest(player_id, _level);
//    }
    AVLTree<std::shared_ptr<Player>, Level>& Group::getLevelTree() {
        return this->playersLevel;
    }
    AVLTree<std::shared_ptr<Player>, int>& Group::getIDTree() {
        return this->playersID;
    }
    void Group::setLevelTree(AVLTree<std::shared_ptr<Player>, Level>& tree) {
        this->playersLevel = tree;
    }
    void Group::setIDTree(AVLTree<std::shared_ptr<Player>, int>& tree) {
       this->playersID = tree;
    }
    void Group::setNumOfPlayers(int size) {
       this->numOfPlayers = size;
    }
//    bool operator>(const Group& group_a, const Group& group_b){
//        return group_b < group_a;
//    }
//    bool operator<=(const Group& group_a, const Group& group_b){
//        return !(group_a > group_b);
//    }
//    bool operator>=(const Group& group_a, const Group& group_b){
//        return !(group_a < group_b);
//    }
//    bool operator!=(const Group& group_a, const Group& group_b){
//        return !(group_a == group_b);
//    }
