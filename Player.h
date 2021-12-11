#ifndef PLAYERSMANAGER_PLAYER_H_
#define PLAYERSMANAGER_PLAYER_H_
struct Level{
    int PlayerLevel;
    int PlayerID;

    Level();
    Level(int key);
    Level(int _level, int player_id);
    Level(const Level& level) = default;
    ~Level() = default;
    Level& operator=(const Level& level) = default;

    friend bool operator==(const Level& level_a, const Level& level_b){
        return level_a.PlayerLevel == level_b.PlayerLevel && level_a.PlayerID == level_b.PlayerID;
    }
    friend bool operator<(const Level& level_a, const Level& level_b){
        if(level_a.PlayerLevel == level_b.PlayerLevel){
            return level_a.PlayerID > level_b.PlayerID;
        }
        return level_a.PlayerLevel < level_b.PlayerLevel;
    }
};
    bool operator>(const Level& level_a, const Level& level_b);
    bool operator<=(const Level& level_a, const Level& level_b);
    bool operator>=(const Level& level_a, const Level& level_b);
    bool operator!=(const Level& level_a, const Level& level_b);

class Player{
    int groupID;
    int PlayerID;
    Level PlayerLevel;

public:
    Player();
    Player(int group_id, int player_id, int _level);
    Player(const Player& player) = default;
    Player& operator=(const Player& player) = delete;
    ~Player() = default;

  //  void setLevel(int _level);
    void setGroupID(int group_id);
    class Level& getLevel();
    int getPlayerID() const;
    int getGroupID() const;
//    friend bool operator==(const Player& player_a, const Player& player_b){
//        return player_a.PlayerID == player_b.PlayerID;
//    }
//    friend bool operator<(const Player& player_a, const Player& player_b){
//        if(player_a.PlayerID == player_b.PlayerID){
//            return false;
//        }
//        return player_a.key == player_b.key ? player_a.PlayerID > player_b.PlayerID : player_a.key < player_b.key;
//    }
};
//    bool operator>(const Player& player_a, const Player& player_b);
//    bool operator<=(const Player& player_a, const Player& player_b);
//    bool operator>=(const Player& player_a, const Player& player_b);
//    bool operator!=(const Player& player_a, const Player& player_b);


#endif