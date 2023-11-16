#include "linkedBTree.h"
#include "linkedBSTree.h"
#include <iostream>

using namespace std;

int main()
{
    LinkedBSTree<int> tree;
    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    tree.add(5);
    tree.add(6);
    tree.add(7);

    cout << tree.getHeight() << endl;

}