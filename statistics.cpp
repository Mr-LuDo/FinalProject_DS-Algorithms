#include "Statistics.h"
//#include "Counting_sort.cpp"
void RadixSort(Tree* tree, Node** fruits);

Statistics::~Statistics() {
    for (auto it : *Plantation_tree_) {
        delete it->tree_;
    }
    delete Plantation_ll_;
    delete Plantation_tree_;
    delete Fruits_ll_;
}

StatusType Statistics::PlantTree(int i, int j) {
    if (i < 0 || j < 0 || i >= Plantation_size_ || j >= Plantation_size_)
        return INVALID_INPUT;

    int treeID = TreeID(i, j);
    Node* tree_node = Plantation_tree_->AddNode(treeID, NULL);
    if (tree_node == nullptr)
        return FAILURE;

    tree_node->tree_ = new Tree(treeID, Fruits_ll_);
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
    if (temp == nullptr)
        return FAILURE;

    if (temp->key_ != fruitID)
        return FAILURE;

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
    fruit->tree_->UpdateBestAndWorstRipeRateNodes();
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

    *fruitID = tree_node->tree_->BestRipeRateNode()->key_;
    return SUCCESS;
}

StatusType Statistics::GetAllFruitsByRate(int i, int j, int** fruits, int* numOffFruits) {
    // ------------------- basics failures and simple case -------------------------------
    
    if (i < 0 || j < 0 || i >= Plantation_size_ || j >= Plantation_size_ || fruits == NULL || numOffFruits == NULL)
        return INVALID_INPUT; 
        
    int treeID = TreeID(i, j);
    Node* tree_node = FindTree(i, j, nullptr);
    if (tree_node == nullptr || tree_node->key_ != treeID) {
        *numOffFruits = 0;
        fruits = NULL;
        return FAILURE;
    }

    const int size = tree_node->tree_->size();
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

// ----------------------------------------------------------------------------------
    Node** fruits_array = new Node * [size];
    int pos = 0;
    for (auto it : *tree_node->tree_) {
        fruits_array[pos] = it;
        ++pos;
    }

    RadixSort(tree_node->tree_, fruits_array);

    *fruits = new int[size];
    for (int i = 0; i < size; ++i) {
        (*fruits)[i] = fruits_array[i]->key_;
    }

    *numOffFruits = size;
    return SUCCESS;
}

StatusType Statistics::UpdateRottenFruits(int rottenBase, int rottenFactor) {
    if (rottenBase < 1 || rottenFactor < 1)
        return INVALID_INPUT;

    bool* updated_trees = new bool[Plantation_tree_->size()]();
    Node* fruit = Fruits_ll_->Front();
    do {
        if (fruit->key_ % rottenBase == 0) {
            fruit->ripeRate_ *= rottenFactor;
            updated_trees[fruit->tree_->treeID_] = true;
        }
        fruit = Fruits_ll_->Next(fruit);
    } while (fruit != Fruits_ll_->Front());

    for (auto it : *Plantation_tree_) {
        if (updated_trees[it->tree_->treeID_] == true)
            it->tree_->UpdateBestAndWorstRipeRateNodes();
    }

    delete[] updated_trees;
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
        return Plantation_tree_->Search(treeID);
    else
        return Plantation_tree_->Search(treeID, start_point);
}

int Statistics::TreeID(int i, int j) {
    return i * Plantation_size_ + j;
}

void CountingSort(Node** fruits, int* nodes_rr_digits, int size) {

    const int TEN = 10;

    int* nodes_digit = new int[size]();
    int* temp_nodes_rr_digits = new int[size]();
    int* ripe_rate_counter = new int[TEN]();
    int* new_position_inorder = new int[TEN]();
    Node** temp_fruits = new Node*[size];

    // copy to temp array fruits by their order
    for (int i = 0; i < size; ++i) {
        temp_fruits[i] = fruits[i];
    }

    // retrieving the digit
    for (int i = 0; i < size; ++i) {
        nodes_digit[i] = nodes_rr_digits[i] % 10;
        nodes_rr_digits[i] /= 10;
        temp_nodes_rr_digits[i] = nodes_rr_digits[i];
    }
       
    // ---------------- counting how many have the same ripe rate ---------------------------------
    for (int i = 0; i < size; ++i) {
        ++ripe_rate_counter[nodes_digit[i]];
    }

    // -- rerouting each ripe rate according to its position (fruitID) and how many repetitions of ripe rate ---
    int sum_prev_nodes = 0;
    for (int i = 0; i < TEN; ++i) {
        if (ripe_rate_counter[i] == 0)
            continue;

        new_position_inorder[i] = sum_prev_nodes;
        sum_prev_nodes += ripe_rate_counter[i];
    }

    // ------------------------ setting fruits in their new position (in ordered) ---------------------------
    for (int i = 0; i < size; ++i) {
        int temp_digit = nodes_digit[i];

        fruits[new_position_inorder[nodes_digit[i]]] = temp_fruits[i];
        nodes_rr_digits[new_position_inorder[nodes_digit[i]]] = temp_nodes_rr_digits[i];
        ++new_position_inorder[nodes_digit[i]];

    }

    delete[] nodes_digit;
    delete[] temp_nodes_rr_digits;
    delete[] ripe_rate_counter;
    delete[] new_position_inorder;
    delete[] temp_fruits;

    return;
}

void RadixSort(Tree* tree, Node** fruits) {

    int temp = tree->WorstRipeRateNode()->ripeRate_;
    int numOffFruits = tree->size();

    int num_of_digits = 0;
    while (temp) {
        ++num_of_digits;
        temp /= 10;
    }

    int* nodes_rr_digits = new int[numOffFruits]();
    for (int j = 0; j < numOffFruits; ++j) {
        nodes_rr_digits[j] = fruits[j]->ripeRate_;
    }

    for (int i = 0; i < num_of_digits; ++i) {
        CountingSort(fruits, nodes_rr_digits, numOffFruits);
    }

    delete[] nodes_rr_digits;
    return;
}