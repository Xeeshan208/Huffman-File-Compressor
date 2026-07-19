// Node.h
#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node {
public:
    char ch;          // character
    int freq;         // frequency
    Node* left;       // left child
    Node* right;      // right child

    // Constructor for leaf node
    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = NULL;
    }

    // Constructor for internal node
    Node(Node* l, Node* r) {
        ch = '\0'; // internal nodes have no character
        freq = l->freq + r->freq;
        left = l;
        right = r;
    }
};

#endif
