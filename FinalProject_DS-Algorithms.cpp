// FinalProject_DS-Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Node.h"
#include "linked_list.h"
#include "tree.h"

using namespace std;


int main()
{
    LinkedListExtraData LL1;

    int treeID1 = 8;
    int treeID2 = 2;
    Tree tree1(treeID1, &LL1);
    Tree tree2(treeID2, &LL1);


    tree1.AddFruit(7);
    tree1.AddFruit(7);
    tree1.AddFruit(5);
    tree1.AddFruit(9);
    tree1.AddFruit(15);
    tree1.AddFruit(1);
    tree1.AddFruit(9);
    tree1.AddFruit(155);
    tree1.AddFruit(91);
    tree1.AddFruit(11);
    tree1.AddFruit(6);
    tree1.AddFruit(52);


    tree2.AddFruit(17);
    tree2.AddFruit(71);
    tree2.AddFruit(55);
    tree2.AddFruit(96);
    tree2.AddFruit(115);
    tree2.AddFruit(11);
    tree2.AddFruit(79);
    tree2.AddFruit(125);
    tree2.AddFruit(91);
    tree2.AddFruit(115);
    tree2.AddFruit(67);
    tree2.AddFruit(8);

    tree1.PrintTreeData();
    cout << "linked list size: " << LL1.size() << endl;
    cout << "tree 1 size: " << tree1.size() << endl;
    cout << "tree 2 size: " << tree2.size() << endl;

    LL1.PrintLinkedList();
    
 
 /*   tree1.DeleteNode(tree1.findPos(1));
    PrintTree(tree1);
    tree1.DeleteNode(tree1.findPos(7));
    PrintTree(tree1);    
    tree1.DeleteNode(tree1.findPos(155));
    PrintTree(tree1);
*/

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
