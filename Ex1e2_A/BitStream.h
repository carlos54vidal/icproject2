#ifndef BITSTREAM_H
#define BITSTREAM_H


#include <iostream>
#include <fstream>

using namespace std;


class BitStream //(const stream "filename", char x)
{
private:
    string wfilename;
    string rfilename;
public:
/*---------------Atributos de Read-------------------*/
//    string rfilename;
    uint8_t rcomp = 0x80;  // 10000000
    char rbuffer;
    uint8_t bit;
    uint8_t firstBit = rbuffer & rcomp; // Extract the first bit of x
/*---------------Atributos de Write------------------*/
//    string wfilename;
    uint8_t wbuffer;
    //    uint8_t* pbuffer = &buffer;
        int bytes = 1;
        int nbytes, nbits;
    //    uint8_t bit = 1;
    //    uint8_t wcomp = 0xFF;
/*------------ Parameterized Constructor-------------*/
    BitStream(string filename, char* x)
    {
        if (x == "w"){
            wfilename=filename;
        }
        if (x == "r"){
            rfilename=filename;
        }
    }

/*---------------------------------------------------*/

    uint8_t Read() /// Read the characters of a text file byte to byte
    {

    ifstream ifs (rfilename);


    sizeof (rbuffer);

    while (ifs.get(rbuffer)) {
        sizeof (rbuffer);
        int nbits = 8;
        int n = 0;
        for(int i = 8; i > 0; i--){
            bit = (rbuffer << n) & 0x80; //0x80=10000000 (binário). bit= o bit mais significativo 1º n=0, depois faz o shift
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
    }





    void Write(uint8_t bit)
    {
    if (nbits >= 8){
        nbits=0;}

            wbuffer = ((wbuffer << 1) | bit);  ///shifts 1 possição e set the last bit of the buffer to bit
            nbits++;
    //
    //        cout << "teste" << "buffer= "<< wbuffer << "nbits =" << nbits << endl;
    //        cout << "tamanho do buffer= " << sizeof (wbuffer) << "bytes" << endl;
    //        cout << "tamanho do buffer= " << sizeof (int8_t) << endl;


    cout << "nbits: " << nbits << endl;

    ofstream ofs(wfilename, std::ofstream::app | std::ofstream::binary);    // para adicionar, caso o ficheiro exista usar:  std::ofstream::app . std::ofstream::binary para que o output seja em binário


       if (nbits==8)
            {

            ofs << wbuffer;
            ofs.flush();
    //      wbuffer = 0x00;
            nbytes++;
            cout << "Caracter : " << wbuffer << endl;
            };


//      ofs.close();


    }



};





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


*/

/// função relativa ao processamento do ficheiro///
/*
string bs (string filename, char* t){

fstream file(filename);

file.open(filename);

if (!file.fail()){

   cout << "the file already exists" << endl;

}

return (filename, t);

};

*/



/*
int main (){

///bs ("novo_ficheiro.txt", "w");

    BitStream bs("teste.txt", "w");

    bs.Write (0);
    bs.Write (0);
    bs.Write (1);
    bs.Write (0);
    bs.Write (0);
    bs.Write (0);
    bs.Write (1);
    bs.Write (1);
    bs.Write (0);
    bs.Write (0);
    bs.Write (1);
    bs.Write (0);
    bs.Write (0);
    bs.Write (0);
    bs.Write (1);
    bs.Write (1);

//    bs.Write.ofs.close()
return 0;
}*/

#endif
