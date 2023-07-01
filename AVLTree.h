/*
 * Filename: AVLTree.h
 * Contains: Interface of AVL Trees for CPSC 223
 * Part of: Homework assignment "AVL Trees" for CPSC 223
 * Author: Alan Weide
 * Adnan Bseisu
 * dab262
 * CPSC 223
 * PSET 5
 * 04/17
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>

/* AVL Tree Node:
 * - data is the value
 * - height is the height of the node within the tree, increasing
 *      from leaf up to the root.
 * - count is the number of times the data has been inserted
 *      into the tree (minus removals)
 *
 * We're defining this outside the class, which is really not good!
 * However, we're giving you a pretty printer for trees that we got
 * from somewhere else, and it will need the node structure.
 *
 * Your client code must NOT access nodes.
 *
 * We will take deductions for abstraction violations when we assess
 * your submission.
 */
struct Node
{
    int data;
    int height;
    int count;
    Node *left;
    Node *right;
};

class AVLTree
{
public:
    /* constructor */
    AVLTree();

    /* copy constructor */
    AVLTree(const AVLTree &source);

    /* destructor */
    ~AVLTree();

    /* assignment overload */
    AVLTree &operator=(const AVLTree &source);

    /*
     * Input: N/A
     * Returns: the minimum value in this
     * Does: Searches this for its minimum value, and returns it. Behavior
     *      is undefined if this is empty
     */
    int find_min() const;

    /*
     * Input: N/A
     * Returns: the maximum value in this
     * Does: Searches this for its maximum value, and returns it. Behavior
     *      is undefined if this is empty
     */
    int find_max() const;

    /*
     * Input: int value - value to search for
     * Returns: true if there is a node in this with data = value, false
     *      otherwise
     * Does: searches the tree for value
     */
    bool contains(int value) const;

    /*
     * Input: int value - value to insert
     * Returns: N/A
     * Does: Inserts value into this, either by creating a new node or, if
     *      value is already in this, by incrementing that node's count
     */
    void insert(int value);

    /*
     * Input: int value - the value to remove
     * Returns: N/A
     * Does: Removes value from the tree. If a node's count is greater than
     *      1, the count is decremented and the node is not removed. Nodes
     *      with a count of 1 are removed according to the algorithm
     *      discussed in class, with arbitrary decisions made in the same way
     *      as the reference implementation.
     */
    void remove(int value);

    /*
     * Input: N/A
     * Returns: the height of this
     * Does: computes and returns the height of this tree.
     */
    int tree_height() const;

    /*
     * Input: N/A
     * Returns: The number of nodes in this tree
     * Does: Counts and returns the number of nodes in this
     */
    int node_count() const;

    /*
     * Input: N/A
     * Returns: the total of all node values, including duplicates.
     * Does: Computes and returns the sum of all nodes and duplicates in
     *      this
     */
    int count_total() const;

    /*
     * Input: N/A
     * Returns: N/A
     * Does: Pretty-prints the tree
     */
    void print_tree() const;

private:
    /* the root of the tree (starts as NULL) */
    Node *root;

    /*
     * the following eight functions are private helper functions
     * for the public functions. We do not want to expose the
     * internals of the tree publicly, so we pass the root (and
     * other information in some cases) to the functions below
     * from the public functions.
     */
    Node *find_min(Node *node) const;
    Node *find_max(Node *node) const;
    bool contains(Node *node, int value) const;
    Node *insert(Node *node, int value);
    Node *remove(Node *node, int value);
    int tree_height(Node *node) const;
    int node_count(Node *node) const;
    int count_total(Node *node) const;

    /*
     * Input: Node node - a pointer to the root of the tree to copy
     * Returns: a deep copy of the tree rooted at node
     * Does: Performs a pre-order traversal of the tree rooted at node to
     *      create a deep copy of it
     */
    Node *pre_order_copy(Node *node) const;

    /*
     * Input: Node node - a pointer to the root of the tree to delete
     * Returns: N/A
     * Does: Performs a post-order traversal of the tree rooted at node to
     *      delete every node in that tree
     */
    void post_order_delete(Node *node);

    /*
     * Input: Node root - a node of the avl tree.
     * Returns: the balanced subtree.
     * Does: If unbalanced, balances the tree rooted at node.
     */
    Node *balance(Node *node);

    /*
     * Input: Node node - a node of the avl tree.
     * Returns: pointer to the root of rotated tree.
     * Does: right rotate tree rooted at node
     */
    Node *right_rotate(Node *node);

    /*
     * Input: Node node - a node of the avl tree.
     * Returns: pointer to the root of rotated tree.
     * Does: left rotate tree rooted at node
     */
    Node *left_rotate(Node *node);

    /*
     * Input: Node node - a node of the avl tree.
     * Returns: integer value signifying the height difference.
     * Does: calculates the difference in the height of the left and child
     *       subtree of node
     */
    int height_diff(Node *node) const;

    /*
     * Input: Node node - the root of the tree in which to search
     *        Node child - a pointer to the the node to search for
     * Returns: a pointer to the parent of child in the tree rooted at
     *      node, or NULL if child is not in that tree
     * Does: Searches the tree rooted at node for child, then returns
     *      that node's parent.
     */
    Node *find_parent(Node *node, Node *child) const;
};

#endif /* AVLTREE_H_ */
