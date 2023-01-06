/**
 * @file binarytree.h
 * @brief declares the binarytree class
 * @author Kendra Walker 
 */

#ifndef ASSIGNMENT5_BINARYTREE_H
#define ASSIGNMENT5_BINARYTREE_H

#include <ostream>
#include <iostream>
#include <stack>

class BinaryTree {
    // print the tree in inorder traversal to the console
    friend std::ostream& operator<<(std::ostream& Out, const BinaryTree& BinaryTree);

private:

    struct Node
    {
        // constructor
        Node() : value(0), right(nullptr), left(nullptr),
                 leftTh(false), rightTh(false){}

        explicit Node(int num) : value(num), right(nullptr), left(nullptr),
                        leftTh(false), rightTh(false){
        }
     
        int value;
        Node* right;
        Node* left;
        bool leftTh;
        bool rightTh;
    };

    int size;
    Node* root;

    /** leftLeaf - gets the leftmost leaf of the tree or subtree
     * @brief traverses to the leftmost node 
     * @param location starting node location to find the leftmost from
     * @return a pointer to the leftmost node
     */
    static Node* leftLeaf(Node *location) ;

    /** rightLeaf - gets the rightmost leaf of the tree or subtree
     * @brief traverses to the rightmost node 
     * @param location starting node location to find thef rightmost from
     * @return a pointer to the rightmost node
     */
    static Node* rightLeaf(Node *location) ;

    /**
    * @brief gets the height of the tree
    * @return and integer of the max tree height
    * @param nodePtr root of tree or subtree to be passed in
    */
    int height(Node * nodePtr) const;

    /** copyTree - recursive helper function to copy constructor
     * @brief will make a deep copy of another tree
     * @param nodePtr root of other tree to be passed in
     */
     void copyTree(const Node* nodePtr);

    /**
     * @brief recursively gets mid points of an array, assists with building tree
     * @param nums an array with values for the tree
     * @param left the left index of the array
     * @param right the right index of the array
     */
    void buildBinaryTree(int nums[], int left, int right);

    /**
    * @brief helper function for remove method, will find parent of a leaf node
    * @param child the node to find the parent of
    * @param left a boolean to store the type of child the child is
    * @return the parent node of the target child node
    */
    Node* findParent(Node* child, bool& left) const;

    /** removeLeft - helper function for remove
    * @brief removes a left child leaf from the tree
    * @param parent - parent of the node to remove
    * @param toRemove the node that will be removed
    * @post toRemove is no longer in the tree
    */
    void removeLeft(Node* parent, Node* toRemove);

    /** removeRight - helper function for remove
    * @brief removes a right child leaf from the tree
    * @param parent - parent of the node to remove
    * @param toRemove the node that will be removed
    * @post toRemove is no longer in the tree
    */
    void removeRight(Node* parent, Node* toRemove);


public:

    /** Default constructor
     * @brief creates an empty threaded binary search tree
     * @post a tree with root = nullptr and size = 0
     */
    BinaryTree();

    /** size Constructor
     * @brief constructs and fills threaded bst
     * @param numbr numbr of tree to be constructed
     * @post a threaded BST with integer nodes 1...numbr
     */
    explicit BinaryTree(int numbr);

    /** Copy constructor
     * @brief makes a deep copy of the otherTree
     * @param otherTree to be copied
     * @post a new threaded BST duplicate of the param
     */
    BinaryTree(const BinaryTree& otherTree);

    /** Destructor
     * @brief deletes the tree and reallocates any memory
     * @post memory is deallocated
     */
    ~BinaryTree();

    /**
     * @brief clears the tree and all nodes
     * @post memory is deallocated
     */
    void clear();

    /**
     * @brief inserts a node into the tree
     * @param num and integer to be stored
     * @post node is added to the tree
     * @return bool of success
     */
    bool insert(int num);

    /**
     * @brief removes a node from the tree
     * @param target value to remove
     * @post node is removed from the tree
     * @return bool of success
     */
    bool remove(int target);

    /**
     * @brief retrieves a node from the tree
     * @param target value to retrieve
     * @param returned a reference to a pointer of the retrieved data
     * @return bool of success
     */
    bool retrieve(int target, BinaryTree::Node *&returned) const;

    /**
     * @brief checks the list for a value
     * @param target target value to find
     * @return bool of if founds
     */
    bool contains(int target) const;

    /**
    * @brief prints the contents of the tree, calls the overloaded << operator
    * @post contents of tree printed to console
    */
    void display() const;

    /**
     * @brief checks if the tree is empty
     * @return bool of if empty
     */
    bool isEmpty() const;

    /**
     * @brief gets the number of nodes in the tree
     * @return an integer of the tree size
     */
    int getCount() const;

    /** 
     * @brief returns the max height of the tree
     * @return an integer of the tree height
     */
    int getHeight() const;

    /**
     * @brief gets the value stored in the root node
     * @return the integer value stored in root
     */
    int getRootData() const;

    /**
     * @brief removes all the even number integers inserted from the size constructor
     * Does not remove even numbers insterted seperately into the tree.
     * @pre a non-empty tree
     * @post a tree with only odd values
     */
    void removeEven();

};


#endif//ASSIGNMENT5_BINARYTREE_H