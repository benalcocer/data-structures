/// @author Benjamin Alcocer
/// github: https://github.com/benalcocer

#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main()
{
    BinarySearchTree<int> tree;

    tree.insert(10);
    tree.insert(2);
    tree.insert(11);

    tree.inorder();
    cout << endl;
    tree.preorder();
    cout << endl;
    tree.postorder();
    cout << endl;

    return 0;
}
