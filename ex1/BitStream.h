#include <iostream>
#include <fstream>

using namespace std;

class BitStream{
    string filename;
    

};

void write_bit(char c,filename){
   ifstream ifs(filename);
        for (int i = 7; i>=0,i--){
            ifs ((c>>i) & 1);
        }
}

void read_bit(char c,string filename){
    ofstream ofs(filename);
    for(int i =7;i>=0;i--){
        ofs<< ((c>>i) & 1);
    }

void write_byte(char c,filename){

}

void read_byte(char c ){

    
}
}

