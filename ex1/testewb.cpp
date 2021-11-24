#include <iostream>
#include <fstream>


using namespace std;


int main (){  /* Write the least significant bit of the argument */

ofstream ofs ("filename.txt");
unsigned char buffer = 0x00;
int nbits = 0;
int bytes = 2;
int nbytes = 0;
unsigned char bit = 1;
unsigned char comp = 0xFF;


while (nbytes < bytes){
    int nbits = 0;
    for(int i = 0; i < 8; i++){
           buffer = ((buffer << 1) | bit);  ///shift 1 possição e set the last bit of the buffer to bit
            nbits++;
}

cout << "teste" << "buffer= "<< buffer << "nbits =" << nbits << endl;
cout << "tamanho do buffer= " << sizeof (buffer) << "bytes" << endl;

    if(nbits = 8)
        {
        ofs << buffer;
        ofs.flush();
        buffer = 0;
        nbytes++;
    }

  }
ofs.close();
return 0;
}
