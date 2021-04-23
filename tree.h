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
            lowestNodeId_(nullptr), highestNodeId_(nullptr), root_(nullptr) {}

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
                lowestNodeId_ = temp_node;
                highestNodeId_ = temp_node;
            }
            else {
                Node* pos = findPos(fruitID);
                if(pos == temp_node) {
                    cout << "fruit already exist" << endl;
                    return;
                }
                if(fruitID < pos->fruitID_) {
                    if(UpdateLeft(pos, temp_node)) ++tree_size_;
                    if(fruitID < lowestNodeId_->fruitID_)
                        lowestNodeId_ = temp_node;
                }
                else {
                    if(UpdateRight(pos, temp_node)) ++tree_size_;
                    if(fruitID > highestNodeId_->fruitID_)
                        highestNodeId_ = temp_node;
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
            return Iterator(this, lowestNodeId_);
        }
        Iterator end() {
            return Iterator(this, nullptr);
        }

        Node* Next(Node* node) {
            if (node->tree_right_ == nullptr) {
                while (1) {
                    cout << "next loop" << endl;
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
            while(node->tree_right_ != nullptr) {
                node = node->tree_right_;
            }
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
            cout << "lowestNodeId_ = " << lowestNodeId_ <<endl;
            cout << "highestNodeId_ = " << highestNodeId_ << endl;
            cout << "root_ = " << root_ << endl;
            cout << "-------------" << endl;
            }

        int size() const {
            return tree_size_;
        }

    private:
        int treeID_;
        bool isEmpty_;
        int tree_size_;

        LinkedListExtraData* linkedlist_;
        Node* lowestNodeId_;
        Node* highestNodeId_;
        Node* root_;
};

#endif // TREE_H
