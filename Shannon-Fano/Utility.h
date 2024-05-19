//
// Created by 38668 on 13. 05. 2023.
//

#ifndef SHANNON_FANO_UTILITY_H
#define SHANNON_FANO_UTILITY_H
#include <iostream>
#include <cmath>
std::string reverseString(const std::string& str) {
    std::string ret = str;
    int start = 0;
    int end = str.length()-1;
    while(start < end){
        std::swap(ret[start], ret[end]);
        start ++;
        end --;
    }return ret;

}
std::string charToBinStr(char x){
    int decValue = static_cast<int>(static_cast<unsigned char>(x));
    std::string ret;
    int temp;
    while (decValue != 0){
        temp = decValue%2;
        ret += static_cast<char>(temp+'0');
        decValue = (decValue-temp)/2;
    }
    ret = reverseString(ret);
    if(ret.length() < 8){
        int diff = 8-ret.length();
        std::string prefix(diff, '0');
        ret = prefix+ret;
    }return ret;
}
std::string decToBinStr(int x, int bytes){
    std::string ret;
    int temp;
    while(x !=0){
        temp = x%2;
        ret += static_cast<char>(temp+'0');
        x = (x-temp)/2;
    }
    ret = reverseString(ret);
    if(ret.length() < bytes*8){
        int diff = bytes*8-ret.length();
        std::string prefix(diff, '0');
        ret = prefix+ret;
    }return ret;
}

void writeBitsToFile(const std::string& fileName, const std::string& bitString) {
    BinWriter writer(fileName.c_str());

    for (char bit : bitString) {
        if (bit == '0') {
            //cout << false;
            writer.writeBit(false);
        } else if (bit == '1') {
            //cout << true;
            writer.writeBit(true);
        } else {
            // Handle error or invalid bit value
            std::cerr << "Invalid bit value: " << bit << std::endl;

            return;
        }
    }
}

std::string readBitsFromFile(const std::string& fileName) {
    BinReader reader(fileName.c_str());
    std::string bitString;

    while (true) {
        bool bit = reader.readBit();
        if (!reader.f.good()) break; // konec fila

        bitString += (bit ? '1' : '0');
    }

    // Reverse the bit string
    //std::reverse(bitString.begin(), bitString.end());
    bitString = bitString.substr(8);
    //std::cout << bitString << std::endl;
    return bitString;
}

template <typename T>
T binStrToInt(const std::string& str){
    T ret = 0;
    for(int i=0; i< str.length(); i++){
        ret += ((int)str[i]-'0') *pow(2, str.length()-1-i);
    }
    return ret;
}

char binaryStrToChar(const std::string& binaryString) {
    if (binaryString.length() != 8) {
        // Handle error: binary string should have exactly 8 characters
        throw std::runtime_error("Invalid binary string length");
    }

    int value = 0;
    for (char bit : binaryString) {
        if (bit == '0') {
            value = (value << 1) + 0;
        } else if (bit == '1') {
            value = (value << 1) + 1;
        } else {
            // Handle error: invalid character in binary string
            throw std::runtime_error("Invalid binary character");
        }
    }

    return static_cast<char>(value);
}
#endif //SHANNON_FANO_UTILITY_H
