#include "Compressor.h"
#include "Decompressor.h"

int main() {

    Compressor compressor;
    HuffmanTree tree;
    Decompressor decompressor;

    // 1?? Read file
    string text = compressor.readFile("input.txt");

    // 2?? Build tree
    tree.buildTree(text);
    tree.buildCodes();

    // 3?? Encode text
    string encoded = compressor.encodeText(text, tree.huffmanCodes);

    // 4?? Save compressed binary file
    compressor.saveCompressedBinary("compressed.bin", encoded);

    cout << "Compression Done Successfully!\n";

    // 5?? Read compressed file
    string binaryData = decompressor.readCompressedBinary("compressed.bin");

    // 6?? Decode
    string decoded = decompressor.decodeText(binaryData, tree.root);

    // 7?? Save decompressed file
    ofstream out("decompressed.txt");
    out << decoded;
    out.close();

    cout << "Decompression Done Successfully!\n";

    // ?? Compression Ratio
    double originalSize = text.size() * 8;
    double compressedSize = binaryData.size();

    cout << "Compression Ratio: "
         << (1 - compressedSize/originalSize) * 100
         << "%\n";

    return 0;
}
