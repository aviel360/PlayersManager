#include "Player.h"
    Player::Player() : key(-1), PlayerID(-1), groupID(-1), Level(-1) {}
    Player::Player(int _key, int _groupID, int _PlayerId, int _Level) : key(_key), PlayerID(_PlayerId), 
                                                                        groupID(_groupID), Level(_Level) {}
    void Player::setLevel(const int _Level){
        this->Level = _Level;
    }
    int Player::getLevel() const{
        return this->Level;
    }
    int Player::getPlayerID() const{
        return this->PlayerID;
    }
    int Player::getKey() const{
        return this->key;
    }
    int Player::getReturn() const {
        return this->PlayerID;
    }
    int Player::getGroupID() const{
        return this->groupID;
    }
    void Player::setGroupID(int _groupID){
        this->groupID = _groupID;
    }
    bool operator>(const Player& player_a, const Player& player_b){
        return player_b < player_a;
    }
    bool operator<=(const Player& player_a, const Player& player_b){
        return !(player_a > player_b);
    }
    bool operator>=(const Player& player_a, const Player& player_b){
        return !(player_a < player_b);
    }
    bool operator!=(const Player& player_a, const Player& player_b){
        return !(player_a == player_b);
    }