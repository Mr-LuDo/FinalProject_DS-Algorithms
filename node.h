#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class LinkedListExtraData;
class Tree;


#define CHECK_FOR_NULL_PTR(node)      ( (node) ? (node->fruitID_) : 0 )


class Node {
    public:
        Node(int fruitID = -1) :
            linkedlist_(nullptr), ll_next_(nullptr), ll_previous_(nullptr),
            key_(0), treeID_(-1), fruitID_(fruitID), ripeRate_(0),
            tree_(nullptr), tree_parent_(nullptr), tree_left_(nullptr), tree_right_(nullptr),
            height_(0), balance_factor_(0)
            {}

        ~Node() = default;

        void UpdateTree(Tree* tree, Node* parent, Node* left, Node* right) {
            tree_ = tree;
            tree_parent_ = parent;
            tree_left_ = left;
            tree_right_ = right;
        }

        void PrintNode() {
            cout << "fruit data: " <<endl;
            cout << "fruitID_     = " << fruitID_ << endl;
            cout << "linkedlist_  = " << linkedlist_ << endl;
            cout << "ll_next_     = " << ll_next_ << endl;
            cout << "ll_previous_ = " << ll_previous_ <<endl;
            cout << "-------------" << endl;
            cout << "tree data: " << endl;
            cout << "tree_                  = " << treeID_;
            cout << "  at address: " << tree_ << endl;
            cout << "fruitID_               = " << fruitID_;
            cout << "  at address: " << this << endl;
            cout << "tree_parent_->fruitID_ = " << CHECK_FOR_NULL_PTR(tree_parent_);
            cout << "  at address: " << tree_parent_ << endl;
            cout << "tree_left_->fruitID_   = " << CHECK_FOR_NULL_PTR(tree_left_);
            cout << "  at address: " << tree_left_ << endl;
            cout << "tree_right_->fruitID_  = " << CHECK_FOR_NULL_PTR(tree_right_);
            cout << "  at address: " << tree_right_ << endl;
            cout << "-----------------------------" << endl;
            cout << "height_         = " << height_ << endl;
            cout << "balance_factor_ = " << balance_factor_ << endl;




        }

    // linked list 
        LinkedListExtraData* linkedlist_;
        Node* ll_next_;
        Node* ll_previous_;

        int key_;
        int treeID_;
        int fruitID_;
        int ripeRate_;

     // binary search tree
        Tree* tree_;
        Node* tree_parent_;
        Node* tree_left_;
        Node* tree_right_;
        
    //  AVL
        int height_;
        int balance_factor_;
};

#endif // NODE_H
