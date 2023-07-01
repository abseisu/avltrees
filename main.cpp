/*
 * main.cpp
 *
 *  Main driver for testing the AVLTree class
 * Adnan Bseisu
 * dab262
 * CPSC 223
 * PSET 5
 * 04/17
 */

#include <iostream>
#include "AVLTree.h"

using namespace std;

void print_tree_details(AVLTree &t)
{
        t.print_tree();
        cout << "\n";
        cout << "min: " << t.find_min() << "\n";
        cout << "max: " << t.find_max() << "\n";
        cout << "nodes: " << t.node_count() << "\n";
        cout << "count total: " << t.count_total() << "\n";
        cout << "tree height: " << t.tree_height() << "\n";
        cout << "\n";
}

int main()
{
        AVLTree t;
        int values[] = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
        int num_values = sizeof(values) / sizeof(int);

        for (int i = 0; i < num_values; i++)
        {
                t.insert(values[i]);
        }
        cout << "Original tree "
             << "(asterisks denote a count of more than 1):\n";
        print_tree_details(t);

        // make a copy with copy constructor
        AVLTree t_copy_constructor = t;
        // t_copy_constructor.print_tree();

        // make a copy with assignment overload
        AVLTree t_copy_1;
        t_copy_1 = t;

        // remove a node with one children
        cout << "Removing 9 from original tree:\n";
        t.remove(9);
        print_tree_details(t);

        t = t_copy_1;

        // remove a node with one child
        cout << "Removing 1 from original tree:\n";
        t.remove(1);
        print_tree_details(t);

        t = t_copy_1;

        // remove a node with one child
        cout << "Removing 11 from original tree:\n";
        t.remove(11);
        print_tree_details(t);

        t = t_copy_1;

        // remove a node with one child (but the count is 2)
        cout << "Removing 5 from original tree "
             << "(should still have one 5):\n";
        t.remove(5);
        print_tree_details(t);

        // check if the tree contains values
        t = t_copy_1;
        for (int i = -10; i < 20; i++)
        {
                cout << "Tree "
                     << (t.contains(i) ? "contains " : "does not contain ")
                     << "the value " << i << "\n";
        }
        cout << "\nFinished!\n";
        return 0;
}
