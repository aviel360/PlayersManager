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

class PlayersManager{
    AVLTree<Group> eGroup;
    AVLTree<Group> fGroup;
    Group players;
    int strongestPlayerID;


    Group& findPlayerGroup(int player_id);
    bool groupExists(const int group_id);
    void arrayMalloc(int size, int* sizePtr, int** arrayPtr);
    AVLTree<Player>& createMergeTree(AVLTree<Player>& tree1, AVLTree<Player>& tree2, int n1, 
                                            int n2, int replace_id);

public:

//    static PlayersManager* Init();
    PlayersManager();
    ~PlayersManager() = default;
    void addGroup(const int id); //maybe void?
    void addPlayer(const int player_id, const int group_id, const int level);
    void removePlayer(const int player_id);
    void replaceGroup(const int group_id, const int replace_id);
    void increaseLevel(const int player_id, const int new_level);
    int getHighestLevel(const int group_id);
    void getAllPlayersByLevel(const int group_id, int** Players, int* numOfPlayers);
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

template <class T>
class array {
protected:
    int size;
    int iter;
    T* my_array;
public:
    array<T>(int _size):  size(_size), iter(0), my_array(new T[size]) {}
    virtual ~array<T>(){
        delete[] my_array;
    }
    void insert(T val)
    {
        if ((iter + 1) >= size)
        {
            throw Index();
        }
        my_array[iter] = val;
    }
    virtual void operator()(T& value){
        insert(value);
        iter++;
    }
    T* getArray(){
        return this->my_array;
    }
    void clearArray(){
        iter = 0;
    }
    int getIter(){
        return this->iter;
    }
};

template <class T>
class arrayPtr : array<T> {
    int** arr;
public:
    arrayPtr<T>(int _size, int** _arr) : array<T>(_size), arr(_arr) {}
    ~arrayPtr<T>() = default;
    void insert(int player_id)
    {
        if ((iter + 1) >= size)
        {
            throw Index();
        }
        *arr[iter] = player_id;
    }
    void operator () (Player& player)
    {
        insert(player.getPlayerID());
        insert(player);
        iter++;
    }
    void operator () (Group& group)
    {
        insert(group.getStrongestPlayer());
        insert(group);
        iter++;
    }
};

class arrayMerge : array<Player> {
    int groupID;
public:
    arrayMerge( int _size, int _groupID) : array<Player>(_size), groupID(_groupID) {}
    ~arrayMerge() = default;
    void operator() (Player& player)
    {
        insert(player);
        player.setGroupID(groupID);
        iter++;
    }
    Player* get(){
        return getArray();
    }
};

// template <class T>
 class arrayInsert : array<Player> {
 public:
    arrayInsert(Player* data, const int _size) : array<Player>(_size){
        delete[] my_array;
        my_array = data;
    }
    void operator () (Player& p)
    {
        if ((iter + 1) >= size)
        {
            throw Index();
        }
        p = my_array[iter];
        iter ++;
    }
 };

#endif //PROJNAME_PLAYERSMANAGER_H
