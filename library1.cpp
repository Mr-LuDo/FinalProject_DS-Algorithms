#include "library1.h"
#include "Statistics.h"

void* Init(int N){
    try {
        if (N < 0)
            return NULL;
        Statistics* DS = new Statistics(N);
        return (void*)DS;
    }
    catch (std::bad_alloc) {
        return NULL;
    }
}

StatusType PlantTree(void *DS, int i, int j){
    try {
        return ((Statistics*)DS)->PlantTree(i, j);
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType AddFruit(void *DS, int i, int j, int fruitID, int ripeRate){
    try {
        return ((Statistics*)DS)->AddFruit(i, j, fruitID, ripeRate);
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType PickFruit(void *DS, int fruitID){
    try {
        return ((Statistics*)DS)->PickFruit(fruitID);
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType RateFruit(void *DS, int fruitID, int ripeRate){
    try {
        return ((Statistics*)DS)->RateFruit(fruitID, ripeRate);
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType GetBestFruit(void *DS, int i, int j, int *fruitID){
    try {
        return ((Statistics*)DS)->GetBestFruit(i, j, fruitID);
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType GetAllFruitsByRate(void *DS, int i, int j, int **fruits, int *numOfFruits){
    try {
        return ((Statistics*)DS)->GetAllFruitsByRate(i, j, fruits, numOfFruits);
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType UpdateRottenFruits(void *DS, int rottenBase, int rottenFactor){
    try {
        return ((Statistics*)DS)->UpdateRottenFruits(rottenBase, rottenFactor);
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
}

void Quit(void** DS){
    delete *DS; 
    *DS = NULL;
    return;
}
