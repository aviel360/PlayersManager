#ifndef PLAYERSMANAGER_PLAYER_H_
#define PLAYERSMANAGER_PLAYER_H_

class Player{
    int key;
    int PlayerID;
    int Level;
    
public:
    Player(int _key, int _PlayerId = 0, int _Level = 0);
    Player(const Player& player) = default;
    Player& operator=(const Player& player) = default;
    ~Player() = default;

    void setLevel(int _Level);
    int getLevel() const;
    int getPlayerID() const;
    int getKey() const;
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