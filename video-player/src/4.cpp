#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>
#include <vector>
#include "methods.cpp"

using namespace std;
using namespace cv;

class BitStream {
    public:
        int pos = 0;
        unsigned char buff = 0;
        const char* filename;

        BitStream(const char* fn) {
            filename = fn;
        }

        void writeBit(int bit) {
            //cout << bit;
            if (bit) 
                buff |= (1 << pos);

            pos++;
            //cout << pos;

            if (pos == 8) {
                ofstream ofs("test.bin", ios::binary);
                ofs.write(reinterpret_cast<char*>(&buff), sizeof(buff) * sizeof(char));
                ofs.close();
                pos = 0;
                buff = 0;
            }
        }
        
        void readfile() {
            int length;
            char* buffer;
            ifstream ifsb;
            ifsb.open("test.bin", ios::binary);

            ifsb.seekg (0, ios::end);
            length = ifsb.tellg();
            ifsb.seekg (0, ios::beg);

            buffer = new char[1];

            ifsb.read(buffer, 1);
            if (ifsb) cout << "Read successfully!";
            else cout << "Error!";
            ifsb.close();
            //for (char x: buffer) cout << x << endl;
        }
};

int main(void)
{
    ofstream o;

    BitStream bs("teste.txt");
    bs.writeBit(0);
    bs.writeBit(1);
    bs.writeBit(1);
    bs.writeBit(1);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);

    //bs.flushBits();
    
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(1);
    

    
    bs.readfile();

    /*
    //Test to write binary file
    vector<int> v;
    for (int i = 0 ; i < 10 ; i++) v.push_back(i * 10);

    ofstream ofsb("data.bin", ios::binary); 
    ofsb.write(reinterpret_cast<char*>(v.data()), v.size() * sizeof(int)); 
    ofsb.close();

    //Test to read binary file
    v.clear();
    v.resize(10);
    ifstream ifsb("data.bin", ios::binary); 
    ifsb.read(reinterpret_cast<char*>(v.data()), v.size() * sizeof(int)); 
    ifsb.close();
    for(auto x : v) cout << x << endl;
    */
    

    
}

