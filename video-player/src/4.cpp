#include<iostream>
#include<fstream>
#include "BitStream.cpp"

using namespace std;

int main(void)
{

    BitStream bsw("test.bin", 'w');
    /*
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(0);
    bsw.writeBit(1);
    bsw.writeBit(0);
    bsw.writeBit(0);

    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(0);
    bsw.writeBit(1);
    bsw.writeBit(1);
    */

    BitStream bsr("test.bin", 'r');
    
    bsr.readFile();

    cout << "\n";

    cout << "Reading the first 3 bits, individually" << "\n";
    bsr.readBit();
    bsr.readBit();
    bsr.readBit();

    cout << "\n";
    cout << "Reading the first 11 bits" << "\n";
    
    bsr.readNBits(11);

    /*
    cout << "\n";

    cout << "Writing int 3 in 6 bits" << "\n";
    bsw.writeNBits(3,6);
    bsw.closeFO();
    */

    bsr.readFile();
    bsr.closeFI();
}

