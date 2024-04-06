#include <iostream>
#include <fstream>

#include "HuffmanCode.h"

std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    std::string content;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }

    return content;
}

void code2file(const std::string &code) {
    std::ofstream outputFile("output.bin", std::ios::out | std::ios::binary);

    // 将01信息写入二进制文件
    char buffer = 0; // 用于存储每个比特位
    int count = 0; // 计数器

    for (char bit : code) {
        if (bit == '1') {
            buffer = (buffer << 1) | 1; // 将1写入buffer
        } else {
            buffer = buffer << 1; // 将0写入buffer
        }
        count++;

        // 当buffer中的比特位达到8个时，将buffer写入文件
        if (count == 8) {
            outputFile.write(&buffer, 1);
            buffer = 0;
            count = 0;
        }
    }

    // 如果buffer中还有剩余的比特位，将其写入文件
    if (count > 0) {
        buffer = buffer << (8 - count); // 将剩余的比特位移到最高位
        outputFile.write(&buffer, 1);
    }

    outputFile.close();
}

std::string file2code() {
    std::ifstream inputFile("output.bin", std::ios::in | std::ios::binary);

    std::string binaryString; // 用于存储读取的01字符串

    char buffer;
    while (inputFile.read(&buffer, 1)) {
        for (int i = 7; i >= 0; --i) {
            if ((buffer >> i) & 1) {
                binaryString += "1"; // 如果当前比特位为1，添加"1"到字符串
            } else {
                binaryString += "0"; // 如果当前比特位为0，添加"0"到字符串
            }
        }
    }

    inputFile.close();

    return binaryString;
}

int main() {
    HuffmanCode* hc = new HuffmanCode();

    int num;
    while (true) {
        std::cout << "1. Print Huffman Code\n";
        std::cout << "2. Encode\n";
        std::cout << "3. Decode\n";
        std::cout << "4. Exit\n";
        std::cin >> num;

        if (num==1) {
            hc->printCodes();
        } else if (num==2) {
            std::cout << "Encode data.txt file to output.bin file\n";
            std::string data = readFileToString("data.txt");
            std::string code = hc->encoding(data);
            code2file(code);
        } else if (num==3) {
            std::string new_code = file2code();
            std::string new_data = hc->decoding(new_code);
            std::cout << "Decoded data:\n" << new_data << std::endl;
        } else {
            break;
        }
    }

    return 0;
}

