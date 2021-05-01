#include "Statistics.h"

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;



Statistics::Statistics()
    : Plantation_ll_(nullptr), Plantation_tree_(nullptr), Plantation_size_(0),
      Fruits_ll_(nullptr)
{}

Statistics::~Statistics() {
    Quit();
    //delete Plantation_ll_;
    //delete Plantation_tree_;
    //delete Fruits_ll_;
}

void Statistics::Init(int N) {
    Plantation_ll_ = new LinkedListExtraData;
    Plantation_tree_ = new Tree(-1, Plantation_ll_);
    Plantation_size_ = N;
    Fruits_ll_ = new LinkedListExtraData;
}

void Statistics::PlantTree(int i, int j) {
    int treeID = TreeID(i, j);
    Node* tree_node = Plantation_tree_->AddNode(treeID);
    if (tree_node == nullptr) {
        cout << "tree node == nullptr " << endl;
        return;
    }
    tree_node->tree_ = new Tree(treeID, Fruits_ll_);
    //tree_node->PrintNode();
    cout << "--------------- tree_node->tree_->PrintTreeData() --------------" << endl;
    tree_node->tree_->PrintTreeData();
    cout << "--------------- --------------------------------- --------------" << endl;
    return;
}

void Statistics::AddFruit(int i, int j, int fruitID, int ripeRate) {
    int treeID = TreeID(i, j);
    Node* tree_node = FindTree(i, j, nullptr);
    if (tree_node->key_ != treeID) {
        PlantTree(i, j);
        tree_node = FindTree(i, j, tree_node);
    }
    Node* temp = tree_node->tree_->AddNode(fruitID);
    if (temp == nullptr) {
        cout << "temp node == nullptr " << endl;
        return;
    }
    //cout << "--------------- print node --------------" << endl;
    //temp->PrintNode();
    //cout << "--------------- ---------- --------------" << endl;

    return;
}

void Statistics::PickFruit(int fruitID) {
    Node* fruit = Fruits_ll_->Search(fruitID);
    fruit->tree_->DeleteNode(fruit);
    return;
}

void Statistics::RateFruit(int fruitID, int ripeRate) {
    Node* fruit = Fruits_ll_->Search(fruitID);
    fruit->ripeRate_ = ripeRate;

    return;
}

void Statistics::GetBestFruit(int i, int j) {
    int treeID = TreeID(i, j);
    return;
}

void Statistics::GetAllFruitsByRate(int i, int j) {
    int treeID = TreeID(i, j);
    return;
}

void Statistics::UpdateRottenFruits(int rottenBase, int rottenFactor) {
    Node* fruit = Fruits_ll_->Front();
    do {
        if (fruit->key_ % rottenBase == 0) {
            fruit->ripeRate_ *= rottenFactor;
        }
        fruit = Fruits_ll_->Next(fruit);
    } while (fruit != Fruits_ll_->Front());
    return;
}

//void Statistics::Quit(void** DS) {
void Statistics::Quit() {

    for(auto it : *Plantation_tree_) {
        delete it->tree_;
    }

    delete Plantation_ll_;
    delete Fruits_ll_;

    return;
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

