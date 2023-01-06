/**
 * @file main.cpp
 * @brief test the binarytree class
 * @author Kendra Walker 
 */

#include "binarytree.h"
#include <cassert>
// tests the construction of the tree
// The size constructor, insert, and contains methods
void testConstruction() {
  BinaryTree myTree(30);
  assert(myTree.getRootData() == 15);
  assert(myTree.getCount() == 30);
  assert(myTree.contains(12));
  assert(myTree.contains(30));
  assert(!myTree.contains(31));
    myTree.insert(60);
  assert(myTree.getCount() == 31);
  assert(myTree.contains(60));
}

// tests the remove function, contains, and removeEvne function
void testRemove() {
  BinaryTree myTree(30);
    myTree.remove(17);
  assert(!myTree.contains(17));
    myTree.remove(1);
  assert(!myTree.contains(1));
  assert(myTree.getCount() == 28);
  myTree.removeEven();
  assert(myTree.getCount() == 13);
}


// create a tree, copy it, remove the even numbers, and print
void ass5Program() {
  BinaryTree myTree(16);
  std::cout << "Threaded binary tree with a root of: " << myTree.getRootData()
            << " a size of: " << myTree.getCount() << std::endl;
  std::cout << myTree << std::endl;
  BinaryTree copyTree(myTree);
  std::cout << "Copy of the original tree has a root of: "
            << copyTree.getRootData()
            << " and a size of: " << copyTree.getCount() << std::endl
            << copyTree << std::endl;
  copyTree.removeEven();
  std::cout << "Copy tree after removing even numbers:" << std::endl
            << copyTree << std::endl;
}

int main() {
  std::cout << "Testing tree construction: " << std::endl;
  testConstruction();
  std::cout << "Tests passed! " << std::endl;

  std::cout << "Testing remove function: " << std::endl;
  testRemove();
  std::cout << "Tests passed! " << std::endl;

  // program for assignment 5
  ass5Program();

  return 0;
}
