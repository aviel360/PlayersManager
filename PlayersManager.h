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
    Group& groupExists(const int group_id);

public:

//    static PlayersManager* Init();
    PlayersManager() = default;
    ~PlayersManager() = default;
    void addGroup(const int& id); //maybe void?
    void addPlayer(const int& player_id, const int& group_id, const int& level);
    void removePlayer(const int& player_id);
    void replaceGroup(const int& group_id, const int& replace_id);
    void increaseLevel(const int& player_id, const int& new_level);
    int getHighestLevel(const int group_id, const int player_id);
    void getAllPlayersByLevel(const int& group_id, int** Players, int* numOfPlayers);
    void getGroupsHighestLevel(const int& numOfGroups, int** Players);
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

template <class T>
class array {
    int size;
    T* arr;
    int iter;
public:
    array(const int& s):  size(s), arr(new T[size]), iter(0) {};
    void insert(const T& t)
    {
        if ((iter + 1) >= size)
        {
            throw Index();
        }
        arr[iter] = t; //maybe new?
        iter ++;
    }
    T* get() {
        return arr;
    }
};
template <class T>
class Add {
    array<int> my_array;
public:
    Add(array<int> _arr): my_array(_arr) {};
    void operator () (const T& t)
    {
        my_array.insert(t.getReturn());
    }
};

#endif //PROJNAME_PLAYERSMANAGER_H
