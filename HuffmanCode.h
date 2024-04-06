//
// Created by My on 2023/12/30.
//

#ifndef HUFFMANCODING_HUFFMANCODE_H
#define HUFFMANCODING_HUFFMANCODE_H


#include <unordered_map>
#include <vector>
#include <string>


struct HuffmanNode {
    char data;
    unsigned frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};


class HuffmanCode {
private:
    std::unordered_map<char, int> freq;
    std::unordered_map<char, std::string> huffman_codes;

    size_t dataLen;

    HuffmanNode* generate_tree();
    void generate_codes(HuffmanNode* root, const std::string &code);

public:

    std::string encoding(const std::string& data);
    std::string decoding(const std::string& code);

    void printCodes();
    void printFreq();
};


#endif //HUFFMANCODING_HUFFMANCODE_H
