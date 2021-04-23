#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class LinkedListExtraData;
class Tree;

class Node {
    public:
        Node(int fruitID) :
            fruitID_(fruitID), ll_source_(nullptr),
            ll_next_(nullptr), ll_previous_(nullptr), treeID_(-1), tree_(nullptr),
            tree_parent_(nullptr), tree_left_(nullptr), tree_right_(nullptr)
            {}

//        Node(int fruitID, int treeID) :
//            fruitID_(fruitID), ll_source_(nullptr),
//            ll_next_(nullptr), ll_previous_(nullptr), treeID_(treeID) {}

        void UpdateTree(Node* parent,Node* left, Node* right, Tree* tree) {
            tree_ = tree;
            tree_parent_ = parent;
            tree_left_ = left;
            tree_right_ = right;
        }

        void PrintNode() {
            cout << "fruit data: " <<endl;
            cout << "fruitID_ = " << fruitID_ << endl;
            cout << "ll_source_ = " << ll_source_ << endl;
            cout << "ll_next_ = " << ll_next_ << endl;
            cout << "ll_previous_ = " << ll_previous_ <<endl;
            cout << "-------------" << endl;
            cout << "tree data: " << endl;
            cout << "treeID_ = " << treeID_ << endl;
            cout << "tree_this_ = " << this << endl;
            cout << "tree_parent_ = " << tree_parent_ << endl;
            cout << "tree_left_ = " << tree_left_ << endl;
            cout << "tree_right_ = " << tree_right_ << endl;
        }

        bool operator==(Node& other) {
            if(fruitID_ == other.fruitID_ &&
               ll_next_ == other.ll_next_ &&
               ll_previous_ == other.ll_previous_ )
                cout << "node == node" << endl;
                return true;
            cout << "node != node" << endl;
            return false;
        }

        bool operator!=(Node& other) {
            return !(*this == other);
        }

        int fruitID_;
        LinkedListExtraData* ll_source_;
        Node* ll_next_;
        Node* ll_previous_;

        int treeID_;
        Tree* tree_;
        Node* tree_parent_;
        Node* tree_left_;
        Node* tree_right_;

};

#endif // NODE_H
