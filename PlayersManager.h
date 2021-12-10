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


    Group& findPlayerGroup(int player_id);
    bool groupExists(const int group_id);
    void arrayMalloc(int size, int* sizePtr, int** arrayPtr);
    AVLTree<Player>& createMergeTree(AVLTree<Player>& tree1, AVLTree<Player>& tree2, int n1,
                                                     int n2, int replace_id, AVLTree<Player>& playerTree);
    void swap(int** Players, int size);
    void mergeArrays(std::shared_ptr<Player>* arr1, std::shared_ptr<Player>* arr2, int n1, int n2, std::shared_ptr<Player>* arr3);

public:

    PlayersManager();
    ~PlayersManager() = default;
    void addGroup(const int id); 
    void addPlayer(const int player_id, const int group_id, const int level);
    void removePlayer(const int player_id);
    void replaceGroup(const int group_id, const int replace_id);
    void increaseLevel(const int player_id, const int new_level);
    int getHighestLevel(const int group_id);
    void getAllPlayersByLevel(const int group_id, int** Players, int* numOfPlayers);
    void getGroupsHighestLevel(const int numOfGroups, int** Players);
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
    void insertT(T& val)
    {
        if ((iter + 1) > size)
        {
            throw Index();
        }
        my_array[iter] = val;
    }
    void insertTP(T& val)
    {
        if ((iter + 1) > size)
        {
            throw Index();
        }
        my_array[size - iter -1] = val;
    }
    virtual void operator()(T& value){
        insertT(value);
        iter++;
    }
    T* get(){
        return my_array;
    }
    void clearArray(){
        iter = 0;
    }
    int getIter(){
        return this->iter;
    }
    void setIter(int _iter){
        this->iter = _iter;
    }
};

template <class T>
class arrayPtr : public array<T> {
    int** arr;
public:
    arrayPtr<T>(int _size, int** _arr) : array<T>(_size), arr(_arr) {}
    ~arrayPtr<T>(){}
    void insertG(int player_id)
    {
        if ((this->iter + 1) > this->size)
        {
            throw Index();
        }
        (*arr)[this->iter] = player_id;
    }
    void insertP(int player_id)
    {
        if ((this->iter + 1) > this->size)
        {
            throw Index();
        }
        (*arr)[this->size - this->iter - 1] = player_id;
    }
    void operator () (std::shared_ptr<Player>& player)
    {
        insertP(player->getPlayerID());
        this->insertTP(player);
        this->iter++;
    }
    void operator () (std::shared_ptr<Group>& group)
    {
        insertG(group->getStrongestPlayer());
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
        this->insertT(player);
        player->setGroupID(groupID);
        iter++;
    }
    std::shared_ptr<Player>* getArr(){
        return this->get();
    }
};

// template <class T>
class arrayInsert : public array<std::shared_ptr<Player>> {
public:
    ~arrayInsert(){}
    arrayInsert(std::shared_ptr<Player>* data, const int _size) : 
                    array<std::shared_ptr<Player>>(_size){
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
        p = my_array[iter];
        iter ++;
    }
};

#endif //PROJNAME_PLAYERSMANAGER_H
