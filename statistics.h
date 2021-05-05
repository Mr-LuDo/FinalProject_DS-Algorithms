#ifndef STATISTICS_H
#define STATISTICS_H


#include "library1.h"
#include "Linked_list.h"
#include "Tree.h"

class Statistics {
    public:
        Statistics();
        ~Statistics();
        
        void Init(int N);                                           // OK
        StatusType PlantTree(int i, int j);                               // OK
        StatusType AddFruit(int i, int j, int fruitID, int ripeRate);     // OK
        StatusType PickFruit(int fruitID);                                // OK
        StatusType RateFruit(int fruitID, int ripeRate);                    // OK
        StatusType GetBestFruit(int i, int j, int* fruitID);                // OK
        StatusType GetAllFruitsByRate(int i, int j, int** fruits, int* numOffFruits);// kinda OK as long as the ripe rate is <= K_tree
        StatusType UpdateRottenFruits(int rottenBase, int rottenFactor);  // OK
        void Quit();                                                // OK


    //private:
        // helpers
        Node* FindTree(int i, int j, Node* start_point);
        void PrintLLPlantation();
        void PrintLLFruits();
        void StaPrintTree(int i, int j);
        int TreeID(int i, int j);

        LinkedListExtraData* Plantation_ll_;
        Tree* Plantation_tree_;
        int Plantation_size_;
        LinkedListExtraData* Fruits_ll_;

};

#endif // STATISTICS_H
