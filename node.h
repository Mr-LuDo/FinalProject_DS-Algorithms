#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class LinkedListExtraData;
class Tree;


#define CHECK_FOR_NULL_PTR(node)      ( (node) ? (node->key_) : 0 )


class Node {
    public:
        Node(int key = -1) :
            linkedlist_(nullptr), ll_next_(nullptr), ll_previous_(nullptr),
            key_(key), treeID_(-1), ripeRate_(0), tree_(nullptr),
            parent_tree_(nullptr), left_tree_(nullptr), right_tree_(nullptr),
            height_(0), balance_factor_(0)
        {}

        ~Node() = default;

        void PrintNode() {
            cout << "------------- PrintNode ----------------" << endl;

            cout << "key data: " <<endl;
            cout << "key_         = " << key_ << endl;
            cout << "linkedlist_  = " << linkedlist_ << endl;
            cout << "ll_next_     = " << ll_next_ << endl;
            cout << "ll_previous_ = " << ll_previous_ <<endl;
            cout << "-------------" << endl;
            cout << "tree data: " << endl;
            cout << "tree_                  = " << treeID_;
            cout << "  at address: " << tree_ << endl;
            cout << "key_                   = " << key_ << endl;
            cout << "parent_tree_->key_ = " << CHECK_FOR_NULL_PTR(parent_tree_);
            cout << "  at address: " << parent_tree_ << endl;
            cout << "left_tree_->key_   = " << CHECK_FOR_NULL_PTR(left_tree_);
            cout << "  at address: " << left_tree_ << endl;
            cout << "right_tree_->key_  = " << CHECK_FOR_NULL_PTR(right_tree_);
            cout << "  at address: " << right_tree_ << endl;
            cout << "-----------------------------" << endl;
            cout << "height_         = " << height_ << endl;
            cout << "balance_factor_ = " << balance_factor_ << endl;
            cout << "------------- End PrintNode ----------------" << endl;

        }

    // linked list 
        LinkedListExtraData* linkedlist_;
        Node* ll_next_;
        Node* ll_previous_;

        int key_;
        int treeID_;
        int ripeRate_;

     // binary search tree
        Tree* tree_;
        Node* parent_tree_;
        Node* left_tree_;
        Node* right_tree_;
        
    //  AVL
        int height_;
        int balance_factor_;
};

#endif // NODE_H
