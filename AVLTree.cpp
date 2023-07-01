/*
 * Filename: AVLTree.cpp
 * Contains: Implementation of AVL Trees for CPSC 223
 * Part of: Homework assignment "AVL Trees" for CPSC 223
 * Adnan Bseisu
 * dab262
 * CPSC 223
 * PSET 5
 * 04/17
 */

#include <iostream>

#include "AVLTree.h"
#include "pretty_print.h"

using namespace std;

/*
 * Input: data (the value to store), multiplicity of the node, height of the
 *      node, left and right child pointers
 * Returns: avl tree node.
 * Does: creates a new node with values given as input parameter
 */
static Node *new_node(int data, int multiplicity, int height, Node *left, Node *right)
{
    Node *node = new Node();

    node->data = data;
    node->count = multiplicity;
    node->height = height;
    node->left = left;
    node->right = right;

    return node;
}

/*
 * Input: data (the value to store)
 * Returns: avl tree node.
 * Does: calls a helper function to create a new node with default
 *        values parameter
 */
static Node *new_node(int data)
{
    return new_node(data, 1, 0, NULL, NULL);
}

/********************************
 * BEGIN PUBLIC AVLTREE SECTION *
 ********************************/

AVLTree::AVLTree()
{
    root = NULL;
}

AVLTree::AVLTree(const AVLTree &source)
{
    root = pre_order_copy(source.root);
}

AVLTree::~AVLTree()
{
    post_order_delete(root);
    root = NULL;
}

// assignment overload
AVLTree &AVLTree::operator=(const AVLTree &source)
{
    //check if root is assigned to self
    if(source.root == root){
        //done
        return *this;
    }
    //delete current tree 
    post_order_delete(root);
    //copy in tree via pre order traversal
    root = pre_order_copy(source.root);
    //return tree
    return *this;
}

int AVLTree::find_min() const
{
    return find_min(root)->data;
}

int AVLTree::find_max() const
{
    return find_max(root)->data;
}

bool AVLTree::contains(int value) const
{
    return contains(root, value);
}

void AVLTree::insert(int value)
{
    root = insert(root, value);
}

void AVLTree::remove(int value)
{
    root = remove(root, value);
}

int AVLTree::tree_height() const
{
    return tree_height(root);
}

int AVLTree::node_count() const
{
    return node_count(root);
}

int AVLTree::count_total() const
{
    return count_total(root);
}

void AVLTree::print_tree() const
{
    print_pretty(root, 1, 0, std::cout);
}

/*************************
 * BEGIN PRIVATE SECTION *
 *************************/

Node *AVLTree::find_min(Node *node) const
{
    if (node->left == NULL){
        return node;
    }
    //keep going left until you get to a leaf
    else{
        return find_min(node->left);
    }
}

Node *AVLTree::find_max(Node *node) const
{
    if (node->right == NULL){
        return node;
    }
     //keep going right until you get to max node
    else{
        return find_max(node->right);
    }
}

bool AVLTree::contains(Node *node, int value) const
{
    if (node == NULL){
        return false;
    }
    // if node contains data, then contains is true
    if (node->data == value){
        return true;
    }
    //recursively check contains via left and right branches
    if (node->data > value){
        return contains(node->left, value);
    } 
    if (node->data < value){
        return contains(node->right, value);
    } 
    // if we get to here, it does not contain such a node
    return false;
}

Node *AVLTree::insert(Node *node, int value)
{
    /* BST insertion start */
    if (node == NULL)
    {
        return new_node(value);
    }
    else if (value < node->data)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = insert(node->right, value);
    }
    else if (value == node->data)
    {
        node->count++;
        return node;
    }
    /* BST insertion ends */

    /* AVL maintenance start */
    node->height = 1 + max(tree_height(node->left), tree_height(node->right));
    node = balance(node);
    /* AVL maintenace end */

    return node;
}

Node *AVLTree::remove(Node *node, int value)
{
    /* BST removal begins */
    if (node == NULL)
    {
        return NULL;
    }

    Node *root = node;
    if (value < node->data)
    {
        node->left = remove(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = remove(node->right, value);
    }
    else
    {
        // We found the value. Remove it.
        if (node->count > 1)
        {
            node->count--;
        }
        else
        {
            if (node->left == NULL && node->right == NULL)
            {
                root = NULL;
                delete node;
                return root;
            }
            else if (node->left != NULL && node->right == NULL)
            {
                root = node->left;
                node->left = NULL;
                delete node;
            }
            else if (node->left == NULL && node->right != NULL)
            {
                root = node->right;
                node->right = NULL;
                delete node;
            }
            else
            {
                Node *replacement = find_min(node->right);
                root->data = replacement->data;
                root->count = replacement->count;
                replacement->count = 1;
                root->right = remove(root->right, replacement->data);
            }
        }
    }
    /* BST removal ends */

    /* AVL maintenance begins */
    if (root != NULL)
    {
        root->height = 1 + max(tree_height(root->left), tree_height(root->right));
        root = balance(root);
    }
    /* AVL maintenance ends */

    return root;
}

int AVLTree::tree_height(Node *node) const
{
    if (node == NULL){
        return -1;
    }
    // increment height for every edge traversed and add max height of left or right branch
    return (max(tree_height(node->left), tree_height(node->right)) + 1);
    
}

int AVLTree::node_count(Node *node) const
{
    if (node == NULL){
        return 0;
    }
    // increment count for every node in tree, looking at brances succesively
    else{
        return (node_count(node->left)+ node_count(node->right) + 1);
    }
}

int AVLTree::count_total(Node *node) const
{
    if (node == NULL){
        return 0;
    }
    // calculate sum of all nodes in tree
    else{
        int total_count = count_total(node->left) + count_total(node->right);
        return (node->data * node->count + total_count);
    }
}

Node *AVLTree::pre_order_copy(Node *node) const
{
    if (node == NULL)
    {
        return NULL;
    }

    //create new nodes and copy in values for whole tree
    Node *new_node = new Node();
    new_node->data = node->data;
    new_node->count = node->count;
    new_node->height = node->height;
    //access all nodes in tree via recursion on left and right brances
    new_node->left = pre_order_copy(node->left);
    new_node->left = pre_order_copy(node->right);
    // return node, once all are copied
    return new_node;
}

void AVLTree::post_order_delete(Node *node)
{
    //free all memory associated with nodes
    if (node != NULL){
        //delete all nodes in tree via recursion on left/right branches
        post_order_delete(node->left);
        post_order_delete(node->right);
        // delete node, starting at leaves and working back
        delete node;
    }
    return;
}

Node *AVLTree::balance(Node *node)
{
    //first, check if balancing is necessary
    if (height_diff(node) < 2 && height_diff(node) > -2){
        //balancing not required
        return node;
    }
    //height difference = left - right
    //if height difference is positive than it is left heavy
    if(height_diff(node) > 0){
        //perform a zigzag
        if(node->left->left == NULL){
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
        //straight line
        else{
            return right_rotate(node);
        }
    }
    //if height difference is negative, than it is right heavy
    if(height_diff(node) < 0){
        //perform a zigzag (now on the right)
        if(node->right->right == NULL){
            node->right = right_rotate(node->left);
            return left_rotate(node);
        }
        //straight line
        else{
            return left_rotate(node);
        }
    }
    //else (== 0), return node
    return node;
}

Node *AVLTree::right_rotate(Node *node)
{
    //find the parent node of the given node in the tree rooted at root
    Node *parent = find_parent(root, node);
    //store a pointer to the left child of the given node in next (root)
    Node *next = node->left;
    //replace the left child of the given node with its right child
    node->left = next->right;
    //make the given node the right child of its former left child
    next->right = node;
    if (parent != NULL){
        //check whether  given node was  left or right child of parent
        if (parent->right == node){
            //make former left child new right child
            parent->right = next;
        }
        else{
            //make former right child new left child
            parent->left = next;
        }
    }
    //return rotated (next) root 
    return next;
}

Node *AVLTree::left_rotate(Node *node)
{
    //same algorithm (just flipped) as right_rotate
    Node *parent = find_parent(root, node);
    Node *next = node->right;
    node->right = next->left;
    next->left = node;
    if (parent != NULL){
        if (parent->left == node){
            parent->left = next;
        }
        else{
            parent->right = next;
        }
    }
    return next;
}

int AVLTree::height_diff(Node *node) const
{
   //Just subtract height of right branch from height of left branch
   //By construction, negative return value means right heavy, positive means left heavy
    return (tree_height(node->left) - tree_height(node->right));
}

Node *AVLTree::find_parent(Node *node, Node *child) const
{
    if (node == NULL)
        return NULL;

    // if either the left or right is equal to the child,
    // we have found the parent
    if (node->left == child or node->right == child)
    {
        return node;
    }

    // Use the binary search tree invariant to walk the tree
    if (child->data > node->data)
    {
        return find_parent(node->right, child);
    }
    else
    {
        return find_parent(node->left, child);
    }
}
