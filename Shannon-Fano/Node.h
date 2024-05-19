//
// Created by 38668 on 14. 05. 2023.
//

#ifndef SHANNON_FANO_NODE_H
#define SHANNON_FANO_NODE_H
#include <iostream>

class Node{
private:
    char value;
    int frequency;
    std::string binaryCode;

public:
    Node(char value, int frequency): value(value), frequency(frequency){};
    char getValue()const{
        return value;
    }
    int getFrequency() const{
        return frequency;
    }
    std::string getBinaryCode() const{
        return binaryCode;
    }
    void appendBit(char a){
        if(a == '0' || a == '1'){
            binaryCode += a;
        }return;
    }

};
#endif //SHANNON_FANO_NODE_H
