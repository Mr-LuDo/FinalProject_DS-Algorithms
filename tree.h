#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "Node.h"
#include "linked_list.h"

using namespace std;


class Tree
{
    public:
        Tree(int treeID, LinkedListExtraData* LL) :
            treeID_(treeID), isEmpty_(true), tree_size_(0), linkedlist_(LL),
            root_(nullptr), lowest_node_(nullptr), highest_node_(nullptr)
        {}

        virtual ~Tree() = default;

        void AddFruit(int fruitID) {
            if(linkedlist_->PushFrontfruit(fruitID, treeID_, this) == false)
                return;

            Node* temp_node = linkedlist_->Front();
            if(isEmpty_) {
                isEmpty_ = false;
                ++tree_size_;
                root_ = temp_node;
                root_->UpdateTree(this, nullptr, nullptr, nullptr);
                lowest_node_ = temp_node;
                highest_node_ = temp_node;
            }
            else {
                Node* pos = findPos(fruitID);
                if(pos == temp_node) {
                    cout << "fruit already exist" << endl;
                    return;
                }
                if(fruitID < pos->fruitID_) {
                    if(UpdateLeft(pos, temp_node)) ++tree_size_;
                    if(fruitID < lowest_node_->fruitID_)
                        lowest_node_ = temp_node;
                }
                else {
                    if(UpdateRight(pos, temp_node)) ++tree_size_;
                    if(fruitID > highest_node_->fruitID_)
                        highest_node_ = temp_node;
                }
            }
        }

        bool UpdateLeft(Node* fruitNode, Node* newLeft_fruitNode) {
            if(fruitNode->tree_left_ == nullptr) {
                fruitNode->tree_= this;
                fruitNode->tree_left_ = newLeft_fruitNode;
                newLeft_fruitNode->tree_parent_ = fruitNode;
                return true;
            }
            else {
                cout << "left son not empty, no action were taken." << endl;
                return false;
            }
        }

        bool UpdateRight(Node* fruitNode, Node* newRight_fruitNode) {
            if(fruitNode->tree_right_ == nullptr) {
                fruitNode->tree_= this;
                fruitNode->tree_right_ = newRight_fruitNode;
                newRight_fruitNode->tree_parent_ = fruitNode;
                return true;
            }
            else {
                cout << "right son not empty, no action were taken." << endl;
                return false;
            }
        }

        void DeleteNode(Node* node) {
            if (node->tree_left_ == nullptr && node->tree_right_ == nullptr) {
                DeleteLeaf(node);
                return;
            }
            if (node->tree_left_ == nullptr || node->tree_right_ == nullptr) {
                DeleteNodeOnechild(node);
                return;
            }
            else {
                SwapNodes(*node, *Next(node));
                if (node->tree_left_ == nullptr && node->tree_right_ == nullptr)
                    DeleteLeaf(node);
                else
                    DeleteNodeOnechild(node);
                return;
            }
        }
        
        void SwapNodes(Node& node1, Node& node2) {
            if (root_ == &node1)
                root_ = &node2;
            if (highest_node_ == &node2)
                highest_node_ = Previous(&node2);

            Node temp = node1;
            if (node1.tree_right_ == &node2) {
                node1.tree_parent_ = &node2;
                node1.tree_left_ = node2.tree_left_;
                node1.tree_right_ = node2.tree_right_;

                node2.tree_parent_ = temp.tree_parent_;
                node2.tree_left_ = temp.tree_left_;
                node2.tree_right_ = &node1;
            }
            else {
                node1.tree_parent_ = node2.tree_parent_;
                node1.tree_left_ = node2.tree_left_;
                node1.tree_right_ = node2.tree_right_;

                node2.tree_parent_ = temp.tree_parent_;
                node2.tree_left_ = temp.tree_left_;
                node2.tree_right_ = temp.tree_right_;
            }

            node2.tree_left_->tree_parent_ = &node2;
            node2.tree_right_->tree_parent_ = &node2;
        }

        void DeleteNodeOnechild(Node* node) {
            Node* parent = node->tree_parent_;
            Node* only_child = (node->tree_left_ ? node->tree_left_ : node->tree_right_);
            only_child->tree_parent_ = parent;
            if (node == root_)
                root_ = only_child;
            if(node == lowest_node_)
                lowest_node_ = Next(node);
            if(node == highest_node_)
                highest_node_ = Previous(node);
            
            if (parent->tree_left_ == node)
                parent->tree_left_ = only_child;
            else
                parent->tree_right_ = only_child;
           
            linkedlist_->PopThis(node);
            --tree_size_;
        }

        void DeleteLeaf(Node * leaf) {
            Node* parent = leaf->tree_parent_;
            if (leaf == root_)
                root_ = parent;
            if (leaf == lowest_node_)
                lowest_node_ = parent;
            if (leaf == highest_node_)
                highest_node_ = parent;
            
            if (parent != nullptr) {
                if (parent->tree_left_ == leaf)
                    parent->tree_left_ = nullptr;
                else
                    parent->tree_right_ = nullptr;
            }
            linkedlist_->PopThis(leaf);
            --tree_size_;
        }


// -------------------------------- iterator ------------------------------------------------------
        class Iterator {
            public:
                Iterator(Tree* tree, Node* node) : tree_(tree), currentNode_(node) {}
                ~Iterator() = default;

                Node* operator*() { return currentNode_; }

                bool operator==(const Iterator& other) {
                    if(currentNode_ == other.currentNode_)
                        return true;
                    
                    //if(currentNode_->treeID_ != other.currentNode_->treeID_) {
                    //    cout << "iterator- wrong tree." << endl;
                    //    return false;
                    //}
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
// ------------------------------- iterator -------------------------------------------------------
        Iterator begin() {
            return Iterator(this, lowest_node_);
        }
        Iterator end() {
            return Iterator(this, nullptr);
        }

        Node* Next(Node* node) {
            if (node->tree_right_ == nullptr) {
                while (1) {
                    //cout << "next loop" << endl;
                    if (node->tree_parent_ == nullptr)
                        return nullptr;
                    if (node->tree_parent_->tree_left_ == node)
                        return node->tree_parent_;
                    if (node->tree_parent_->tree_right_ == node)
                        node = node->tree_parent_;
                }
            }
            return Min(node->tree_right_);
        }

        Node* Previous(Node* node) {
            if (node->tree_left_ == nullptr) {
                while (1) {
                    if (node->tree_parent_ == nullptr)
                        return nullptr;
                    if (node->tree_parent_->tree_right_ == node)
                        return node->tree_parent_;
                    if (node->tree_parent_->tree_left_ == node)
                        node = node->tree_parent_;
                }
            }
            return Max(node->tree_left_);
        }

        Node* Max(Node* node) {
            while(node->tree_right_ != nullptr)
                node = node->tree_right_;          
            return node;
        }

        Node* Min(Node* node) {
            while (node->tree_left_ != nullptr)
                node = node->tree_left_;
            return node;
        }

        Node* findPos(int fruitID) {
            Node* tempnode = root_;
            while(tempnode != nullptr) {
                if(fruitID == tempnode->fruitID_)
                    return tempnode;
                if(fruitID < tempnode->fruitID_) {
                    if(tempnode->tree_left_ == nullptr)
                        return tempnode;
                    tempnode = tempnode->tree_left_;
                    continue;
                }
                if(fruitID > tempnode->fruitID_) {
                    if(tempnode->tree_right_ == nullptr)
                        return tempnode;
                    tempnode = tempnode->tree_right_;
                    continue;
                }
            }
            return nullptr;
        }

        void Printtreedata() {
            cout << endl << "-------------" << endl;
            cout << "tree data: " <<endl;
            cout << "treeID_ = " << treeID_ << endl;
            cout << "isEmpty_ = " << isEmpty_ << endl;
            cout << "linkedlist_ = " << linkedlist_ << endl;
            cout << "lowest_node_ = " << lowest_node_ <<endl;
            cout << "highest_node_ = " << highest_node_ << endl;
            cout << "root_ = " << root_ << endl;
            cout << "-------------" << endl;
            }

        int size() const {
            return tree_size_;
        }
        
        void PrintTreeData() {
            cout << "----------------------" << endl;
            cout << "treeID_ = " << treeID_ << endl;
            cout << "isEmpty_ = " << (isEmpty_ == 0 ? "no" : "yes") << endl;
            cout << "tree_size_ = " << tree_size_ << endl;
            cout << "root_ = " << root_ << endl;
            cout << "lowest_node_ = " << lowest_node_ << endl;
            cout << "highest_node_ = " << highest_node_ << endl;
            cout << "----------------------" << endl;
        }

        int treeID_;
    private:
        bool isEmpty_;
        int tree_size_;

        LinkedListExtraData* linkedlist_;
        Node* root_;
        Node* lowest_node_;
        Node* highest_node_;
};


void PrintTree(Tree& tree) {
    tree.PrintTreeData();
    cout << endl << endl <<
        "----------------- Iterator Tree ID = "<< tree.treeID_ << " -----------------" << endl << endl;
    for (auto it : tree) {
        cout << "iterator curent node value: " << (it)->fruitID_ << endl;
        //(it)->PrintNode();
        cout << "---------------------------------------" << endl << endl;
    }
}


#endif // TREE_H
