#ifndef PLAYERSMANAGER_PLAYER_H_
#define PLAYERSMANAGER_PLAYER_H_

class Player{
    int key;
    int groupID;
    int PlayerID;
    int Level;
    
public:
    Player();
    Player(int _key, int groupID, int _PlayerId, int _Level = 0);
    Player(const Player& player) = default;
    Player& operator=(const Player& player) = default;
    ~Player() = default;

    void setLevel(int _Level);
    void setGroupID(int _groupID);
    int getLevel() const;
    int getPlayerID() const;
    int getKey() const;
    int getReturn() const;
    int getGroupID() const;
    void changePlayer();
    friend bool operator==(const Player& player_a, const Player& player_b){ 
        return player_a.PlayerID == player_b.PlayerID;
    }
    friend bool operator<(const Player& player_a, const Player& player_b){
        if(player_a.PlayerID == player_b.PlayerID){
            return false;
        }
        return player_a.key == player_b.key ? player_a.PlayerID > player_b.PlayerID : player_a.key < player_b.key;
    }
};
    bool operator>(const Player& player_a, const Player& player_b);
    bool operator<=(const Player& player_a, const Player& player_b);
    bool operator>=(const Player& player_a, const Player& player_b);
    bool operator!=(const Player& player_a, const Player& player_b);


#endif