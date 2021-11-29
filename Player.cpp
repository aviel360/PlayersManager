#include "Player.h"

    Player::Player(int _key, int _PlayerId, int _Level) : key(_key), PlayerID(_PlayerId), Level(_Level) {}
    void Player::setLevel(int _Level){
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