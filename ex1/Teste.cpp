#include "BitStream.h"
int main (){
    
    char c;
    ifstream ifs("test.txt");
    BitStream bs;
    
    uint8_t x;
    int y =10;

    x = bs.write_bit(0);
    x = bs.write_bit(1);
    x = bs.write_bit(1);

    cout<< x;

    
    
}