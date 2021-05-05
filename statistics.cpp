#include "Statistics.h"
class DataStructure;
class LinkedListExtraData;
class Tree;

Statistics::Statistics()
    //: Plantation_ll_(nullptr), Plantation_tree_(nullptr), Plantation_size_(0),
    //  Fruits_ll_(nullptr)
{}

Statistics::~Statistics() {
    //Quit(&DS);
    //delete Plantation_ll_;
    //delete Plantation_tree_;
    //delete Fruits_ll_;
}

void* Statistics::Init(int N) {
    DataSructure* DS = new DataSructure;
    DS->Plantation_ll_ = new LinkedListExtraData;
    DS->Plantation_tree_ = new Tree(-1, DS->Plantation_ll_);
    DS->Plantation_size_ = N;
    DS->Fruits_ll_ = new LinkedListExtraData;
    
    return DS;
}

StatusType Statistics::PlantTree(void* DS, int i, int j) {
    if (i >= ((DataSructure*)DS)->Plantation_size_ || j >= ((DataSructure*)DS)->Plantation_size_)
        return INVALID_INPUT;

    int treeID = TreeID(DS, i, j);
    Node* tree_node = ((DataSructure*)DS)->Plantation_tree_->AddNode(treeID, NULL);
    if (tree_node == nullptr) {
        cout << "tree node == nullptr " << endl;
        return ALLOCATION_ERROR;
    }
    tree_node->tree_ = new Tree(treeID, ((DataSructure*)DS)->Fruits_ll_);
    //tree_node->PrintNode();
    cout << "--------------- tree_node->tree_->PrintTreeData() --------------" << endl;
    tree_node->tree_->PrintTreeData();
    cout << "--------------- --------------------------------- --------------" << endl;

    return SUCCESS;
}

StatusType Statistics::AddFruit(void* DS, int i, int j, int fruitID, int ripeRate) {
    if (i >= ((DataSructure*)DS)->Plantation_size_ || j >= ((DataSructure*)DS)->Plantation_size_ || fruitID <= 0 || ripeRate <= 0)
        return INVALID_INPUT;

    int treeID = TreeID(DS, i, j);
    Node* tree_node = FindTree(DS, i, j, nullptr);
    if (tree_node == nullptr || tree_node->key_ != treeID)
        return FAILURE;

    //if (tree_node->key_ != treeID) {
    //    PlantTree(i, j);
    //    tree_node = FindTree(i, j, tree_node);
    //}

    Node* temp = tree_node->tree_->AddNode(fruitID, ripeRate);
    if (temp == nullptr) {
        //cout << "temp node == nullptr " << endl;
        return ALLOCATION_ERROR;
    }
    if (temp->key_ != fruitID)
        return FAILURE;
    //cout << "--------------- print node --------------" << endl;
    //temp->PrintNode();
    //cout << "--------------- ---------- --------------" << endl;

    return SUCCESS;
}

StatusType Statistics::PickFruit(void* DS, int fruitID) {
    if (fruitID <= 0)
        return INVALID_INPUT;

    Node* fruit = ((DataSructure*)DS)->Fruits_ll_->Search(fruitID);
    if (fruit->key_ != fruitID)
        return FAILURE;

    fruit->tree_->DeleteNode(fruit);
    return SUCCESS;
}

StatusType Statistics::RateFruit(void* DS, int fruitID, int ripeRate) {
    if (fruitID <= 0 || ripeRate <= 0)
        return INVALID_INPUT;

    Node* fruit = ((DataSructure*)DS)->Fruits_ll_->Search(fruitID);
    if (fruit->key_ != fruitID)
        return FAILURE;

    fruit->ripeRate_ = ripeRate;
    return SUCCESS;
}

StatusType Statistics::GetBestFruit(void* DS, int i, int j, int* fruitID) {
    if (i >= ((DataSructure*)DS)->Plantation_size_ || j >= ((DataSructure*)DS)->Plantation_size_) {
        *fruitID = 1;
        return INVALID_INPUT;
    }

    int treeID = TreeID(DS, i, j);
    Node* tree_node = FindTree(DS, i, j, nullptr);
    if (tree_node == nullptr || tree_node->key_ != treeID)
        return FAILURE;

    Node* best_fruit = tree_node->tree_->BestRipeRateNode();
    *fruitID = best_fruit->key_;
    return SUCCESS;
}

StatusType Statistics::GetAllFruitsByRate(void* DS, int i, int j, int** fruits, int* numOffFruits) {
    if (i >= ((DataSructure*)DS)->Plantation_size_ || j >= ((DataSructure*)DS)->Plantation_size_ || fruits == NULL || numOffFruits == NULL)
        return INVALID_INPUT; 
    
    int treeID = TreeID(DS, i, j);
    Node* tree_node = FindTree(DS, i, j, nullptr);
    if (tree_node == nullptr || tree_node->key_ != treeID) {
        *numOffFruits = 0;
        fruits = NULL;
        return FAILURE;
    }

    int size = tree_node->tree_->size();
    int* ripe_rate = new int[size];
    int* ripe_rate_fuitID = new int[size];

    for (int i = 0; i < size; ++i) {
        ripe_rate[i] = 0;
        ripe_rate_fuitID[i] = 0;
    }
    
    for (auto it : *tree_node->tree_)
        ++ripe_rate[it->ripeRate_];

    for (int i = 1, prev_pos = 0, prev_size; i < size; ++i) {
        if (ripe_rate[i] == 0)
            continue;

        prev_size = ripe_rate[prev_pos];
        int temp = ripe_rate[i];

        ripe_rate[i] = prev_pos + prev_size;
        prev_pos += temp;
    }

    for (auto it : *tree_node->tree_) {
        //int counter = 0;
        //while (ripe_rate_nodes[ripe_rate[it->ripeRate_] + counter] != nullptr) {
        //    ++counter;
        //}
        //ripe_rate_nodes[ripe_rate[it->ripeRate_] + counter] = it;
        //counter = 0;

        ripe_rate_fuitID[ripe_rate[it->ripeRate_]] = it->key_;
        ++ripe_rate[it->ripeRate_];
    }

    delete[] ripe_rate;
    *fruits = ripe_rate_fuitID;
    *numOffFruits = size;
    return SUCCESS;
}

StatusType Statistics::UpdateRottenFruits(void* DS, int rottenBase, int rottenFactor) {
    if (rottenBase < 1 || rottenFactor < 1)
        return INVALID_INPUT; 

    Node* fruit = ((DataSructure*)DS)->Fruits_ll_->Front();
    do {
        if (fruit->key_ % rottenBase == 0) {
            fruit->ripeRate_ *= rottenFactor;
        }
        fruit = ((DataSructure*)DS)->Fruits_ll_->Next(fruit);
    } while (fruit != ((DataSructure*)DS)->Fruits_ll_->Front());

    for (auto it : *((DataSructure*)DS)->Plantation_tree_) {
        it->tree_->BestRipeRateNode();
    }

    return SUCCESS;
}

//void Statistics::Quit(void** DS) {
void Statistics::Quit(void** DS) {

    //for(auto it : *Plantation_tree_) {
    //    delete it->tree_;
    //}

    //delete Plantation_ll_;
    //delete Fruits_ll_;
    delete DS;
    return;
}



// -------------------------- helpers ----------------------------------

void Statistics::PrintLLPlantation(void* DS) {
    cout << "--------------- print Plantation --------------" << endl;
    ((DataSructure*)DS)->Plantation_ll_->PrintLinkedList();
    PrintTree(*((DataSructure*)DS)->Plantation_tree_);
    cout << "--------------- End print Plantation  --------------" << endl;

}

void Statistics::PrintLLFruits(void* DS) {
    cout << "--------------- print Fruits --------------" << endl;
    ((DataSructure*)DS)->Fruits_ll_->PrintLinkedList();
    cout << "--------------- ---------- --------------" << endl;
}

void Statistics::StaPrintTree(void* DS, int i, int j) {
    cout << "--------------- print Tree --------------" << endl;
    Node* tree_node = FindTree(DS, i, j, nullptr);
    PrintTree(*tree_node->tree_);
    cout << "--------------- ---------- --------------" << endl;
}

Node* Statistics::FindTree(void* DS, int i, int j, Node* start_point) {
    int treeID = TreeID(DS, i, j);
    if(start_point == nullptr)
        return ((DataSructure*)DS)->Plantation_tree_->findPos(treeID);
    else
        return ((DataSructure*)DS)->Plantation_tree_->findPos(treeID, start_point);
}

int Statistics::TreeID(void* DS, int i, int j) {
    return i * ((DataSructure*)DS)->Plantation_size_ + j;
}

