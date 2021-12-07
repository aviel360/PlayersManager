//
// Created by Sofia Blyufer on 29/11/2021.
//

#ifndef PROJNAME_PLAYERSMANAGER_H
#define PROJNAME_PLAYERSMANAGER_H

#include <memory>
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
    AVLTree<std::shared_ptr<Player>>& createMergeTree(AVLTree<std::shared_ptr<Player>>& tree1, AVLTree<std::shared_ptr<Player>>& tree2, int n1,
                                                     int n2, int replace_id, AVLTree<std::shared_ptr<Player>>& playerTree);

    void mergeArrays(std::unique_ptr<std::shared_ptr<Player>*[]>& arr1, std::unique_ptr<std::shared_ptr<Player>*[]>& arr2, 
                        int n1, int n2, std::unique_ptr<std::shared_ptr<Player>*[]>& arr3);

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
    std::unique_ptr<T*[]> my_array;
public:
    array<T>(int _size):  size(_size), iter(0), my_array(new T*[size]) {}
    virtual ~array<T>(){}
    void insertT(T& val)
    {
        if ((iter + 1) > size)
        {
            throw Index();
        }
        my_array[iter] = &val;
    }
    virtual void operator()(T& value){
        insertT(value);
        iter++;
    }
    std::unique_ptr<T*[]>& get(){
        return my_array;
    }
    void clearArray(){
        iter = 0;
    }
    int getIter(){
        return this->iter;
    }
};

template <class T>
class arrayPtr : public array<T> {
    int** arr;
public:
    arrayPtr<T>(int _size, int** _arr) : array<T>(_size), arr(_arr) {}
    ~arrayPtr<T>(){}
    void insert(int player_id)
    {
        if ((this->iter + 1) > this->size)
        {
            throw Index();
        }
        (*arr)[this->iter] = player_id;
    }
    void operator () (std::shared_ptr<Player>& player)
    {
        insert((*player).getPlayerID());
        this->insertT(player);
        this->iter++;
    }
    void operator () (Group& group)
    {
        insert(group.getStrongestPlayer());
        this->insertT(group);
        this->iter++;
    }
};

class arrayMerge : public array<std::shared_ptr<Player>> {
    int groupID;
public:
    arrayMerge( int _size, int _groupID) : array<std::shared_ptr<Player>>(_size), groupID(_groupID) {}
    ~arrayMerge(){}
    void operator() (std::shared_ptr<Player>& player)
    {
        insertT(player);
        (*player).setGroupID(groupID);
        iter++;
    } 
};

// template <class T>
 class arrayInsert : public array<std::shared_ptr<Player>> {
 public:
    ~arrayInsert(){}
    arrayInsert(std::unique_ptr<std::shared_ptr<Player>*[]>& data, const int _size) : array<std::shared_ptr<Player>>(_size){
        for(int i = 0; i < size; i++){
            my_array[i] = data[i];
        }
    }
    void operator () (std::shared_ptr<Player>& p)
    {
        if ((iter + 1) > size)
        {
            throw Index();
        }
        p = *(my_array[iter]);
        iter ++;
    }
 };

#endif //PROJNAME_PLAYERSMANAGER_H
