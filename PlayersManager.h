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
    AVLTree<std::shared_ptr<Group>, int> eGroup;
    AVLTree<std::shared_ptr<Group>, int> fGroup;
    Group players;


    int findPlayerGroup(int player_id);
    bool groupExists(const int group_id);
    static void arrayMalloc(int size, int* sizePtr, int** arrayPtr);
    template<class T>
    AVLTree<std::shared_ptr<Player>, T>& createMergeTree(AVLTree<std::shared_ptr<Player>, T>& tree1,
                        AVLTree<std::shared_ptr<Player>, T>& tree2, int n1, int n2, int replace_id,
                        AVLTree<std::shared_ptr<Player>, T>& playerTree);
 //   void swap(int** Players, int size);
    template<class T>
    void mergeArrays(std::shared_ptr<Player>* arr1, std::shared_ptr<Player>* arr2,
                     T* keys1, T* keys2, int n1, int n2,
                     std::shared_ptr<Player>* arr3, T* keys3);

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

template <class T, class K>
class array {
protected:
    int size;
    int iter;
    std::shared_ptr<T>* my_array;
    K* keys;
public:
    array<T, K>(int _size):  size(_size), iter(0), my_array(new std::shared_ptr<T>[size]), keys(new K[size]) {
        for(int i = 0; i < size; i++){
            my_array[i] = std::make_shared<T>(T());
            keys[i] = K();
        }
    }
    virtual ~array<T, K>(){
        delete[] my_array;
        delete[] keys;
    }
    void insertT(std::shared_ptr<T>& val, K& key, int iter)
    {
        if ((iter + 1) > size)
        {
            throw Index();
        }
        std::shared_ptr<T> _value = val;
        my_array[iter] = _value;
        keys[iter] = key;
    }
    virtual void operator()(std::shared_ptr<T>& value, K& key){
        std::shared_ptr<T> _value = value;
        insertT(_value, key, iter);
        iter++;
    }
    std::shared_ptr<T>* getArr(){
        return my_array;
    }
    K* getKeys(){
        return keys;
    }
    int getIter(){
        return this->iter;
    }
};

template <class T, class K>
class arrayPtr : public array<T, K> {
    int** arr;
public:
    arrayPtr<T, K>(int _size, int** _arr) : array<T, K>(_size), arr(_arr) {}
    ~arrayPtr<T, K>(){}
    void insert(int player_id, int iter)
    {
        if ((this->iter + 1) > this->size)
        {
            throw Index();
        }
        (*arr)[this->size - this->iter - 1] = player_id;
    }
    void operator () (std::shared_ptr<Player>& player, Level level)
    {
        std::shared_ptr<Player> _player = player;
        insert(player->getPlayerID(), this->size - this->iter - 1);
        this->insertT(_player, level, this->size - this->iter - 1);
        this->iter++;
    }
    void operator () (std::shared_ptr<Group>& group, int group_id)
    {
        std::shared_ptr<Group> _group = group;
        insert(group->getStrongestPlayer().PlayerID, this->iter);
        this->insertT(_group, group_id, this->iter);
        this->iter++;
    }
};

template<class K>
class arrayMerge : public array<Player, K> {
    int groupID;
public:
    arrayMerge<K>( int _size, int _groupID) : array<Player, K>(_size), groupID(_groupID) {}
    ~arrayMerge<K>(){}
    void operator() (std::shared_ptr<Player>& player, K& key)
    {
        std::shared_ptr<Player> _player = player;
        this->insertT(_player, key, this->iter);
        player->setGroupID(groupID);
        this->iter++;
    }
};

template <class K>
class arrayInsert : public array<Player, K> {
public:
    ~arrayInsert<K>(){}
    arrayInsert<K>(std::shared_ptr<Player>* data, K* keys, const int _size) : array<Player, K>(_size){
        for(int i = 0; i < this->size; i++){
            this->my_array[i] = data[i];
            this->keys[i] = keys[i];
        }
    }
    void operator () (std::shared_ptr<Player>& p, K& key)
    {
        if ((this->iter + 1) > this->size)
        {
            throw Index();
        }
        std::shared_ptr<Player> _player = this->my_array[this->iter];
        p = _player;
        key = this->keys[this->iter];
        this->iter ++;
    }
};

#endif //PROJNAME_PLAYERSMANAGER_H
