#include <iostream>

#include "DSWTree.h"


// ========================= //
//           MAIN            //
// ========================= //
int main() {
        // You can test using this main.

    std::cout << "=========Default constructor/Print=========" << std::endl;

    std::cout << "-> Creating a DSW tree with default constructor." << std::endl;

    DSWTree<int> tree;
    //TreeMap<int,int> treeMap;
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(16);
    tree.insert(11);
    tree.insert(26);
    tree.insert(21);
    tree.insert(36);
    tree.insert(19);
    tree.balance();
    
    
    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);
    tree.printPretty();






    return 0;
}