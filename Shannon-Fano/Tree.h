//
// Created by 38668 on 8. 05. 2023.
//
#include "Frequency.h"
#include <vector>
#ifndef SHANNON_FANO_TREE_H
#define SHANNON_FANO_TREE_H
bool compareNodeFrequency(const Node& node1, const Node& node2) {
    return node1.getFrequency() > node2.getFrequency();
}
class TreeNode{
public:
    std::vector<Node>values;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(std::vector<Node> v):values(v){};
};
class Tree{
    std::vector<TreeNode*> forDestructor; //da lahko napišemo destruktor pol
    TreeNode* root = nullptr;
    std::vector<Node> listi;

public:
    explicit Tree(TreeNode*root):root(root){
        forDestructor.push_back(root);
    };
    ~Tree(){
        for(auto&i:forDestructor){
            delete i;
        }
    }


    void devide(TreeNode*treeNode){
        int sum1 = 0;
        int sum2 = 0;
        int totalSum = 0;
        for(auto&i:treeNode->values){
            totalSum+=i.getFrequency();
        }
        std::vector<Node> v1;
        std::vector<Node> v2;
        for(auto&i:treeNode->values){
            if (sum1 + i.getFrequency() <= totalSum / 2) {
                i.appendBit('0');
                v1.push_back(i);
                sum1 += i.getFrequency();
            } else {
                i.appendBit('1');
                v2.push_back(i);
                sum2 += i.getFrequency();
            }
        }
        TreeNode* nov1 = new TreeNode(v1);
        TreeNode* nov2 = new TreeNode(v2);

        forDestructor.push_back(nov1);
        forDestructor.push_back(nov2);
        treeNode->left = nov1;
        treeNode->right = nov2;
    }
    void divideLeaves(TreeNode* treeNode) {
        //cekne če je list
        if (treeNode->left == nullptr && treeNode->right == nullptr) {
            // če ma list več ko eno vrednost
            if (treeNode->values.size() > 1) {
                //kliči devide
                this->devide(treeNode);

                //rekurziji
                divideLeaves(treeNode->left);
                divideLeaves(treeNode->right);
            }else{listi.push_back(treeNode->values[0]);}
        }
        std::sort(listi.begin(), listi.end(), compareNodeFrequency);
    }
    void printListi(){
        for(auto&i:listi){
            std::cout<< i.getValue()<< " "<< i.getFrequency()<< " "<<i.getBinaryCode()<<std::endl;
        }
    }
    std::string getCharBitValue(char a){
        std::string ret;
        for(auto&i:listi){
            if(i.getValue() == a){
                return i.getBinaryCode();
            }
        }return "Not found";
    }
    const std::vector<Node> &getListi() const {
        return listi;
    }

};


#endif //SHANNON_FANO_TREE_H
