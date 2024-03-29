#include "tree.h"

#define DOES_NODE_EXIST(node)           ( (node != nullptr) ? true : false )
#define CHECK_FOR_NULL_PARENT(node)     ( DOES_NODE_EXIST(node) ?  ( DOES_NODE_EXIST( (node)->parent_tree_ ) ? (node)->parent_tree_ : nullptr ) : nullptr )
#define CHECK_FOR_NULL_LEFT(node)       ( DOES_NODE_EXIST(node) ?  ( DOES_NODE_EXIST( (node)->left_tree_   ) ? (node)->left_tree_   : nullptr ) : nullptr )
#define CHECK_FOR_NULL_RIGHT(node)      ( DOES_NODE_EXIST(node) ?  ( DOES_NODE_EXIST( (node)->right_tree_  ) ? (node)->right_tree_  : nullptr ) : nullptr )

#define IF_EXIST_RETURN_VARIABLE(node, direction, variable, if_false)  ( DOES_NODE_EXIST(node) ? ( DOES_NODE_EXIST( node->direction ) ? node->direction->variable : if_false ) : if_false )
#define UNBALANCED_LEFT 2
#define UNBALANCED_RIGHT -2
#define LEFT_HEAVY 1
#define RIGHT_HEAVY -1

void PrintTree(Tree& tree);

Node* Tree::AddNode(int key, int ripe_rate) {
    if (linkedlist_->PushFront(key, treeID_, this) == false) {
        return nullptr;
    }

    Node* temp_node = linkedlist_->Front();
    temp_node->ripeRate_ = ripe_rate;

    if (tree_size_ == 0) {
        ++tree_size_;
        root_ = lowest_node_ = highest_node_ = temp_node;
        UpdateRoot(this, nullptr, nullptr, nullptr);
    }
    else {
        Node* pos = Search(key);
        if (pos == temp_node)
            return pos;

        if (key < pos->key_) {
            if (UpdateLeft(pos, temp_node))
                ++tree_size_;
            if (key < lowest_node_->key_)
                lowest_node_ = temp_node;
        }
        else {
            if (UpdateRight(pos, temp_node))
                ++tree_size_;
            if (key > highest_node_->key_)
                highest_node_ = temp_node;
        }
    }
    BalanceTree(temp_node);
    UpdateBestAndWorstRipeRateNodes();

    return temp_node;
}

void Tree::UpdateRoot(Tree * tree, Node * parent, Node * left, Node * right) {
    root_->parent_tree_ = parent;
    root_->left_tree_ = left;
    root_->right_tree_ = right;
}

bool Tree::UpdateLeft(Node * node, Node * newLeft_node) {
    if (node->left_tree_ == nullptr) {
        node->left_tree_ = newLeft_node;
        newLeft_node->parent_tree_ = node;
        return true;
    }
    else {
        cout << "left son not empty, no action were taken." << endl;
        return false;
    }
}

bool Tree::UpdateRight(Node * node, Node * newRight_node) {
    if (node->right_tree_ == nullptr) {
        node->right_tree_ = newRight_node;
        newRight_node->parent_tree_ = node;
        return true;
    }
    else {
        cout << "right son not empty, no action were taken." << endl;
        return false;
    }
}

void Tree::DeleteNode(int key) {
    Node* node = Search(key);
    if (node->key_ != key)
        return;
    DeleteNode(node);
}

void Tree::DeleteNode(Node * node) {
    Node* parent = node->parent_tree_;

    if (node->left_tree_ == nullptr && node->right_tree_ == nullptr) {
        DeleteLeaf(node);
    }
    else {
        if (node->left_tree_ == nullptr || node->right_tree_ == nullptr) {
            DeleteNodeWithOnechild(node);
        }
        else {
            SwapNodes(*node, *Next(node));
            if (node->left_tree_ == nullptr && node->right_tree_ == nullptr)
                DeleteLeaf(node);
            else
                DeleteNodeWithOnechild(node);
        }
    }

    BalanceTree(parent);
    UpdateBestAndWorstRipeRateNodes();

    return;
}

void Tree::SwapNodes(Node & node1, Node & node2) {
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

void Tree::DeleteNodeWithOnechild(Node * node) {
    Node* parent = node->parent_tree_;
    Node* only_child = (node->left_tree_ ? node->left_tree_ : node->right_tree_);
    only_child->parent_tree_ = parent;
    if (node == root_)
        root_ = only_child;
    if (node == lowest_node_)
        lowest_node_ = Next(node);
    if (node == highest_node_)
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

void Tree::DeleteLeaf(Node * leaf) {
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

Node* Tree::Next(Node* node) {
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

Node* Tree::Previous(Node* node) {
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

Node* Tree::Max(Node* node) {
    while (node->right_tree_ != nullptr)
        node = node->right_tree_;
    return node;
}

Node* Tree::Min(Node* node) {
    while (node->left_tree_ != nullptr)
        node = node->left_tree_;
    return node;
}

Node* Tree::Search(int key) {
    return Search(key, root_);
}

Node* Tree::Search(int key, Node* start_point) {
    Node* tempnode = start_point;
    while (tempnode != nullptr) {
        if (key == tempnode->key_)
            return tempnode;
        if (key < tempnode->key_) {
            if (tempnode->left_tree_ == nullptr)
                return tempnode;
            tempnode = tempnode->left_tree_;
            continue;
        }
        if (key > tempnode->key_) {
            if (tempnode->right_tree_ == nullptr)
                return tempnode;
            tempnode = tempnode->right_tree_;
            continue;
        }
    }
    return nullptr;
}

int Tree::size() const {
    return tree_size_;
}

void Tree::PrintTreeData() {
    cout << "----------------------" << endl;
    cout << "treeID_ = " << treeID_ << endl;
    cout << "is tree Empty = " << (tree_size_ == 0 ? "yes": "no") << endl;
    if (tree_size_ == 0)
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


void PrintTree(Tree& tree) {
    tree.PrintTreeData();
    cout << endl << endl <<
        "----------------- Iterator Tree ID = " << tree.treeID_ << " -----------------" << endl << endl;
    for (auto it : tree) {
        cout << "iterator current node value: " << (it)->key_ << endl;
        (it)->PrintNode();
        cout << "---------------------------------------" << endl << endl;
    }
}

void Tree::BalanceTree(Node* node) {

    do {
        if (DOES_NODE_EXIST(node) == false)
            return;

        UpdateHeightAndBalanceFactor(node);

        int height_zero = 0;
        if (node->balance_factor_ == UNBALANCED_LEFT || node->balance_factor_ == UNBALANCED_RIGHT) {
            int left_balance_factor = IF_EXIST_RETURN_VARIABLE(node, left_tree_, balance_factor_, height_zero);
            int right_balance_factor = IF_EXIST_RETURN_VARIABLE(node, right_tree_, balance_factor_, height_zero);

            if (node->balance_factor_ == UNBALANCED_LEFT) {
                if (left_balance_factor == LEFT_HEAVY)
                    RightRotation(node);
                else {
                    LeftRotation(node->left_tree_);
                    RightRotation(node);
                }
            }
            else {
                if (right_balance_factor == RIGHT_HEAVY)
                    LeftRotation(node);
                else {
                    RightRotation(node->right_tree_);
                    LeftRotation(node);
                }
            }
        }

        UpdateHeightAndBalanceFactor(node);
        node = node->parent_tree_;
    } while (node != nullptr);

    return;
}

void Tree::UpdateHeightAndBalanceFactor(Node* node) {

    if (DOES_NODE_EXIST(node) == false)
        return;
    if (node->parent_tree_ == nullptr)
        root_ = node;

    int height_zero = 0;
    int left_height = IF_EXIST_RETURN_VARIABLE(node, left_tree_, height_, height_zero);
    int right_height = IF_EXIST_RETURN_VARIABLE(node, right_tree_, height_, height_zero);

    node->height_ = 1 + std::max(left_height, right_height);
    node->balance_factor_ = left_height - right_height;

    return;
}

void Tree::LeftRotation(int nodeid) {
    LeftRotation(Search(nodeid));
}
void Tree::RightRotation(int nodeid) {
    RightRotation(Search(nodeid));
}

void Tree::LeftRotation(Node* node) {

    Node* father_node = CHECK_FOR_NULL_PARENT(node);
    Node* right_node = CHECK_FOR_NULL_RIGHT(node);
    Node* right_node_lefttson = CHECK_FOR_NULL_LEFT(right_node);

    if (DOES_NODE_EXIST(right_node)) {
        right_node->parent_tree_ = father_node;
        if (DOES_NODE_EXIST(father_node)) {
            if (father_node->left_tree_ == node)
                node->parent_tree_->left_tree_ = right_node;
            else
                node->parent_tree_->right_tree_ = right_node;
        }

        right_node->left_tree_ = node;
        node->parent_tree_ = right_node;

        node->right_tree_ = right_node_lefttson;
        if (DOES_NODE_EXIST(right_node_lefttson))
            right_node_lefttson->parent_tree_ = node;

        if (node == root_)
            root_ = right_node;
    }
}

void Tree::RightRotation(Node* node) {

    Node* father_node = CHECK_FOR_NULL_PARENT(node);
    Node* left_node = CHECK_FOR_NULL_LEFT(node);
    Node* left_node_rightson = CHECK_FOR_NULL_RIGHT(left_node);

    if (DOES_NODE_EXIST(left_node)) {
        left_node->parent_tree_ = father_node;
        if (DOES_NODE_EXIST(father_node)) {
            if (father_node->left_tree_ == node)
                node->parent_tree_->left_tree_ = left_node;
            else
                node->parent_tree_->right_tree_ = left_node;
        }

        left_node->right_tree_ = node;
        node->parent_tree_ = left_node;

        node->left_tree_ = left_node_rightson;
        if (DOES_NODE_EXIST(left_node_rightson))
            left_node_rightson->parent_tree_ = node;

        if (root_ = node)
            root_ = left_node;
    }
}


void Tree::UpdateBestAndWorstRipeRateNodes() {
    lowest_ripe_rate_node_ = lowest_node_;
    highest_ripe_rate_node_ = lowest_node_;

    if (lowest_ripe_rate_node_ == nullptr)
        return;

    for (auto it : *this) {
        if (it->ripeRate_ < lowest_ripe_rate_node_->ripeRate_)
            lowest_ripe_rate_node_ = it;
        if (it->ripeRate_ > highest_ripe_rate_node_->ripeRate_)
            highest_ripe_rate_node_ = it;
    }
    return;
}

Node* Tree::BestRipeRateNode() {
    return lowest_ripe_rate_node_;
}

Node* Tree::WorstRipeRateNode() {
    return highest_ripe_rate_node_;
}
