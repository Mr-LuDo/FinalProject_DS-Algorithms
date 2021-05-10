
////#include <iostream>
//using namespace std;
//
////#include "Statistics.h"
////#include "Node.h"
////#include "Linked_list.h"
//#include "Tree.h"

//class LinkedListExtraData;
//class Tree;
//class Node;

/*
void CountingSort(Node** fruits, int* nodes_rr_digits, int size) {

    const int TEN = 10;

    int* nodes_digit = new int[size]();
    int* ripe_rate_counter = new int[TEN]();
    int* new_position_inorder = new int[TEN]();
    Node** temp_fruits = new Node * [size];

    // copy to temp array fruits by their order
    for (int i = 0; i < size; ++i) {
        temp_fruits[i] = fruits[i];
    }

    // retrieving the digit
    for (int i = 0; i < size; ++i) {
        nodes_digit[i] = nodes_rr_digits[i] % 10;
        nodes_rr_digits[i] /= 10;
    }

    // ---------------- counting how many have the same ripe rate ---------------------------------
    for (int i = 0; i < size; ++i) {
        ++ripe_rate_counter[nodes_digit[i]];
    }

    // -- rerouting each ripe rate according to its position (fruitID) and how many repetitions of ripe rate ---
    int sum_prev_nodes = 0;
    for (int i = 1; i < TEN; ++i) {
        if (ripe_rate_counter[i] == 0)
            continue;

        new_position_inorder[i] = sum_prev_nodes;
        sum_prev_nodes += ripe_rate_counter[i];
    }

    // -- setting fruits in there new position (in ordered) - for now only those which ripe rate < K_tree - because of the memory limitation ---
    for (int i = 1; i < size; ++i) {

        fruits[new_position_inorder[nodes_digit[i]]] = temp_fruits[i];
        ++new_position_inorder[nodes_digit[i]];
    }

    delete[] nodes_digit;
    delete[] ripe_rate_counter;
    delete[] new_position_inorder;
    delete[] temp_fruits;

    return;
}

void RedixSort(Tree* tree, Node** fruits) {

    int temp = tree->highest_ripe_rate_node_->ripeRate_;
    int numOffFruits = tree->size();

    int num_of_digits = 0;
    while(temp / 10) {
        ++num_of_digits;
    }

    int* nodes_rr_digits = new int[numOffFruits]();
    for (int i = 0; i < numOffFruits; ++i) {
        nodes_rr_digits[i] = fruits[i]->ripeRate_;
    }

    for (int i = 0; i < numOffFruits; ++i) {
        CountingSort(fruits, nodes_rr_digits, numOffFruits);
    }

    delete[] nodes_rr_digits;
    return;
}


*/