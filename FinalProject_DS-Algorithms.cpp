// FinalProject_DS-Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
using namespace std;

#include "Linked_list.h"
#include "Tree.h"
#include "Statistics.h"

//using std::exception;

int main1();

#define N 10

int main()
{
    //main1();


    Statistics* St = new Statistics(); // Call constructor
    void* DS = St->Init(N);
    St->PlantTree(DS, 1, 3);
    St->PlantTree(DS, 2, 1);
    St->PlantTree(DS, 5, 0);
    St->PlantTree(DS, 4, 3);

    St->PrintLLPlantation(DS);
    
    St->AddFruit(DS, 1, 3, 7, -1);
    St->AddFruit(DS, 1, 3, 7, -1);
    St->AddFruit(DS, 1, 3, 5, -1);
    St->AddFruit(DS, 1, 3, 9, -1);
    St->AddFruit(DS, 1, 3, 15, -1);
    St->AddFruit(DS, 1, 3, 1, -1);
    St->AddFruit(DS, 1, 3, 9, -1);
    St->AddFruit(DS, 1, 3, 155, -1);
    St->AddFruit(DS, 1, 3, 91, -1);
    St->AddFruit(DS, 1, 3, 11, -1);
    St->AddFruit(DS, 1, 3, 6, -1);
    St->AddFruit(DS, 1, 3, 52, -1);

    St->PrintLLFruits(DS);
    St->StaPrintTree(DS, 1, 3);
   




    return 0;
}



// basics function direct addressing 
int main1()
{
    LinkedListExtraData LL1;

    int treeID1 = 8;
    int treeID2 = 2;
    Tree tree1(treeID1, &LL1);
    Tree tree2(treeID2, &LL1);


    tree1.AddNode(7, 1);
    tree1.AddNode(7, 1);
    tree1.AddNode(5, 1);
    tree1.AddNode(9, 1);
    tree1.AddNode(15, 1);
    tree1.AddNode(1, 1);
    tree1.AddNode(9, 1);
    tree1.AddNode(155, 1);
    tree1.AddNode(91, 1);
    tree1.AddNode(11, 1);
    tree1.AddNode(6, 1);
    tree1.AddNode(52, 1);


    tree2.AddNode(17, 1);
    tree2.AddNode(71, 1);
    tree2.AddNode(55, 1);
    tree2.AddNode(96, 1);
    tree2.AddNode(115, 1);
    tree2.AddNode(11, 1);
    tree2.AddNode(79, 1);
    tree2.AddNode(125, 1);
    tree2.AddNode(91, 1);
    tree2.AddNode(115, 1);
    tree2.AddNode(67, 1);
    tree2.AddNode(8, 1);

    tree1.PrintTreeData();
    cout << "linked list size: " << LL1.size() << endl;
    cout << "tree 1 size: " << tree1.size() << endl;
    cout << "tree 2 size: " << tree2.size() << endl;

    LL1.PrintLinkedList();
    
    
 
    //tree1.DeleteNode(tree1.findPos(1));
    //PrintTree(tree1);
    //tree1.DeleteNode(tree1.findPos(7));
    //PrintTree(tree1);    
    //tree1.DeleteNode(tree1.findPos(155));
    //PrintTree(tree1);


    PrintTree(tree1);



    //tree1.LeftRotation(7);
    ////tree1.LeftRotation(155);
    ////tree1.RightRotation(155);
    ////tree1.RightRotation(91);
    ////tree1.RightRotation(15);
    //tree1.LeftRotation(91);
    ////tree1.RightRotation(11);

    //PrintTree(tree1);


    //Tree& temp = tree1;
    //cout << "&tree1 = " << &tree1 << endl;
    //cout << "&temp = " << &temp << endl;

     
    //cout << tree1.findPos(11)->key_ << " at address:  " << tree1.findPos(11) << endl;
    tree1.DeleteNode(11);
    tree1.DeleteNode(11);
    tree1.DeleteNode(9);
    tree1.DeleteNode(1);
    tree1.DeleteNode(6);
    tree1.DeleteNode(52);
    PrintTree(tree1);
    //delete &tree1;

    //int temp;
    //cin >> temp;
    //tree1.PrintTreeData();
    cout << "linked list size: " << LL1.size() << endl;
    cout << "tree 1 size: " << tree1.size() << endl;
    //cout << "tree 2 size: " << tree2.size() << endl;

    //try {
    //    delete& tree1;
    //}
    //catch (const std::exception& e) {
    //    cout << e.what() << endl;
    //}

    //cout << "deleted ll1" << endl;



    return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
