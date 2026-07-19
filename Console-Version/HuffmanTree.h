// HuffmanTree.h
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "Node.h"
#include <queue>
#include <map>
#include <fstream>

using namespace std;

// comparator for priority queue (min heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

class HuffmanTree {
public:
    Node* root;
    map<char, string> huffmanCodes;

    // Step 1: Frequency Count
    map<char,int> buildFrequencyTable(string text) {
        map<char,int> freq;
        for(char c : text)
            freq[c]++;
        return freq;
    }

    // Step 2: Build Huffman Tree
    void buildTree(string text) {
        auto freqTable = buildFrequencyTable(text);
        priority_queue<Node*, vector<Node*>, Compare> pq;

        for(auto pair : freqTable)
            pq.push(new Node(pair.first, pair.second));

        while(pq.size() != 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();

            Node* newNode = new Node(left, right);
            pq.push(newNode);
        }

        root = pq.top();
    }

    // Step 3: Generate Codes using Recursion
    void generateCodes(Node* node, string code) {
        if(!node) return;

        // Leaf node
        if(node->ch != '\0')
            huffmanCodes[node->ch] = code;

        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    }

    void buildCodes() {
        generateCodes(root, "");
    }
};

#endif
