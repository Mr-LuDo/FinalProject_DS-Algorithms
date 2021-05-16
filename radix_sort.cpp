
#include "Tree.h"

void CountingSort(Node** fruits, int* nodes_rr_digits, int size);

void RadixSort(Tree* tree, Node** fruits) {

    int temp = tree->WorstRipeRateNode()->ripeRate_;
    int numOffFruits = tree->size();

    int num_of_digits = 0;
    while (temp) {
        ++num_of_digits;
        temp /= 10;
    }

    int* nodes_rr_digits = new int[numOffFruits]();
    for (int j = 0; j < numOffFruits; ++j) {
        nodes_rr_digits[j] = fruits[j]->ripeRate_;
    }

    for (int i = 0; i < num_of_digits; ++i) {
        CountingSort(fruits, nodes_rr_digits, numOffFruits);
    }

    delete[] nodes_rr_digits;
    return;
}


void CountingSort(Node** fruits, int* nodes_rr_digits, int size) {

    const int TEN = 10;

    int* nodes_digit = new int[size]();
    int* temp_nodes_rr_digits = new int[size]();
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
        temp_nodes_rr_digits[i] = nodes_rr_digits[i];
    }

    // ---------------- counting how many have the same ripe rate ---------------------------------
    for (int i = 0; i < size; ++i) {
        ++ripe_rate_counter[nodes_digit[i]];
    }

    // -- rerouting each ripe rate according to its position (fruitID) and how many repetitions of ripe rate ---
    int sum_prev_nodes = 0;
    for (int i = 0; i < TEN; ++i) {
        if (ripe_rate_counter[i] == 0)
            continue;

        new_position_inorder[i] = sum_prev_nodes;
        sum_prev_nodes += ripe_rate_counter[i];
    }

    // ------------------------ setting fruits in their new position (in ordered) ---------------------------
    for (int i = 0; i < size; ++i) {
        int temp_digit = nodes_digit[i];

        fruits[new_position_inorder[nodes_digit[i]]] = temp_fruits[i];
        nodes_rr_digits[new_position_inorder[nodes_digit[i]]] = temp_nodes_rr_digits[i];
        ++new_position_inorder[nodes_digit[i]];

    }

    delete[] nodes_digit;
    delete[] temp_nodes_rr_digits;
    delete[] ripe_rate_counter;
    delete[] new_position_inorder;
    delete[] temp_fruits;

    return;
}


