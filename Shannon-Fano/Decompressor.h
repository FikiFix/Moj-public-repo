//
// Created by 38668 on 14. 05. 2023.
//

#ifndef SHANNON_FANO_DECOMPRESSOR_H
#define SHANNON_FANO_DECOMPRESSOR_H
#include "Node.h"
#include "Tree.h"
bool compareByBinValue(const Node& node1, const Node& node2) {
    return stoi(node1.getBinaryCode(), nullptr, 2) < stoi(node2.getBinaryCode(), nullptr, 2);
}

class Decompressor {
private:
    std::ifstream file;
    std::string binStr; //to je vhod
    std::vector<Node> frekvence;
    std::string texst;

public:
    explicit Decompressor(const std::string &filename) {
        file.open(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "File failed to open!";
        } else {
            binStr = readBitsFromFile(filename);
            //std::cout << binStr;
        }
    }

    std::string getBinStr() const {
        return binStr;
    }
    int getAlphabetSize(){
        std::string alphabetStr = binStr.substr(0,8);
        return binStrToInt<int>(alphabetStr);
    }
    void preberiFrekvence(){
        std::string copyBitStr = binStr.substr(40);
        for(int i = 0; i < getAlphabetSize(); i++){
            char chValue = binaryStrToChar(copyBitStr.substr(0, 8));
            //std::cout << chValue<<" ";
            int intValue = binStrToInt<int>(copyBitStr.substr(8, 32));
            //std::cout << intValue<< " ";

            frekvence.emplace_back(chValue, intValue);
            copyBitStr = copyBitStr.substr(40);
        }
        texst = copyBitStr.substr(0,getTextSize());
    }
    void printFrekvence() const{
        for(auto&i:frekvence){
            std::cout << i.getValue()<<" ";
            std::cout << i.getFrequency()<<" ";
            std::cout << i.getBinaryCode() << " ";
            std::cout << std::endl;
        }
    }
    int getTextSize(){
        //std::cout <<"Check 2"<< binStr.substr(8, 32)<<"\n"; //zakaj ni tu 40?
        return binStrToInt<int>(binStr.substr(8, 32));//zakaj ni tu 40?
    }
    std::string getText(){
        return texst;
    }

    std::vector<Node> listi(){
        TreeNode* root = new TreeNode(frekvence);
        Tree tree = Tree(root);
        tree.divideLeaves(root);
        return tree.getListi();
    }

    char findLetter(const std::string& binStr2) { //binary search
        std::vector<Node> listi = frekvence;
        int left = 0;

        int right = listi.size() - 1;
        unsigned long l;
        unsigned long r;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            //std::cout << listi[mid].getBinaryCode()<<" ";
            try{
                l = binStrToInt<long>(listi[mid].getBinaryCode());
                r = binStrToInt<long>(binStr2);
                if (listi[mid].getBinaryCode() == binStr2) {
                    return listi[mid].getValue();
                } else if (l < r) {
                    left = mid + 1; // iščemo na desno
                } else {
                    right = mid - 1; // iščemo na levo
                }
            }catch (const std::out_of_range& e) {
                // Handle the out_of_range exception
                std::cout << "Out of range error occurred. Problematic value: " << listi[mid].getBinaryCode() << std::endl;
                // Additional error handling if needed
                return '\0';
            } catch (const std::exception& e) {
                // Handle other exceptions
                std::cout << "Error: " << e.what() << std::endl;
                // Additional error handling if needed
                return '\0';
            }
        }
        return '\0';
    }


    void addBinValuesToFrequency(){
        frekvence = listi();
        std::sort(frekvence.begin(), frekvence.end(), compareByBinValue);
    }

    std::string decriptText(){
        std::string ret;

        for(int i= 0, j=1; i< texst.length();){ // && i+j<=texst.length() mby bom rabo pol
            if(findLetter(texst.substr(i,j)) == '\0'){
                j++;
            }else{
                ret += findLetter(texst.substr(i,j));
                i +=j;
                j = 1;
                //std::cout <<"found";
            }

        }
        return ret;
    }
};
#endif //SHANNON_FANO_DECOMPRESSOR_H
