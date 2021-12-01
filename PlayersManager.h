//
// Created by Sofia Blyufer on 29/11/2021.
//

#ifndef PROJNAME_PLAYERSMANAGER_H
#define PROJNAME_PLAYERSMANAGER_H

#include <iostream>
#include "AVLTree.h"
#include "Player.h"
#include "Group.h"
#include "Exceptions.h"

enum StatusType{
    SUCCESS,
    ALLOCATION_ERROR,
    INVALID_INPPUT,
    FAILURE
}; // here?

class PlayersManager{
    AVLTree<Group> eGroup;
    AVLTree<Group> fGroup;
    Group players;
    int strongestPlayerID;


    Group& findPlayerGroup(int player_id);
    bool groupExists(const int group_id);
    void arrayMalloc(int size, int* sizePtr, int** arrayPtr);

public:

//    static PlayersManager* Init();
    PlayersManager();
    ~PlayersManager() = default;
    void addGroup(const int& id); //maybe void?
    void addPlayer(const int& player_id, const int& group_id, const int& level);
    void removePlayer(const int& player_id);
    void replaceGroup(const int& group_id, const int& replace_id);
    void increaseLevel(const int& player_id, const int& new_level);
    int getHighestLevel(const int group_id);
    void getAllPlayersByLevel(const int& group_id, int** Players, int* numOfPlayers);
    void getGroupsHighestLevel(const int numOfGroups, int** Players);
//    void Quit();
};

template <class T>
class print {
public:
    void operator () (const T& t)
    {
        std::cout << t << std::endl;
    }
};

class array {
    int size;
    int** arr;
    int iter;
public:
    array(int _size, int** _arr):  size(_size), arr(_arr), iter(0) {};
    void insert(int player_id)
    {
        if ((iter + 1) >= size)
        {
            throw Index();
        }
        *arr[iter] = player_id; //maybe new?
        iter ++;
    }
    int* get() {
        return *arr;
    }
    void operator () (Player& player)
    {
        insert(player.getPlayerID());
    }
    void operator () (Group& group)
    {
        insert(group.getStrongestPlayer());
    }
};

// template <class T>
// class Add {
//     array my_array;
// public:
//     Add(array<int> _arr): my_array(_arr) {};
//     void operator () (const T& t)
//     {
//         my_array.insert(t.getReturn());
//     }
// };

#endif //PROJNAME_PLAYERSMANAGER_H
