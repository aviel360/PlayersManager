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

    void setGroupID(int group_id);
    class Level& getLevel();
    int getPlayerID() const;
    int getGroupID() const;
};


#endif