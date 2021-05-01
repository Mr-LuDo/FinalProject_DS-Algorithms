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


void PrintTree(Tree& tree) {
    tree.PrintTreeData();
    cout << endl << endl <<
        "----------------- Iterator Tree ID = " << tree.treeID_ << " -----------------" << endl << endl;
    for (auto it : tree) {
        cout << "iterator curent node value: " << (it)->key_ << endl;
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
    LeftRotation(findPos(nodeid));
}
void Tree::RightRotation(int nodeid) {
    RightRotation(findPos(nodeid));
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

