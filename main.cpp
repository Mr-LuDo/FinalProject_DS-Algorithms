#include <iostream>

#include "linked_list.h"
#include "tree.h"
#include "Node.h"

using namespace std;


int main()
{
    LinkedListExtraData LL1;

    int treeID = 8;
    Tree tree1(treeID, &LL1);


    tree1.AddFruit(7);

    tree1.AddFruit(7);
    tree1.AddFruit(5);
//    /*
    tree1.AddFruit(9);
    tree1.AddFruit(15);
    tree1.AddFruit(1);
    tree1.AddFruit(9);
    tree1.Printtreedata();
    cout << "linked list size: " << LL1.size() << endl;
    cout << "tree size: " << tree1.size() << endl;

//    cout << endl << endl <<
//     " ----------------- Linked list -----------------" << endl << endl;
//
//    cout << "LL size is: " << LL1.size() << endl;
//    cout << "this is LL1 first: " << LL1.first_node_ << endl;
//    cout << "this is LL1 last: " << LL1.last_node_ << endl << endl <<
//     " ----------------- Linked list -----------------" << endl << endl;


    cout << endl << endl <<
     " ----------------- Tree iterator -----------------" << endl << endl;

//     for(auto it = tree1.begin(); it != tree1.end(); ++it) {
//     for(auto it : tree1) {
    auto it = tree1.begin();
    for(auto i = 0; i < LL1.size(); ++i, ++it) {
        cout << "this is iterator result: " << endl;
        if(*it == nullptr) {
            cout << "no node, break out..." << endl;
            break;
        }
        (*it)->PrintNode();
        cout << "---------------------------------------" << endl << endl;
     }

     cout << endl << endl <<
     " ----------------- Tree iterator -----------------" << endl << endl;


//
//    Node* temp_node;
//    temp_node = LL1.first_node_;
//    for(auto i = 0; i < LL1.size(); ++i) {
//        cout << "this is node fruitID: " << temp_node->fruitID_ << endl;
//        cout << "this is node ll_source_: " << temp_node->ll_source_ << endl;
//        cout << "this is node ll_next_: " << temp_node->ll_next_ << endl;
//        cout << "this is node ll_previous_: " << temp_node->ll_previous_ << endl;
//
//        temp_node = temp_node->ll_next_;
//        cout << " -------------- Node ------------------" << endl;
//    }


//*/


    return 0;
}


/*
int main()
{
    LinkedListExtraData<int> LL1;
    LL1.PushFront(1);
    LL1.PushFront(2);
    LL1.PushFront(3);
    LL1.PushFront(4);
    LL1.PushFront(5);
    LL1.PushFront(6);

    LL1.PushBack(-1);
    LL1.PushBack(-2);
    LL1.PushBack(-3);
    LL1.PushBack(-4);
    LL1.PushBack(-5);
    LL1.PushBack(-6);


    cout << "LL size is: " << LL1.size() << endl;
    cout << "this is LL1 first: " << LL1.first_node_ << endl;
    cout << "this is LL1 last: " << LL1.last_node_ << endl << endl <<
     " ----------------- Linked list -----------------" << endl << endl;

    Node* temp_node;
    temp_node = LL1.first_node_;
    for(auto i = 0; i < LL1.size(); ++i) {
        cout << "this is node fruitID: " << temp_node->fruitID_ << endl;
        cout << "this is node source: " << temp_node->source_ << endl;
        cout << "this is node next: " << temp_node->next_ << endl;
        cout << "this is node previous: " << temp_node->previous_ << endl;

        temp_node = temp_node->next_;
        cout << " -------------- Node ------------------" << endl;

        if(i == 5) temp_node->source_->PopThis(temp_node->previous_);
        if(i == 8) temp_node->source_->PushAfterThis(temp_node, 50);

    }

    cout << "LL size is: " << LL1.size() << endl;
    cout << "this is LL1 first: " << LL1.first_node_ << endl;
    cout << "this is LL1 last: " << LL1.last_node_ << endl << endl <<
     " ----------------- Linked list -----------------" << endl << endl;
//    Node* temp_node;
    temp_node = LL1.first_node_;
    for(auto i = 0; i < LL1.size(); ++i) {
        cout << "this is node fruitID: " << temp_node->fruitID_ << endl;
        cout << "this is node source: " << temp_node->source_ << endl;
        cout << "this is node next: " << temp_node->next_ << endl;
        cout << "this is node previous: " << temp_node->previous_ << endl;

        temp_node = temp_node->next_;
        cout << " -------------- Node ------------------" << endl;


    }



    cout << "LL size is: " << LL1.size() << endl;
    cout << "this is LL1 first: " << LL1.first_node_ << endl;
    cout << "this is LL1 last: " << LL1.last_node_ << endl << endl <<
     " ----------------- Linked list -----------------" << endl << endl;
//    Node* temp_node;
    temp_node = LL1.last_node_;
    for(auto i = 0; i < LL1.size(); ++i) {
        cout << "this is node fruitID: " << temp_node->fruitID_ << endl;
        cout << "this is node source: " << temp_node->source_ << endl;
        cout << "this is node next: " << temp_node->next_ << endl;
        cout << "this is node previous: " << temp_node->previous_ << endl;

        temp_node = temp_node->previous_;
        cout << " -------------- Node ------------------" << endl;


    }
    return 0;
}
*/
