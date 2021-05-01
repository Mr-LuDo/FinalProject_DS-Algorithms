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


    Statistics* DS = new Statistics(); // Call constructor
    DS->Init(N);
    DS->PlantTree(1, 3);
    DS->PlantTree(2, 1);
    DS->PlantTree(5, 0);
    DS->PlantTree(4, 3);

    DS->PrintLLPlantation();
    
    DS->AddFruit(1, 3, 7, -1);
    DS->AddFruit(1, 3, 7, -1);
    DS->AddFruit(1, 3, 5, -1);
    DS->AddFruit(1, 3, 9, -1);
    DS->AddFruit(1, 3, 15, -1);
    DS->AddFruit(1, 3, 1, -1);
    DS->AddFruit(1, 3, 9, -1);
    DS->AddFruit(1, 3, 155, -1);
    DS->AddFruit(1, 3, 91, -1);
    DS->AddFruit(1, 3, 11, -1);
    DS->AddFruit(1, 3, 6, -1);
    DS->AddFruit(1, 3, 52, -1);

    DS->PrintLLFruits();
    DS->StaPrintTree(1, 3);
   




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


    tree1.AddNode(7);
    tree1.AddNode(7);
    tree1.AddNode(5);
    tree1.AddNode(9);
    tree1.AddNode(15);
    tree1.AddNode(1);
    tree1.AddNode(9);
    tree1.AddNode(155);
    tree1.AddNode(91);
    tree1.AddNode(11);
    tree1.AddNode(6);
    tree1.AddNode(52);


    tree2.AddNode(17);
    tree2.AddNode(71);
    tree2.AddNode(55);
    tree2.AddNode(96);
    tree2.AddNode(115);
    tree2.AddNode(11);
    tree2.AddNode(79);
    tree2.AddNode(125);
    tree2.AddNode(91);
    tree2.AddNode(115);
    tree2.AddNode(67);
    tree2.AddNode(8);

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
