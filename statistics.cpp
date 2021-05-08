#include "Statistics.h"

//class DataStructure;
class LinkedListExtraData;
class Tree;

Statistics::Statistics()
    : Plantation_ll_(nullptr), Plantation_tree_(nullptr), Plantation_size_(0),
      Fruits_ll_(nullptr)
{}

Statistics::~Statistics() {
    for(auto it : *Plantation_tree_) {
        delete it->tree_;
    }
    delete Plantation_tree_;
    delete Plantation_ll_;
    delete Fruits_ll_;
    return;
}

void Statistics::Init(int N) {
    Plantation_ll_ = new LinkedListExtraData;
    Plantation_tree_ = new Tree(-1, Plantation_ll_);
    Plantation_size_ = N;
    Fruits_ll_ = new LinkedListExtraData;
    
    return;
}

StatusType Statistics::PlantTree(int i, int j) {
    if (i < 0 || j < 0 || i >= Plantation_size_ || j >= Plantation_size_)
        return INVALID_INPUT;

    int treeID = TreeID(i, j);
    Node* tree_node = Plantation_tree_->AddNode(treeID, NULL);
    if (tree_node == nullptr) {
        //cout << "tree node == nullptr " << endl;
        return FAILURE;
    }
    tree_node->tree_ = new Tree(treeID, Fruits_ll_);
    //tree_node->PrintNode();
    //cout << "--------------- tree_node->tree_->PrintTreeData() --------------" << endl;
    //tree_node->tree_->PrintTreeData();
    //cout << "--------------- --------------------------------- --------------" << endl;

    return SUCCESS;
}

StatusType Statistics::AddFruit(int i, int j, int fruitID, int ripeRate) {
    if (i < 0 || j < 0 || i >= Plantation_size_ || j >= Plantation_size_ || fruitID <= 0 || ripeRate <= 0)
        return INVALID_INPUT;

    int treeID = TreeID(i, j);
    Node* tree_node = FindTree(i, j, nullptr);
    if (tree_node == nullptr || tree_node->key_ != treeID)
        return FAILURE;

    Node* temp = tree_node->tree_->AddNode(fruitID, ripeRate);
    if (temp == nullptr) {
        //cout << "temp node == nullptr " << endl;
        return FAILURE;
    }
    if (temp->key_ != fruitID)
        return FAILURE;
    //cout << "--------------- print node --------------" << endl;
    //temp->PrintNode();
    //cout << "--------------- ---------- --------------" << endl;

    return SUCCESS;
}

StatusType Statistics::PickFruit(int fruitID) {
    if (fruitID <= 0)
        return INVALID_INPUT;

    Node* fruit = Fruits_ll_->Search(fruitID);
    if (fruit->key_ != fruitID)
        return FAILURE;

    fruit->tree_->DeleteNode(fruit);
    return SUCCESS;
}

StatusType Statistics::RateFruit(int fruitID, int ripeRate) {
    if (fruitID <= 0 || ripeRate <= 0)
        return INVALID_INPUT;

    Node* fruit = Fruits_ll_->Search(fruitID);
    if (fruit == nullptr || fruit->key_ != fruitID)
        return FAILURE;

    fruit->ripeRate_ = ripeRate;
    return SUCCESS;
}

StatusType Statistics::GetBestFruit(int i, int j, int* fruitID) {
    if (i < 0 || j < 0 || i >= Plantation_size_ || j >= Plantation_size_) {
        *fruitID = -1;
        return INVALID_INPUT;
    }

    int treeID = TreeID(i, j);
    Node* tree_node = FindTree(i, j, nullptr);

    if (tree_node->tree_->size() == NULL) {
        *fruitID = -1;
        return SUCCESS;
    }

    if (tree_node == nullptr || tree_node->key_ != treeID) {
        *fruitID = -1;
        return FAILURE;
    }

    Node* best_fruit = tree_node->tree_->BestRipeRateNode();
    *fruitID = best_fruit->key_;
    return SUCCESS;
}

StatusType Statistics::GetAllFruitsByRate(int i, int j, int** fruits, int* numOffFruits) {
    if (i < 0 || j < 0 || i >= Plantation_size_ || j >= Plantation_size_ || fruits == NULL || numOffFruits == NULL)
        return INVALID_INPUT; 
    
    int treeID = TreeID(i, j);
    Node* tree_node = FindTree(i, j, nullptr);
    if (tree_node == nullptr || tree_node->key_ != treeID) {
        *numOffFruits = 0;
        fruits = NULL;
        return FAILURE;
    }

    int size = tree_node->tree_->size();
    //cout << "size = " << size << endl;
    if (size == 0) {
        *fruits = NULL;
        *numOffFruits = size;
        return SUCCESS;
    }
    if (size == 1) {
        *fruits = new int[size];
        **fruits = tree_node->tree_->BestRipeRateNode()->key_;
        *numOffFruits = size;
        return SUCCESS;
    }

    int* ripe_rate = new int[size];
    int* new_position = new int[size];
    int* ripe_rate_fuitID = new int[size];
    int* ripe_rate_fuitID_rr = new int[size];

    for (int i = 0; i < size; ++i) {
        ripe_rate[i] = 0;
        new_position[i] = 0;
        ripe_rate_fuitID[i] = 0;
        ripe_rate_fuitID_rr[i] = 0;
    }
    
    for (auto it : *tree_node->tree_) {

        //cout << "----------------------------------------" << endl;
        //cout << "it->key_ = " << it->key_ << endl;
        //cout << "it->ripeRate_ = " << it->ripeRate_ << endl;
        //cout << "----------------------------------------" << endl;

        if (it->ripeRate_ >= size) {
            //cout << "ripeRate_ > size" << endl;
            continue;
        }
        ++ripe_rate[it->ripeRate_];
    }

    ////"----------------------------------------"
    //cout << "ripe rate before changes:" << endl;
    //for (int i = 0; i < size; ++i)
    //    cout << ripe_rate[i] << " ";
    //cout << endl;
    ////"----------------------------------------"
    int sum_prev_nodes = 0;
    for (int i = 1; i < size; ++i) {
        if (ripe_rate[i] == 0)
            continue;

        new_position[i] = sum_prev_nodes;
        sum_prev_nodes += ripe_rate[i];
    }

    ////"----------------------------------------"
    //cout << "new_position after changes:" << endl;
    //for (int i = 0; i < size; ++i)
    //    cout << new_position[i] << " ";
    //cout << endl;
    ////"----------------------------------------"

    for (auto it : *tree_node->tree_) {
        if (it->ripeRate_ >= size || new_position[it->ripeRate_] >= size) {
            //cout << "ripeRate_ > size" << endl;
            continue;
        }
        else {
            ripe_rate_fuitID[new_position[it->ripeRate_]] = it->key_;
            ripe_rate_fuitID_rr[new_position[it->ripeRate_]] = it->ripeRate_;
        }
        ++new_position[it->ripeRate_];
    }

    //-------------------------- this is for all ripe rate > size(k) ------------------------------------------
    for (int i = 0; i < size; ++i) {
        ripe_rate[i] = 0;
        new_position[i] = 0;
    }

    int last_pos = sum_prev_nodes;
    if (tree_node->tree_->BestRipeRateNode() == nullptr) {
        cout << "nullptr" << endl;
        return FAILURE;
    }

    int max_rr = tree_node->tree_->BestRipeRateNode()->ripeRate_;
    for (auto it : *tree_node->tree_) {
        if (it->ripeRate_ > max_rr)
            max_rr = it->ripeRate_;
    }    

    //cout << "----------------------------------------" << endl;
    //cout << "max rr = " << max_rr << endl;
    //cout << "size = " << size << endl;
    //cout << "last_pos = " << last_pos << endl;
    //cout << "----------------------------------------" << endl;

    int dx = ceil(double(max_rr - size) / (size - last_pos));
    //cout << "dx = " << dx << endl;

    for (auto it : *tree_node->tree_) {
        if (it->ripeRate_ >= size) {
            int new_pos = double(it->ripeRate_ - size) / dx;
            if (new_pos >= size - last_pos)
                new_pos = size - last_pos - 1;

            ++ripe_rate[last_pos + new_pos];
        }
    }

    ////"----------------------------------------"
    //cout << "ripe rate before changes:" << endl;
    //for (int i = 0; i < size; ++i)
    //    cout << ripe_rate[i] << " ";
    //cout << endl;
    ////"----------------------------------------"

    for (int i = sum_prev_nodes; i < size; ++i) {
        if (ripe_rate[i] == 0)
            continue;

        new_position[i] = sum_prev_nodes;
        sum_prev_nodes += ripe_rate[i];
    }

    ////"----------------------------------------"
    //cout << "new_position after changes:" << endl;
    //for (int i = 0; i < size; ++i)
    //    cout << new_position[i] << " ";
    //cout << endl;
    ////"----------------------------------------"
    for (auto it : *tree_node->tree_) {
        if (it->ripeRate_ < size )
            continue;        

        int new_pos = double(it->ripeRate_ - size) / dx;
        //cout << "new_pos = " << new_pos << endl;
        if (new_pos >= size - last_pos)
            new_pos = size - last_pos - 1;
        //cout << "new_pos = " << new_pos << endl;

        ripe_rate_fuitID[new_position[last_pos + new_pos]] = it->key_;
        ripe_rate_fuitID_rr[new_position[last_pos + new_pos]] = it->ripeRate_;

        ++new_position[last_pos + new_pos];
    }

    //"----------------------------------------"
    cout << "ripe_rate_fuitID_rr after changes:" << endl;
    for (int i = 0; i < size; ++i)
        cout << ripe_rate_fuitID_rr[i] << " ";
    cout << endl;
    //"----------------------------------------"


    delete[] ripe_rate;
    delete[] new_position;
    delete[] ripe_rate_fuitID_rr;
    *fruits = ripe_rate_fuitID;
    *numOffFruits = size;
    return SUCCESS;
}

// kinda working- previous version
//StatusType Statistics::GetAllFruitsByRate(int i, int j, int** fruits, int* numOffFruits) {
//    if (i < 0 || j < 0 || i >= Plantation_size_ || j >= Plantation_size_ || fruits == NULL || numOffFruits == NULL)
//        return INVALID_INPUT; 
//    
//    int treeID = TreeID(i, j);
//    Node* tree_node = FindTree(i, j, nullptr);
//    if (tree_node == nullptr || tree_node->key_ != treeID) {
//        *numOffFruits = 0;
//        fruits = NULL;
//        return FAILURE;
//    }
//
//    int size = tree_node->tree_->size();
//    //cout << "size = " << size << endl;
//
//    int* ripe_rate = new int[size];
//    int* ripe_rate_fuitID = new int[size];
//
//    for (int i = 0; i < size; ++i) {
//        ripe_rate[i] = 0;
//        ripe_rate_fuitID[i] = 0;
//    }
//    
//    for (auto it : *tree_node->tree_) {
//        if (it->ripeRate_ >= size) {
//            //cout << "ripeRate_ > size" << endl;
//            continue;
//        }
//        ++ripe_rate[it->ripeRate_];
//    }
//
//    for (int i = 1, prev_pos = 0, prev_size; i < size; ++i) {
//        if (ripe_rate[i] == 0)
//            continue;
//
//        prev_size = ripe_rate[prev_pos];
//        int temp = ripe_rate[i];
//
//        ripe_rate[i] = prev_pos + prev_size;
//        prev_pos += temp;
//    }
//
//    for (auto it : *tree_node->tree_) {
//        if (it->ripeRate_ >= size || ripe_rate[it->ripeRate_] >= size) {
//            //cout << "ripeRate_ > size" << endl;
//            continue;
//        }
//        else {
//            ripe_rate_fuitID[ripe_rate[it->ripeRate_]] = it->key_;
//        }
//        ++ripe_rate[it->ripeRate_];
//    }
//
//    delete[] ripe_rate;
//    *fruits = ripe_rate_fuitID;
//    *numOffFruits = size;
//    return SUCCESS;
//}

StatusType Statistics::UpdateRottenFruits(int rottenBase, int rottenFactor) {
    if (rottenBase < 1 || rottenFactor < 1)
        return INVALID_INPUT; 

    Node* fruit = Fruits_ll_->Front();
    do {
        if (fruit->key_ % rottenBase == 0) {
            fruit->ripeRate_ *= rottenFactor;
        }
        fruit = Fruits_ll_->Next(fruit);
    } while (fruit != Fruits_ll_->Front());

    for (auto it : *Plantation_tree_) {
        it->tree_->BestRipeRateNode();
    }

    return SUCCESS;
}

// -------------------------- helpers ----------------------------------

void Statistics::PrintLLPlantation() {
    cout << "--------------- print Plantation --------------" << endl;
    Plantation_ll_->PrintLinkedList();
    PrintTree(*Plantation_tree_);
    cout << "--------------- End print Plantation  --------------" << endl;

}

void Statistics::PrintLLFruits() {
    cout << "--------------- print Fruits --------------" << endl;
    Fruits_ll_->PrintLinkedList();
    cout << "--------------- ---------- --------------" << endl;
}

void Statistics::StaPrintTree(int i, int j) {
    cout << "--------------- print Tree --------------" << endl;
    Node* tree_node = FindTree(i, j, nullptr);
    PrintTree(*tree_node->tree_);
    cout << "--------------- ---------- --------------" << endl;
}

Node* Statistics::FindTree(int i, int j, Node* start_point) {
    int treeID = TreeID(i, j);
    if(start_point == nullptr)
        return Plantation_tree_->findPos(treeID);
    else
        return Plantation_tree_->findPos(treeID, start_point);
}

int Statistics::TreeID(int i, int j) {
    return i * Plantation_size_ + j;
}

