#ifndef STATISTICS_H
#define STATISTICS_H

#include "Linked_list.h"
#include "Tree.h"

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

class DataSructure {
    public:
        DataSructure() : Plantation_ll_(nullptr), Plantation_tree_(nullptr),
            Plantation_size_(0), Fruits_ll_(nullptr)
        {}

        ~DataSructure() {
            for (auto it : *Plantation_tree_) {
                delete it->tree_;
            }
            delete Plantation_ll_;
            delete Fruits_ll_;
        }

        LinkedListExtraData* Plantation_ll_;
        Tree* Plantation_tree_;
        int Plantation_size_;
        LinkedListExtraData* Fruits_ll_;
};

class Statistics {
    public:
        Statistics();
        ~Statistics();
        
        void* Init(int N);                                           // OK
        StatusType PlantTree(void* DS, int i, int j);                               // OK
        StatusType AddFruit(void* DS, int i, int j, int fruitID, int ripeRate);     // OK
        StatusType PickFruit(void* DS, int fruitID);                                // OK
        StatusType RateFruit(void* DS, int fruitID, int ripeRate);                    // OK
        StatusType GetBestFruit(void* DS, int i, int j, int* fruitID);                // OK
        StatusType GetAllFruitsByRate(void* DS, int i, int j, int** fruits, int* numOffFruits);// kinda OK as long as the ripe rate is <= K_tree
        StatusType UpdateRottenFruits(void* DS, int rottenBase, int rottenFactor);  // OK
        void Quit(void** DS);                                                // OK


    //private:
        // helpers
        Node* FindTree(void* DS, int i, int j, Node* start_point);
        void PrintLLPlantation(void* DS);
        void PrintLLFruits(void* DS);
        void StaPrintTree(void* DS, int i, int j);
        int TreeID(void* DS, int i, int j);

        //LinkedListExtraData* Plantation_ll_;
        //Tree* Plantation_tree_;
        //int Plantation_size_;
        //LinkedListExtraData* Fruits_ll_;

};

#endif // STATISTICS_H
