#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;

#include "Node.h"
#include "Linked_list.h"

void PrintTree(Tree& tree);

class Tree
{
    public:
        Tree(int treeID, LinkedListExtraData* ll) :
            treeID_(treeID), isEmpty_(true), tree_size_(0), linkedlist_(ll),
            root_(nullptr), lowest_node_(nullptr), highest_node_(nullptr),
            lowest_ripe_rate_(0), highest_ripe_rate_(0), lowest_ripe_rate_node_(nullptr)
        {}

        virtual ~Tree() = default;

        Node* AddNode(int key, int ripe_rate) {
            if (linkedlist_->PushFront(key, treeID_, this) == false) {
                //cout << "linkedlist_->PushFront(key, treeID_, this) == false" << endl;
                return nullptr;
            }

            Node* temp_node = linkedlist_->Front();
            temp_node->ripeRate_ = ripe_rate;

            if(isEmpty_) {
                //cout << "tree is empty" << endl;
                isEmpty_ = false;
                ++tree_size_;
                root_ = lowest_node_ = highest_node_ = temp_node;
                UpdateRoot(this, nullptr, nullptr, nullptr);
            }
            else {
                Node* pos = findPos(key);
                if(pos == temp_node) {
                    //cout << "key already exist" << endl;
                    return pos;
                }
                if(key < pos->key_) {
                    if(UpdateLeft(pos, temp_node))
                        ++tree_size_;
                    if(key < lowest_node_->key_)
                        lowest_node_ = temp_node;
                }
                else {
                    if(UpdateRight(pos, temp_node)) 
                        ++tree_size_;
                    if(key > highest_node_->key_)
                        highest_node_ = temp_node;
                }
            }
            BalanceTree(temp_node);

            if (lowest_ripe_rate_node_ == nullptr)
                lowest_ripe_rate_node_ = temp_node;
            else {
                if (temp_node->ripeRate_ < lowest_ripe_rate_node_->ripeRate_)
                    lowest_ripe_rate_node_ = temp_node;
            }

            return temp_node;
        }

        void UpdateRoot(Tree* tree, Node* parent, Node* left, Node* right) {
            //root_->tree_ = tree;
            root_->parent_tree_ = parent;
            root_->left_tree_ = left;
            root_->right_tree_ = right;
        }

        bool UpdateLeft(Node* node, Node* newLeft_node) {
            if(node->left_tree_ == nullptr) {
                //node->tree_= this;
                node->left_tree_ = newLeft_node;
                newLeft_node->parent_tree_ = node;
                return true;
            }
            else {
                cout << "left son not empty, no action were taken." << endl;
                return false;
            }
        }

        bool UpdateRight(Node* node, Node* newRight_node) {
            if(node->right_tree_ == nullptr) {
                //node->tree_= this;
                node->right_tree_ = newRight_node;
                newRight_node->parent_tree_ = node;
                return true;
            }
            else {
                cout << "right son not empty, no action were taken." << endl;
                return false;
            }
        }

        void DeleteNode(int key) {
            Node* node = findPos(key);
            if (node->key_ != key)
                return;
            DeleteNode(node);
        }
        
        void DeleteNode(Node* node) {
            Node* parent = node->parent_tree_;
            
            if (node->left_tree_ == nullptr && node->right_tree_ == nullptr) {
                DeleteLeaf(node);
            }
            else {
                if (node->left_tree_ == nullptr || node->right_tree_ == nullptr) {
                    DeleteNodeWithOnechild(node);
                }
                else {
                    //cout << "swap" << endl;
                    SwapNodes(*node, *Next(node));
                    if (node->left_tree_ == nullptr && node->right_tree_ == nullptr)
                        DeleteLeaf(node);
                    else
                        DeleteNodeWithOnechild(node);
                }
            }

            BalanceTree(parent);
            BestRipeRateNode();

            return;
        }
        
        void SwapNodes(Node& node1, Node& node2) {
            if (root_ == &node1)
                root_ = &node2;
            if (highest_node_ == &node2)
                highest_node_ = Previous(&node2);

            Node temp = node1;
            if (node1.right_tree_ == &node2) {
                node1.parent_tree_ = &node2;
                node1.left_tree_ = node2.left_tree_;
                node1.right_tree_ = node2.right_tree_;

                node2.parent_tree_ = temp.parent_tree_;
                node2.left_tree_ = temp.left_tree_;
                node2.right_tree_ = &node1;
            }
            else {
                node1.parent_tree_ = node2.parent_tree_;
                node1.left_tree_ = node2.left_tree_;
                node1.right_tree_ = node2.right_tree_;

                node2.parent_tree_ = temp.parent_tree_;
                node2.left_tree_ = temp.left_tree_;
                node2.right_tree_ = temp.right_tree_;
            }

            node2.left_tree_->parent_tree_ = &node2;
            node2.right_tree_->parent_tree_ = &node2;
        }

        void DeleteNodeWithOnechild(Node* node) {
            Node* parent = node->parent_tree_;
            Node* only_child = (node->left_tree_ ? node->left_tree_ : node->right_tree_);
            only_child->parent_tree_ = parent;
            if (node == root_)
                root_ = only_child;
            if(node == lowest_node_)
                lowest_node_ = Next(node);
            if(node == highest_node_)
                highest_node_ = Previous(node);
            
            if (parent != nullptr) {
                if (parent->left_tree_ == node)
                    parent->left_tree_ = only_child;
                else
                    parent->right_tree_ = only_child;
            }
            linkedlist_->PopThis(node);
            --tree_size_;
        }

        void DeleteLeaf(Node * leaf) {
            Node* parent = leaf->parent_tree_;
            if (leaf == root_)
                root_ = parent;
            if (leaf == lowest_node_)
                lowest_node_ = parent;
            if (leaf == highest_node_)
                highest_node_ = parent;
            
            if (parent != nullptr) {
                if (parent->left_tree_ == leaf)
                    parent->left_tree_ = nullptr;
                else
                    parent->right_tree_ = nullptr;
            }
            linkedlist_->PopThis(leaf);
            --tree_size_;
        }

// ---------------------------------- AVL ---------------------------------------------------------

        void BalanceTree(Node* node);
        void UpdateHeightAndBalanceFactor(Node* node);
        void LeftRotation(int nodeid);
        void LeftRotation(Node* node);
        void RightRotation(int nodeid);
        void RightRotation(Node* node); 

// -------------------------------- iterator ------------------------------------------------------
        class Iterator {
            public:
                Iterator(Tree* tree, Node* node) : tree_(tree), currentNode_(node) {}
                ~Iterator() = default;

                Node* operator*() { return currentNode_; }

                bool operator==(const Iterator& other) {
                    if(currentNode_ == other.currentNode_)
                        return true;
                    
                    return false;
                }

                bool operator!=(const Iterator& other) {
                    return !(*this == other);
                }

                Iterator& operator++() {
                    currentNode_ = tree_->Next(currentNode_);
                    return *this;
                }

            private:
                Tree* tree_;
                Node* currentNode_;
        };
// -------------------------------- -------- ------------------------------------------------------
        Iterator begin() {
            return Iterator(this, lowest_node_);
        }
        Iterator end() {
            return Iterator(this, nullptr);
        }

        Node* Next(Node* node) {
            if (node->right_tree_ == nullptr) {
                while (1) {
                    if (node->parent_tree_ == nullptr)
                        return nullptr;
                    if (node->parent_tree_->left_tree_ == node)
                        return node->parent_tree_;
                    if (node->parent_tree_->right_tree_ == node)
                        node = node->parent_tree_;
                }
            }
            return Min(node->right_tree_);
        }

        Node* Previous(Node* node) {
            if (node->left_tree_ == nullptr) {
                while (1) {
                    if (node->parent_tree_ == nullptr)
                        return nullptr;
                    if (node->parent_tree_->right_tree_ == node)
                        return node->parent_tree_;
                    if (node->parent_tree_->left_tree_ == node)
                        node = node->parent_tree_;
                }
            }
            return Max(node->left_tree_);
        }

        Node* Max(Node* node) {
            while(node->right_tree_ != nullptr)
                node = node->right_tree_;          
            return node;
        }

        Node* Min(Node* node) {
            while (node->left_tree_ != nullptr)
                node = node->left_tree_;
            return node;
        }

        Node* findPos(int key) {
            return findPos(key, root_);
        }

        Node* findPos(int key, Node* start_point) {
            Node* tempnode = start_point;
            while(tempnode != nullptr) {
                //cout << tempnode->key_ << " at address:  " << tempnode << endl;

                if(key == tempnode->key_)
                    return tempnode;
                if(key < tempnode->key_) {
                    if(tempnode->left_tree_ == nullptr)
                        return tempnode;
                    tempnode = tempnode->left_tree_;
                    continue;
                }
                if(key > tempnode->key_) {
                    if(tempnode->right_tree_ == nullptr)
                        return tempnode;
                    tempnode = tempnode->right_tree_;
                    continue;
                }
            }
            return nullptr;
        }

        int size() const {
            return tree_size_;
        }
        
        void PrintTreeData() {
            cout << "----------------------" << endl;
            cout << "treeID_ = " << treeID_ << endl;
            cout << "isEmpty_ = " << (isEmpty_ == 0 ? "no" : "yes") << endl;
            if ((isEmpty_ == 0 ? "no" : "yes"))
                return;
            cout << "tree_size_ = " << tree_size_ << endl;
            cout << "root_->key =          " << root_->key_;
            cout << "  at address: " << root_ << endl;
            cout << "lowest_node_->key_ =  " << lowest_node_->key_;
            cout << "  at address: " << lowest_node_ << endl;
            cout << "highest_node_->key_ = " << highest_node_->key_;
            cout << "  at address: " << highest_node_ << endl;
            cout << "----------------------" << endl;
        }

        Node* BestRipeRateNode();

        int treeID_;

    private:
        bool isEmpty_;
        int tree_size_;

        LinkedListExtraData* linkedlist_;
        Node* root_;
        Node* lowest_node_;
        Node* highest_node_;

        int lowest_ripe_rate_;
        int highest_ripe_rate_;
        Node* lowest_ripe_rate_node_;
};


#endif // TREE_H
