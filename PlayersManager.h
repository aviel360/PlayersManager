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

    template <class T>
    void mergeArrays(T arr1[], T arr2[], int n1,
                     int n2, T arr3[])
    {
        int i = 0, j = 0, k = 0;

        while (i<n1 && j <n2)
        {
            if (arr1[i] < arr2[j])
                arr3[k++] = arr1[i++];
            else
                arr3[k++] = arr2[j++];
        }

        while (i < n1)
            arr3[k++] = arr1[i++];

        while (j < n2)
            arr3[k++] = arr2[j++];
    }

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

template <class T>
class array {
    int size;
    int** arr;
    int iter;
    T* my_array;
    int T_iter;
public:
    array<T>(int _size, int** _arr):  size(_size), arr(_arr), iter(0), my_array(new T[size]), T_iter(0) {}
    ~array()
    {
        delete my_array;
    }
    void insert(int player_id)
    {
        if ((iter + 1) >= size)
        {
            throw Index();
        }
        *arr[iter] = player_id; //maybe new?
        iter ++;
    }
    void T_insert(T val)
    {
        if ((T_iter + 1) >= size)
        {
            throw Index();
        }
        my_array[T_iter] = val; //maybe new?
        T_iter ++;
    }
    int* get() {
        return *arr;
    }

    T* T_get() {
        return my_array;
    }

    void operator () (Player& player)
    {
        insert(player.getPlayerID());
        T_insert(player);
    }
    void operator () (Group& group)
    {
        insert(group.getStrongestPlayer());
    }
};

// template <class T>
 class Insert {
     Player* my_array;
     int size;
     int iter;
 public:
     Insert(Player* data, const int& s): size (s), my_array(data) , iter(0) {};
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
