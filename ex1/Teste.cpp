#include "BitStream.h"
int main (){
    
    char c;
    ifstream ifs("test.txt");
    BitStream bs;
    while (ifs.get(c)){
        bs.read_bit(c,"out.txt");
    }
    ifs.close();
}