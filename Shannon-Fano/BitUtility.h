//
// Created by 38668 on 9. 05. 2023.
//

#ifndef SHANNON_FANO_BITUTILITY_H
#define SHANNON_FANO_BITUTILITY_H
#include <stack>
#include <cstring>

void printStack(const std::stack<std::string>& stack) {
    std::stack<std::string> tempStack = stack;  // Create a temporary copy of the stack
    std::cout <<"\n";
    while (!tempStack.empty()) {
        std::string element = tempStack.top();  // Get the top element of the stack
        std::cout << element;      // Print the element
        tempStack.pop();                         // Remove the element from the stack
    }
    std::cout <<"\n";
}

bool toBit(char a) {
    return (a == '1');
}

void writeBitsToFile(const std::string& fileName, const std::string& bitString, Frequency frequencys) {
    std::ofstream file(fileName, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing\n";
        return;
    }
    std::stack<std::string> store; //TU JE STACKKKKKKKKK!!!!!
    //tu gleamo kolko nul je treba našopat prej
    int remainingChars = bitString.length() % 8;

    //obični proces
    for (int i = bitString.length() - 8; i >= 0; i -= 8) {
        std::string substr = bitString.substr(i, 8);
        store.push(substr);
    }
    //našopaj nule
    if (remainingChars != 0) {
        std::string paddedChars = std::string(8 - remainingChars, '0') + bitString.substr(0, remainingChars);
        store.push(paddedChars);
    }

    printStack(store);

    char letter;
    int letterFrequecy;
    //TU NAŠOPAMO TABELO FREKVENC V FILE
    for (auto&i:frequencys.getFrekvence()){
        letter = i.getValue();
        letterFrequecy = i.getFrequency();
        const char* pLetter = &letter; //int je 4byte. Če bi mel samo char bi piso samo 1 byte, zato dam pointer
        const char* pLF = reinterpret_cast<const char*>(&letterFrequecy);
        file.write(pLetter, strlen(pLetter));
        file.write(pLF, strlen(pLF));
        std::cout << "pLF: "<< pLF<< letterFrequecy;

    }
    //BINARNI ZAPIS ZA NEWLINE. loči kompresirano kodo od ostale;

    char newline = '\n';
    file.write(&newline, sizeof(newline));
    while(!store.empty()){
        const char value = std::stoi(store.top(), nullptr, 2);
        file.write(&value, sizeof(value));
        std::cout << value << "\n";
        store.pop();
    }

    file.close();
}

void readCompression(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file for reading\n";
        return;
    }

    char ch;
    bool newlineFound = false;
    while (file.read(&ch, sizeof(ch))) {
        if (ch == '\n') {
            newlineFound = true;
            break;
        }
    }

    if (!newlineFound) {
        std::cerr << "Newline character not found in the file\n";
        return;
    }
    char data;
    while (file.read(&data, sizeof(data))) {
        std::cout << data; //tu je pol procesiranje
    }

    file.close();
}
void readTable(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file for reading\n";
        return;
    }

    char buffer[4];
    int num;
    bool isChar = true;

    while (file.read(buffer, sizeof(buffer)) && buffer[0] != '\n') {
        if (isChar) {
            // Process the character
            std::cout << "Char: " << buffer[0] << std::endl;
        } else {
            // Process the integer
            std::memcpy(&num, buffer, sizeof(num));
            std::cout << "Int: " << num << std::endl;
        }

        isChar = !isChar; // Toggle between char and int positions
    }

    file.close();
}


#endif //SHANNON_FANO_BITUTILITY_H
