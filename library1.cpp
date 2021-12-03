#include"PlayersManager.h"
#include"library1.h"

void* Init() {
    try{
        PlayersManager *DS = new PlayersManager();
        return (void*)DS;
    }
    catch(...){
        return nullptr;
    }
}
StatusType AddGroup(void *DS, int GroupID){
    if((PlayersManager*)DS == nullptr){
        return INVALID_INPUT;
    }
    try{
        ((PlayersManager*)DS)->addGroup(GroupID);
    }
    catch(ValueExists& e){
        return FAILURE;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch(InvalidInput& e){
        return INVALID_INPUT;
    }
    return SUCCESS;
}
StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level){
    if((PlayersManager*)DS == nullptr){
        return INVALID_INPUT;
    }
    try{
        ((PlayersManager*)DS)->addPlayer(PlayerID, GroupID, Level);
    }
    catch(ValueExists& e){
        return FAILURE;
    }
    catch(ValueNotExists& e){
        return FAILURE;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch(InvalidInput& e){
        return INVALID_INPUT;
    }   
    return SUCCESS;
}
StatusType RemovePlayer(void *DS, int PlayerID){
    if((PlayersManager*)DS == nullptr){
        return INVALID_INPUT;
    }
    try{
        ((PlayersManager*)DS)->removePlayer(PlayerID);
    }
    catch(ValueNotExists& e){
        return FAILURE;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}
StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID){
    if((PlayersManager*)DS == nullptr){
        return INVALID_INPUT;
    }
    try{
        ((PlayersManager*)DS)->replaceGroup(GroupID, ReplacementID);
    }
    catch(ValueNotExists& e){
        return FAILURE;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch(InvalidInput& e){
        return INVALID_INPUT;
    } 
    return SUCCESS;  
}
StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease){
    if((PlayersManager*)DS == nullptr){
        return INVALID_INPUT;
    }
    try{
        ((PlayersManager*)DS)->increaseLevel(PlayerID, LevelIncrease);
    }
    catch(ValueNotExists& e){
        return FAILURE;
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch(InvalidInput& e){
        return INVALID_INPUT;
    } 
    return SUCCESS;  
}
