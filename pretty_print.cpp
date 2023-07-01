/* Pretty Printing for a Node
 * Code in this file was borrowed from leetcode.com:
 * http://leetcode.com/2010/09/how-to-pretty-print-binary-tree.html
 * Thanks to http://leetcode.com/members/admin/ for the code!
 * (please forgive slight formatting issues in the output!)
 * Adnan Bseisu
 * dab262
 * CPSC 223
 * PSET 5
 * 04/17
 */

#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

#include "pretty_print.h"

using namespace std;

// Find the maximum height of the binary tree
int max_height(Node *p)
{
    if (p == NULL)
    {
        return 0;
    }
    int left_height = max_height(p->left);
    int right_height = max_height(p->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

// Convert an integer value to string
string int_to_string(int val)
{
    ostringstream ss;
    ss << val;
    return ss.str();
}

// Print the arm branches (eg, /    \ ) on a line
void print_branches(int branch_len, int node_space_len, int start_len,
                    int nodes_in_this_level, const deque<Node *> &nodes_queue,
                    ostream &out)
{
    deque<Node *>::const_iterator iter = nodes_queue.begin();
    for (int i = 0; i < nodes_in_this_level / 2; i++)
    {
        out << ((i == 0) ? setw(start_len - 1) : setw(node_space_len - 2))
            << "" << ((*iter++) ? "/" : " ");
        out << setw(2 * branch_len + 2) << "" << ((*iter++) ? "\\" : " ");
    }
    out << endl;
}

// Print the branches and node (eg, ___10___ )
void print_nodes(int branch_len, int node_space_len, int start_len,
                 int nodes_in_this_level, const deque<Node *> &nodes_queue,
                 ostream &out)
{
    deque<Node *>::const_iterator iter = nodes_queue.begin();
    for (int i = 0; i < nodes_in_this_level; i++, iter++)
    {
        out << ((i == 0) ? setw(start_len) : setw(node_space_len))
            << ""
            << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
        out << setw(branch_len + 2)
            << ((*iter) ? int_to_string((*iter)->data) : "")
            << (((*iter) && (*iter)->count > 1) ? "*" : "");
        out << ((*iter && (*iter)->right) ? setfill('_') : setfill(' '))
            << setw(branch_len) << "" << setfill(' ');
    }
    out << endl;
}

// Print the leaves only (just for the bottom row)
void print_leaves(int indent_space, int level, int nodes_in_this_level,
                  const deque<Node *> &nodes_queue, ostream &out)
{
    deque<Node *>::const_iterator iter = nodes_queue.begin();
    for (int i = 0; i < nodes_in_this_level; i++, iter++)
    {
        out << ((i == 0) ? setw(indent_space + 2) : setw(2 * level + 2))
            << ((*iter) ? int_to_string((*iter)->data) : "")
            << (((*iter) && (*iter)->count > 1) ? "*" : "");
    }
    out << endl;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the
//     minimum space between nodes, while level 2 has a larger space between
//     nodes)
// indent_space  Change this to add some indent space to the left (eg,
//     indent_space of 0 means the lowest level of the left node will stick to
//     the left margin)
void print_pretty(Node *root, int level, int indent_space, ostream &out)
{
    int h = max_height(root);
    int nodes_in_this_level = 1;

    // eq of the length of branch for each node of each level
    int branch_len =
        2 * ((int)pow(2.0, h) - 1) - (3 - level) * (int)pow(2.0, h - 1);

    // distance between left neighbor node's right arm and right neighbor
    // node's left arm
    int node_space_len = 2 + (level + 1) * (int)pow(2.0, h);

    // starting space to the first node to print of each level (for the left
    // most node of each level only)
    int start_len = branch_len + (3 - level) + indent_space;

    deque<Node *> nodes_queue;
    nodes_queue.push_back(root);
    for (int r = 1; r < h; r++)
    {
        print_branches(branch_len,
                       node_space_len,
                       start_len,
                       nodes_in_this_level,
                       nodes_queue,
                       out);
        branch_len = branch_len / 2 - 1;
        node_space_len = node_space_len / 2 + 1;
        start_len = branch_len + (3 - level) + indent_space;
        print_nodes(branch_len,
                    node_space_len,
                    start_len,
                    nodes_in_this_level,
                    nodes_queue,
                    out);

        for (int i = 0; i < nodes_in_this_level; i++)
        {
            Node *curr_node = nodes_queue.front();
            nodes_queue.pop_front();
            if (curr_node)
            {
                nodes_queue.push_back(curr_node->left);
                nodes_queue.push_back(curr_node->right);
            }
            else
            {
                nodes_queue.push_back(NULL);
                nodes_queue.push_back(NULL);
            }
        }
        nodes_in_this_level *= 2;
    }
    print_branches(branch_len,
                   node_space_len,
                   start_len,
                   nodes_in_this_level,
                   nodes_queue,
                   out);
    print_leaves(indent_space, level, nodes_in_this_level, nodes_queue, out);
}
