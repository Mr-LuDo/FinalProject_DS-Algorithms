#ifndef STATISTICS_H
#define STATISTICS_H

#include "Linked_list.h"
#include "Tree.h"

class Statistics {
    public:
        Statistics();
        ~Statistics();
        
        void Init(int N);       // OK
        void PlantTree(int i, int j);   // OK
        void AddFruit(int i, int j, int fruitID, int ripeRate); // OK
        void PickFruit(int fruitID);    // OK
        void RateFruit(int fruitID, int ripeRate);
        void GetBestFruit(int i, int j);            // need to add to node best ripe rate node
        void GetAllFruitsByRate(int i, int j);      // kinka ok
        void UpdateRottenFruits(int rottenBase, int rottenFactor); // OK
        void Quit(); // Destructor???
        //void Quit(void** DS); // Destructor???

        Node* FindTree(int i, int j, Node* start_point);
        void PrintLLPlantation();
        void PrintLLFruits();
        void StaPrintTree(int i, int j);
        int TreeID(int i, int j);

    protected:

    private:
        LinkedListExtraData* Plantation_ll_;
        Tree* Plantation_tree_;
        int Plantation_size_;
        LinkedListExtraData* Fruits_ll_;

};

#endif // STATISTICS_H
