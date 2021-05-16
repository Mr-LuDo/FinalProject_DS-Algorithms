#ifndef STATISTICS_H
#define STATISTICS_H

#include "library1.h"
#include "Linked_list.h"
#include "Tree.h"

class Statistics {
    public:
        Statistics(int N)
          : Plantation_ll_(new LinkedListExtraData),
            Plantation_tree_(new Tree(-1, Plantation_ll_)),
            Plantation_size_(N), Fruits_ll_(new LinkedListExtraData)
        {}
        ~Statistics();
        
        StatusType PlantTree(int i, int j);                                             // OK
        StatusType AddFruit(int i, int j, int fruitID, int ripeRate);                   // OK
        StatusType PickFruit(int fruitID);                                              // OK
        StatusType RateFruit(int fruitID, int ripeRate);                                // OK
        StatusType GetBestFruit(int i, int j, int* fruitID);                            // OK
        StatusType GetAllFruitsByRate(int i, int j, int** fruits, int* numOffFruits);   // OK
        StatusType UpdateRottenFruits(int rottenBase, int rottenFactor);                // OK

    // helpers
    private:
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
