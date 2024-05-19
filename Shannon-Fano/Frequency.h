//
// Created by 38668 on 8. 05. 2023.
//

#ifndef SHANNON_FANO_FREQUENCY_H
#define SHANNON_FANO_FREQUENCY_H
#include <vector>
#include <algorithm>
#include "Node.h"

class Frequency{
private:
    int* arr = new int[256]{0};
    std::vector<Node> frekvence;
public:
    explicit Frequency(const std::string& text){
        for(auto i:text){
            arr[(int)(unsigned char)i]++;
        }
        for(int i = 0; i <256; i++){
            if (arr[i] > 0){
                frekvence.emplace_back((char)i, arr[i]);
            }
        }
        std::sort(frekvence.begin(), frekvence.end(), [](const Node& a, const Node& b) {
            return a.getFrequency() > b.getFrequency(); //sortiramo po padajočih vrednostih
        });
    }
    ~Frequency(){
        delete[] arr;
    }
    int getFrequency(char a){
        return arr[(int)(unsigned char)a];
    }
    int getSize(){
        return frekvence.size();
    }
    std::vector<Node>getFrekvence(){
        return frekvence;
    }
    void printFreq(){
        for(auto&i: frekvence){
            std::cout << i.getValue()<<": "<<i.getFrequency()<<"\n";
        }
    }


};
#endif //SHANNON_FANO_FREQUENCY_H
