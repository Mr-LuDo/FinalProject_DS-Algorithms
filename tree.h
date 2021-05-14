#ifndef TREE_H
#define TREE_H

#include <iostream>
using std::cout;
using std::endl;

#include "Node.h"
#include "Linked_list.h"

void PrintTree(Tree& tree);

class Tree
{
    public:
        Tree(int treeID, LinkedListExtraData* ll) :
            treeID_(treeID), tree_size_(0), linkedlist_(ll),
            root_(nullptr), lowest_node_(nullptr), highest_node_(nullptr),
            lowest_ripe_rate_node_(nullptr), highest_ripe_rate_node_(nullptr)
        {}

        virtual ~Tree() = default;

        Node* AddNode(int key, int ripe_rate);
        void DeleteNode(Node* node);

        int size() const;
        void PrintTreeData();
        Node* BestRipeRateNode();
        Node* WorstRipeRateNode();
        void UpdateBestAndWorstRipeRateNodes();    

        int treeID_;
        Node* Search(int key);
        Node* Search(int key, Node* start_point);

// -------------------------------- iterator ------------------------------------------------------

        class Iterator {
        public:
            Iterator(Tree* tree, Node* node) : tree_(tree), currentNode_(node) {}
            ~Iterator() = default;

            Node* operator*() { return currentNode_; }

            bool operator==(const Iterator& other) {
                if (currentNode_ == other.currentNode_)
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
        Iterator begin() {
            return Iterator(this, lowest_node_);
        }
        Iterator end() {
            return Iterator(this, nullptr);
        }

// -------------------------------- -------- ------------------------------------------------------

    private:
        // New node
        void UpdateRoot(Tree* tree, Node* parent, Node* left, Node* right);
        bool UpdateLeft(Node* node, Node* newLeft_node);
        bool UpdateRight(Node* node, Node* newRight_node);

        // delete node
        void DeleteNode(int key);
        void SwapNodes(Node& node1, Node& node2);
        void DeleteNodeWithOnechild(Node* node);
        void DeleteLeaf(Node* leaf);

        // ---------------------------------- AVL ---------------------------------------------------------

        void BalanceTree(Node* node);
        void UpdateHeightAndBalanceFactor(Node* node);
        void LeftRotation(int nodeid);
        void LeftRotation(Node* node);
        void RightRotation(int nodeid);
        void RightRotation(Node* node);

        // ---------------------------------- --- ---------------------------------------------------------

        Node* Next(Node* node);
        Node* Previous(Node* node);
        Node* Max(Node* node);
        Node* Min(Node* node);

        unsigned int tree_size_;

        LinkedListExtraData* linkedlist_;
        Node* root_;
        Node* lowest_node_;
        Node* highest_node_;

        Node* lowest_ripe_rate_node_;       
        Node* highest_ripe_rate_node_;     
};


#endif // TREE_H
