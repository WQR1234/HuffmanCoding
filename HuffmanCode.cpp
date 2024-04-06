//
// Created by My on 2023/12/30.
//

#include "HuffmanCode.h"

#include <queue>
#include <iostream>

struct compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return (left->frequency > right->frequency);
    }
};

HuffmanNode* HuffmanCode::generate_tree() {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, compare> minHeap;
    for (auto pair : freq) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() != 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top();
}

void HuffmanCode::generate_codes(HuffmanNode* root, const std::string &code) {
    if (root) {
        if (!root->left && !root->right) {
            huffman_codes[root->data] = code;
        }
        generate_codes(root->left, code + "0");
        generate_codes(root->right, code + "1");
    }
}

std::string HuffmanCode::encoding(const std::string& data) {
    dataLen = data.size();

    for (char ch : data) {
        freq[ch]++;
    }

    HuffmanNode* root = generate_tree();
    generate_codes(root, "");

    std::string encoded_data;
    for (char ch : data) {
        encoded_data += huffman_codes[ch];
    }
    std::cout << (1.0f - encoded_data.size() / 8.0f /  (float)dataLen) * 100 << "%\n";

    return encoded_data;
}

std::string HuffmanCode::decoding(const std::string &code) {
    std::unordered_map<std::string, char> huffman_codes_reverse;
    for (const auto &pair : huffman_codes) {
        huffman_codes_reverse[pair.second] = pair.first;
    }

    std::string data, prefix;
    int cnt = 0;
    for (char ch : code) {
        prefix.push_back(ch);
        if (huffman_codes_reverse.find(prefix) != huffman_codes_reverse.end()) {
            data.push_back(huffman_codes_reverse[prefix]);
            prefix.clear();
            cnt ++;
            if (cnt==dataLen) break;
        }
    }

    return data;
}

void HuffmanCode::printCodes() {
    for (const auto &pair : huffman_codes) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << std::endl;
}

void HuffmanCode::printFreq() {
    for (const auto &pair : freq) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}






