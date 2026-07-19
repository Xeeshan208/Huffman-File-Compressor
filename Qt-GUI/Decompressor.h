#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "Node.h"
#include <bitset>
#include <fstream>

class Decompressor {
public:

    // ?? READ BINARY FILE
    string readCompressedBinary(string filename) {
        ifstream file(filename, ios::binary);
        string bits = "";

        char paddingChar;
        file.get(paddingChar);
        int padding = (int)paddingChar;

        char byte;
        while(file.get(byte)) {
            bitset<8> bitsByte(byte);
            bits += bitsByte.to_string();
        }

        bits.erase(bits.size() - padding);
        return bits;
    }

    string decodeText(string encoded, Node* root) {
        string decoded = "";
        Node* curr = root;

        for(char bit : encoded) {
            curr = (bit=='0') ? curr->left : curr->right;

            if(curr->left == NULL && curr->right == NULL) {
                decoded += curr->ch;
                curr = root;
            }
        }
        return decoded;
    }
};

#endif
