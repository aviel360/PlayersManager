#include "Player.h"

    Player::Player(int _PlayerId, int _Level, int _key) : PlayerID(_PlayerId), Level(_Level), key(_key) {}
    void Player::setLevel(int _Level){
        this->Level = _Level;
    }
    int Player::getLevel(){
        return this->Level;
    }
    int Player::getPlayerID(){
        return this->PlayerID;
    }
    int Player::getKey(){
        return this->key;
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