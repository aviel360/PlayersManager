#include "Player.h"
    Player::Player() : groupID(-1), PlayerID(-1), PlayerLevel(-1, -1) {}
    Player::Player(int _groupID, int _PlayerId, int _Level) : groupID(_groupID), PlayerID(_PlayerId), PlayerLevel(_Level, _PlayerId) {}
//    void Player::setLevel(const int _Level){
//        this->Level = _Level;
//    }
    Level::Level() : PlayerLevel(-1), PlayerID(-1) {}
    Level::Level(int key) : PlayerLevel(key), PlayerID(key) {}
    Level::Level(int _level, int player_id) : PlayerLevel(_level), PlayerID(player_id) {}
    Level& Player::getLevel(){
        return this->PlayerLevel;
    }
    int Player::getPlayerID() const{
        return this->PlayerID;
    }
    int Player::getGroupID() const{
        return this->groupID;
    }
    void Player::setGroupID(int _groupID){
        this->groupID = _groupID;
    }
    bool operator>(const Level& level_a, const Level& level_b){
        return level_b < level_a;
    }
    bool operator<=(const Level& level_a, const Level& level_b){
        return !(level_a > level_b);
    }
    bool operator>=(const Level& level_a, const Level& level_b){
        return !(level_a < level_b);
    }
    bool operator!=(const Level& level_a, const Level& level_b){
        return !(level_a == level_b);
    }