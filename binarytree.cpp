/**
 * @file binarytree.cpp
 * @brief defines the binarytree class
 * @author Kendra Walker 
 */

#include "binarytree.h"

// overloaded << operator to traverse and print the tree
std::ostream &operator<<(std::ostream &Out, const BinaryTree &bTree) {
  BinaryTree::Node *cur = bTree.leftLeaf(bTree.root);

  while (cur != nullptr) {
    // print out the value
    Out << cur->value << " ";
    if (cur->rightTh || cur->right == nullptr) {
      cur = cur->right;
    } else if (cur->right != nullptr) {
      cur = bTree.leftLeaf(cur->right);
    }
  }

  return Out;
}

///// constructors ///////////

// default constructor
BinaryTree::BinaryTree() {
  root = nullptr;
  size = 0;
}

// constructor
BinaryTree::BinaryTree(int numbr) {
  root = nullptr;
  size = 0;
  if (numbr > 0) {
    int *nums;
    nums = new int[numbr];
    for (int i = 0; i < numbr; i++) {
      nums[i] = i + 1;
    }

    // send only the filled elements
    // and insert them
    buildBinaryTree(nums, 0, numbr - 1);
    delete[] nums;
  }
}

// Copy constructor
BinaryTree::BinaryTree(const BinaryTree &otherTree) {
  root = nullptr;
  size = 0;
  copyTree(otherTree.root);
}

// Destructor
BinaryTree::~BinaryTree() { clear(); }

////////// Class methods /////////////////

// recursive helper function to copy tree
void BinaryTree::copyTree(const BinaryTree::Node *nodePtr) {
  insert(nodePtr->value);
  if (!nodePtr->leftTh && nodePtr->left != nullptr) {
    copyTree(nodePtr->left);
  }
  if (!nodePtr->rightTh && nodePtr->right != nullptr) {
    copyTree(nodePtr->right);
  }
}

// insert a node into the tree
// will thread nodes as they get inserted
bool BinaryTree::insert(int num) {
  bool inserted = false;
  // create a new node
  Node *newNode = new Node(num);
  // set node to traverse
  Node *cur = root;

  // if its empty set the root node
  if (root == nullptr) {
    root = newNode;
    size++;
    return true;
  }

  // move through the list while cur is not null
  // should exit at parent node of new node
  while (cur != nullptr) {
    // if its less then go left
    if (num <= cur->value) {
      // check to make sure its not a thread
      if (!cur->leftTh && cur->left != nullptr) {
        cur = cur->left;
      } else {
        break;
      }
    }

    if (num > cur->value) {
      // if its not threaded keep moving
      if (!cur->rightTh && cur->right != nullptr) {
        cur = cur->right;
      } else {
        break;
      }
    }
  }
  // if the new node belongs as a left child
  if (num < cur->value) {
    // the left thread should be the parents predecessor
    newNode->left = cur->left;
    if (newNode->left != nullptr) {
      newNode->leftTh = true;
    }
    // the right thread should point to the parent
    newNode->right = cur;
    newNode->rightTh = true;
    // set parent to false thread and point to new node
    cur->leftTh = false;
    cur->left = newNode;
    inserted = true;
    size++;
  }
  // if the new node belongs as a right child
  // opposite of left thread
  if (num > cur->value) {
    // predecessor should be parent
    newNode->left = cur;
    newNode->leftTh = true;
    // successor should be parents successor
    newNode->right = cur->right;
    if (newNode->right != nullptr) {
      newNode->rightTh = true;
    }
    cur->rightTh = false;
    cur->right = newNode;
    inserted = true;
    size++;
  }
  return inserted;
}

// case for node with one child
// case for node with two children
// case for leaf
bool BinaryTree::remove(int target) {
  bool removed = false;
  // cur will store the target value to remove
  Node *cur = nullptr;
  // retrieve the target node to remove,
  // if retrieve is false, theres no such value in the tree will return false
  if (retrieve(target, cur)) {
    // keep track of what kind of child the leaf is
    // need to find the leaf and its parent

    Node *parent = nullptr;
    bool left;

    // if the target node is a leaf
    if ((cur->leftTh && cur->rightTh) ||
        (cur->rightTh && cur->left == nullptr) ||
        (cur->leftTh && cur->right == nullptr)) {
      // get the parent node
      parent = findParent(cur, left);
      // if the leaf is a left child
      if (left) {
        removeLeft(parent, cur);
        removed = true;
      }
      // if  the leaf is a right child
      else if (!left) {
        removeRight(parent, cur);
        removed = true;
      }
    }

    // if the target node has two children - no threads and no nullptrs
    else if (!cur->leftTh && !cur->rightTh && (cur->right != nullptr) &&
             (cur->left != nullptr)) {
      Node *leaf = nullptr;
      // if it has a left subtree
      if (!cur->left->leftTh) {
        // get the rightmost of the left subtree
        leaf = rightLeaf(cur->left);
      }
      // if it has a right subtree and not a left
      else if (!cur->right->rightTh) {
        parent = cur->right;
        leaf = leftLeaf(cur->right);
      }
      // if it doenst have subtrees just get the rightmost
      else {
        leaf = rightLeaf(cur);
      }
      // leaf is now a value that can replace the position of the node to remove
      parent = findParent(leaf, left);
      // swap the values
      cur->value = leaf->value;
      // remove the leaf
      if (left) {
        removeLeft(parent, leaf);
        removed = true;
      } else {
        removeRight(parent, leaf);
        removed = true;
      }
    }

    // node with one child
    else if ((cur->leftTh && !cur->rightTh) || (!cur->leftTh && cur->rightTh) ||
             (cur->left == nullptr && !cur->rightTh) ||
             (!cur->leftTh && cur->right == nullptr)) {
      parent = findParent(cur, left);
      // find out where the one child is
      bool childLeft = true;
      if (cur->leftTh || cur->left == nullptr) {
        childLeft = false;
      }
      // if the node to remove is a left child
      if (left) {
        // if the child of the node to remove is also a left child
        if (childLeft) {
          parent->left = cur->left;
        } else if (!childLeft) {
          parent->left = cur->right;
        }
      }
      // if the node to remove is a right child
      if (!left) {
        // and has only a left child
        if (childLeft) {
          parent->right = cur->left;
        }
        // or has only a right child
        if (!childLeft) {
          parent->right = cur->right;
        }
      }
      // node to remove no longer a child in the tree
      // set the threads

      // if its an end node set the nullptr to the child's left thread
      if (cur->left == nullptr) {
        cur->right->left = nullptr;
        cur->right->leftTh = false;
      } else if (cur->left->rightTh) {
        cur->left->right = cur->right;
      }

      if (cur->right == nullptr) {
        cur->left->right = nullptr;
        cur->left->rightTh = false;
      } else if (cur->right->leftTh) {
        cur->right->left = cur->left;
      }

      // delete the node
      cur->left = nullptr;
      cur->right = nullptr;
      delete cur;
      size--;
      removed = true;
    }
  }
  return removed;
}

// private helper function for remove - removes a leaf node that is a left child
// to the parent
void BinaryTree::removeLeft(BinaryTree::Node *parent,
                            BinaryTree::Node *toRemove) {
  parent->left = toRemove->left;
  // check if its the smallest value in the tree & set the thread
  if (parent->left != nullptr) {
    parent->leftTh = true;
  }
  toRemove->left = nullptr;
  toRemove->right = nullptr;
  delete toRemove;
  size--;
}

// private helper function for remove - removes a node that is a right child to
// the parent
void BinaryTree::removeRight(BinaryTree::Node *parent,
                             BinaryTree::Node *toRemove) {
  parent->right = toRemove->right;
  // check if its the smallest value in the tree & set the thread
  if (parent->right != nullptr) {
    parent->rightTh = true;
  }
  toRemove->left = nullptr;
  toRemove->right = nullptr;
  delete toRemove;
  size--;
}

// retrieve value stored in tree
bool BinaryTree::retrieve(const int target, BinaryTree::Node *&returned) const {
  Node *cur = root;
  bool found = false;
  while (cur != nullptr) {
    if (target == cur->value) {
      found = true;
      returned = cur;
      break;
    }
    if (target < cur->value && !cur->leftTh) {
      cur = cur->left;
    } else if (target > cur->value && !cur->rightTh) {
      cur = cur->right;
    } else {
      break;
    }
  }
  return found;
}

// same functionality as retrieve
bool BinaryTree::contains(int target) const {
  // dummy node to call retrieve
  BinaryTree::Node *found = nullptr;
  return retrieve(target, found);
}

// iteratively deletes the tree
void BinaryTree::clear() {
  // to traverse the tree inorder
  Node *cur = leftLeaf(root);
  while (cur != nullptr) {
    // one step behind cur, as to not delete links
    Node *toDelete = cur;
    // move cur forward a node
    if (cur->rightTh || cur->right == nullptr) {
      cur = cur->right;
    } else if (cur->right != nullptr) {
      cur = leftLeaf(cur->right);
    }
    // delete the previous node
    toDelete->left = nullptr;
    toDelete->right = nullptr;
    delete toDelete;
  }
}

// print the tree using the << operator overload
void BinaryTree::display() const { std::cout << *this; }

// returns if the current tree is empty
bool BinaryTree::isEmpty() const { return root == nullptr; }

int BinaryTree::height(BinaryTree::Node *nodePtr) const {
  if (nodePtr == nullptr) {
    return 0;
  } else {
    // recursively dives down the left side of the tree
    // to the leaves and finds the max depth
    int lef = 1;
    if (!nodePtr->leftTh) {
      lef += height(nodePtr->left);
    }
    // recursively dives down the right side of the tree
    // to the leaves and finds the max depth
    int rig = 1;
    if (!nodePtr->rightTh) {
      rig += height(nodePtr->right);
    }

    // returns whichever is deeper
    if (lef < rig) {
      return rig;
    } else {
      return lef;
    }
  }
}

// returns the size count
int BinaryTree::getCount() const { return size; }

// returns the root data
int BinaryTree::getRootData() const { return root->value; }

// continually get midpoint of array and call insert
void BinaryTree::buildBinaryTree(int nums[], int left, int right) {
  if (right < left) {
    return;
  } else {
    int mid = (right + left) / 2;
    insert(nums[mid]);
    buildBinaryTree(nums, left, mid - 1);
    buildBinaryTree(nums, mid + 1, right);
  }
}

// find the leftmost node from location
BinaryTree::Node *BinaryTree::leftLeaf(BinaryTree::Node *location) {
  BinaryTree::Node *temp = location;
  while (temp->left != nullptr && !temp->leftTh) {
    temp = temp->left;
  }
  return temp;
}

// finds the rightmost node from location
BinaryTree::Node *BinaryTree::rightLeaf(BinaryTree::Node *location) {
  BinaryTree::Node *temp = location;
  while (temp->right != nullptr && !temp->rightTh) {
    temp = temp->right;
  }
  return temp;
}

// returns height of the total tree
int BinaryTree::getHeight() const { return height(root); }

// does not work on root
BinaryTree::Node *BinaryTree::findParent(BinaryTree::Node *child,
                                         bool &left) const {
  // case handling for root being passed in
  if (child == root) {
    return nullptr;
  }
  Node *cur = root;
  while (cur != nullptr) {
    if (cur->right == child) {
      left = false;
      return cur;
    }
    if (cur->left == child) {
      left = true;
      return cur;
    }
    if (child->value < cur->value) {
      cur = cur->left;
    } else if (child->value > cur->value) {
      cur = cur->right;
    }
  }
  return nullptr;
}

void BinaryTree::removeEven() {
  // move all the way left
  Node *cur = leftLeaf(root);
  std::stack<int> even;
  while (cur != nullptr) {

    if (cur->value % 2 == 0) {
      even.push(cur->value);
    }
    if (cur->rightTh) {
      cur = cur->right;
    } else if (cur->right != nullptr) {
      cur = leftLeaf(cur->right);
    } else if (cur->right == nullptr) {
      break;
    }
  }

  while (!even.empty()) {
    remove(even.top());
    even.pop();
  }
}