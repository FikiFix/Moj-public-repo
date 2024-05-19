//
// Created by 38668 on 9. 05. 2023.
//

#ifndef SHANNON_FANO_BINTOOLKIT_H
#define SHANNON_FANO_BINTOOLKIT_H
#include <iostream>
#include <fstream>

class BinWriter {
public:
    int k;
    std::ofstream f;
    char x;

    BinWriter(const char *p) : k(0) {
        f.open(p, std::ios::binary);
    }

    ~BinWriter() {
        if (k > 0) writeByte(x);
        f.close();
    }

    void writeByte(char v) {
        f.write((char*)&v, 1);
    }

    void writeInt(int y) {
        f.write((char*)&y, 4);
    }

    void writeBit(bool b) {
        if (k == 8) {
            writeByte(x);
            k = 0;
        }
        x ^= (-b ^ x) & (1 << k);
        k++;
    }
};

class BinReader {
public:
    int k;
    std::ifstream f;
    char x;

    BinReader(const char *p) : k(0) {
        f.open(p, std::ios::binary);
    }
    ~BinReader(){
        f.close();
    }

    char readByte() {
        f.read((char*)&x, 1);
        return x;
    }

    bool readBit() {
        if (k == 8) {
            readByte();
            k = 0;
        }
        bool b = (x >> k) & 1;
        k++;
        return b;
    }
};
#endif //SHANNON_FANO_BINTOOLKIT_H
