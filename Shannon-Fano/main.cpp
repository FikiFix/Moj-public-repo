#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Frequency.h"
#include "Tree.h"
#include "BinToolkit.h"
#include "Utility.h"
#include "Decompressor.h"
using namespace std;

ofstream out;

string inputText(const string &pot) {
	ifstream input(pot);
	stringstream sstream;

	if (!input.is_open()) {
		return string();
	}

	sstream << input.rdbuf();
	return sstream.str();
}


void eraseBinaryFile(const char* filename) {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Failed to open the file for erasing." << std::endl;
        return;
    }
    file.close();
    std::cout << "File content erased." << std::endl;
}







int main(int argc, const char *const argv[]) {
    if (std::string(argv[1]) == "c"){
        eraseBinaryFile(argv[2]);

        string text = inputText(R"(C:\Users\38668\Desktop\Shannon-Fano\lorem_ipsum.txt)");
        //cout << text;
        Frequency f = Frequency(text);
        TreeNode *root = new TreeNode(f.getFrekvence());
        Tree tree = Tree(root);
        tree.divideLeaves(root);
        //tree.printListi();
        string outText;
        for (auto i: text) {
            outText += tree.getCharBitValue(i);
        }
        //cout << "Out text:" << outText; //to je kompresija texta


        std::string file = argv[2];

        //prvi byte v datoteki uporabimo za naznanitev dolžine abecede
        int alphabetSize = f.getSize();

        string inText; //to bomo pol v file insertali
        inText = decToBinStr(alphabetSize, 1); //255 znakov -> 1 byte je dost;

        //4byti za hrambo dolžine texta
        inText += decToBinStr(outText.length(), 4); //to mamo limited na int. Če rabimo lahko še bol stisnemo

        for (auto &i: f.getFrekvence()) {
            inText += charToBinStr(i.getValue()); //shranimo char - 1byte
            inText += decToBinStr(i.getFrequency(), 4); //shranimo frekvenco - 4byti = sizeof(int)
        }
        inText += outText;

        writeBitsToFile(file, inText);
        cout << "file compressed to: "<< file;
    }

    if(std::string(argv[1]) == std::string(1, 'd')){
        std::string file = argv[2];
        Decompressor decompressor = Decompressor(file);
        //cout << decompressor.getBinStr();
        std::cout << std::endl;
        decompressor.preberiFrekvence();
        decompressor.addBinValuesToFrequency();
        //decompressor.printFrekvence();
        //cout << decompressor.findLetter("110")<< endl;
        //cout << decompressor.getText()<< endl;
        out.open("out.txt");
        out << decompressor.decriptText();
        cout << "Decompresed!";
    }

	return 0;
}