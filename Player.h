#ifndef PLAYERSMANAGER_PLAYER_H_
#define PLAYERSMANAGER_PLAYER_H_

class Player{
    int key;
    int PlayerID;
    int Level;
public:
    Player(int _PlayerId, int _Level, int _key);
    Player(const Player& player) = default;
    Player& operator=(const Player& player) = default;
    ~Player() = default;

    void setLevel(int _Level);
    int getLevel();
    int getPlayerID();
    int getKey();
    friend bool operator==(const Player& player_a, const Player& player_b){
        return player_a.key == player_b.key;
    }
    friend bool operator<(const Player& player_a, const Player& player_b){
        return player_a.key < player_b.key;
    }
};
    bool operator>(const Player& player_a, const Player& player_b);
    bool operator<=(const Player& player_a, const Player& player_b);
    bool operator>=(const Player& player_a, const Player& player_b);
    bool operator!=(const Player& player_a, const Player& player_b);


#endif