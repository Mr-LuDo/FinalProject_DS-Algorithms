#include "library1.h"
#include "Statistics.h"

void* Init(int N){
    Statistics *DS = new Statistics(); // Call constructor
    DS->Init(N);
    return (void*)DS;
}

StatusType PlantTree(void *DS, int i, int j){
    return ((Statistics*)DS)->PlantTree(i, j);
}

StatusType AddFruit(void *DS, int i, int j, int fruitID, int ripeRate){
    return ((Statistics*)DS)->AddFruit(i, j, fruitID, ripeRate);
}

StatusType PickFruit(void *DS, int fruitID){
    return ((Statistics*)DS)->PickFruit(fruitID);
}

StatusType RateFruit(void *DS, int fruitID, int ripeRate){
    return ((Statistics*)DS)->RateFruit(fruitID, ripeRate);
}

StatusType GetBestFruit(void *DS, int i, int j, int *fruitID){
    return ((Statistics*)DS)->GetBestFruit(i, j, fruitID);
}

StatusType GetAllFruitsByRate(void *DS, int i, int j, int **fruits, int *numOfFruits){
    return ((Statistics*)DS)->GetAllFruitsByRate(i, j, fruits, numOfFruits);
}

StatusType UpdateRottenFruits(void *DS, int rottenBase, int rottenFactor){
    return ((Statistics*)DS)->UpdateRottenFruits(rottenBase, rottenFactor);
}


void Quit(void** DS){
    delete *DS; // Call destructor
    *DS = NULL;
    return;
}
