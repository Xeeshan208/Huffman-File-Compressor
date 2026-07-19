#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "HuffmanTree.h"
#include <bitset>

class Compressor {
public:

    string readFile(string filename) {
        ifstream file(filename);
        string text((istreambuf_iterator<char>(file)),
                     istreambuf_iterator<char>());
        return text;
    }

    string encodeText(string text, map<char,string>& codes) {
        string encoded = "";
        for(char c : text)
            encoded += codes[c];
        return encoded;
    }

    // ?? BIT PACKING FUNCTION (REAL COMPRESSION)
    void saveCompressedBinary(string filename, string encodedText) {
        ofstream file(filename, ios::binary);

        int padding = 8 - (encodedText.size() % 8);
        encodedText.append(padding, '0');

        // first byte store padding info
        bitset<8> padBits(padding);
        file.put((char)padBits.to_ulong());

        for(int i=0; i<encodedText.size(); i+=8) {
            bitset<8> byte(encodedText.substr(i,8));
            file.put((char)byte.to_ulong());
        }

        file.close();
    }
};

#endif
