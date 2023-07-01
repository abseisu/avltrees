#ifndef __PRETTY_PRINT_H__
#define __PRETTY_PRINT_H__

#include "AVLTree.h"

/*
 * Input: N/A
 * Returns: N/A
 * Does: Pretty-prints the tree rooted at root. See pretty_print.cpp for
 *      details
 * Adnan Bseisu
 * dab262
 * CPSC 223
 * PSET 5
 * 04/17
 */
void print_pretty(Node *root, int level, int indent_space, std::ostream &out);

#endif
