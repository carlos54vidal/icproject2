#include <iostream>
#include <fstream>

using namespace std;
/*
void Writex(uint8_t bit)
{

    ofstream ofs ("filename2.txt");
    uint8_t buffer = 0x00;
    int bytes = 1;
    int nbytes = 0;
///    uint8_t bit = 1;
    uint8_t comp = 0xFF;

    while (nbytes < bytes){
        int nbits = 0;
        for(int i = 0; i < 8; i++){
           buffer = ((buffer << 1) | bit);  ///shift 1 possição e set the last bit of the buffer to bit
            nbits++;
            }
        cout << "teste" << "buffer= "<< buffer << "nbits =" << nbits << endl;
        cout << "tamanho do buffer= " << sizeof (buffer) << "bytes" << endl;
        cout << "tamanho do buffer= " << sizeof (int8_t) << endl;

        if(nbits = 8)
            {
            ofs << buffer;
            ofs.flush();
            buffer = 0x00;
            nbytes++;
            }
    }
ofs.close();


};

uint8_t Read() /// Read the characters of a text file byte to byte
{



    ifstream ifs ("filename2.txt");

    uint8_t bit = 0x80;  // 10000000
    char buffer;
    uint8_t firstBit = buffer & bit; // Extract the first bit of x
    sizeof (buffer);

    while (ifs.get(buffer)) {
        sizeof (buffer);
        int nbits = 8;
        int n = 0;
        for(int i = 8; i > 0; i--){
            bit = (buffer << n) & 0x80; //0x80=10000000 (binário). bit= o bit mais significativo 1º n=0, depois faz o shift
            n=1;

    ///fazer aqui qualquer coisa com o bit, tipo: comparar, etc


        nbits--; /// contador do bit que está a ser lido no byte


        }

    if(nbits = 1){

    ///    fazer aqui qualquer coisa com o byte

        nbits = 8;
        }
    }
return bit;
};
*/
void Write(uint8_t bit)
{

    ofstream ofs("filename2.txt", std::ofstream::app);
    uint8_t buffer/* = 0*/;
    int bytes = 1;
    int nbytes = 0;
    int nbits;
//    uint8_t bit = 1;
//    uint8_t comp = 0xFF;
if (nbits >= 8){
    nbits=0;}
//    while (nbytes < bytes){
//        int nbits = 0;
//        for(int i = 0; i < 8; i++){
           buffer = ((buffer << 1) | bit);  ///shifts 1 possição e set the last bit of the buffer to bit
            nbits++;
//            }
//        cout << "teste" << "buffer= "<< buffer << "nbits =" << nbits << endl;
//        cout << "tamanho do buffer= " << sizeof (buffer) << "bytes" << endl;
//        cout << "tamanho do buffer= " << sizeof (int8_t) << endl;
cout << "nbits: " << nbits << endl;

       if (nbits==8)
            {

//            ofs.put(buffer); //provavelmente não é a operação mais certa...
            ofs << buffer;
//            ofs.flush();
//            buffer = 0x00;
            nbytes++;
            cout << "Caracter : " << buffer << endl;
            };

ofs.close();

};



int main (){

    Write (0);
    Write (0);
    Write (1);
    Write (0);
    Write (0);
    Write (0);
    Write (1);
    Write (1);
    Write (0);
    Write (0);
    Write (1);
    Write (0);
    Write (0);
    Write (0);
    Write (1);
    Write (1);

return 0;
}
