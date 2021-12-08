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
    long count_tbits=0;//contador do total de bits
    int nbits=8;

public:
/*---------------Atributos de Read-------------------*/
//    string rfilename;
    uint8_t rcomp = 0x80;  // 10000000
    char rbuffer;
    uint8_t bit;
    uint8_t firstBit = rbuffer & rcomp; // Extract the first bit of x
/*---------------Atributos de Write------------------*/
//    string wfilename;
    char wbuffer=0;
    //    uint8_t* pbuffer = &buffer;
        int bytes = 1;
        int nbytes;
    //    uint8_t bit = 1;
    //    uint8_t wcomp = 0xFF;
/*------------ Parameterized Constructors-------------*/
    BitStream (string filename, char* x)
    {
        if (x == "w"){
            wfilename=filename;
        }
        if (x == "r"){
            rfilename=filename;
        }

    }


/*---------------------------------------------------*/

    void Read() /// Read the characters of a text file byte to byte
    {
        long total_nbits;
        ifstream ifs;
        ifs.open(rfilename, std::ifstream::app | std::ifstream::binary | std::ifstream::in | std::ifstream::ate);

    while(total_nbits=0 || count_tbits<=total_nbits){

        ifs.get(rbuffer);
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
    }


    void Write(uint8_t bit)
    {
    long total_nbits;
    ofstream ofs(wfilename, std::ofstream::app | std::ofstream::binary);    // para adicionar, caso o ficheiro exista usar:  std::ofstream::app . std::ofstream::binary para que o output seja em binário
//    ofs.open;

//    while (count_tbits<=total_nbits){
        if (nbits < 9){            //reset do contador dos bits no buffer para saber quando o buffer está cheio e que deve escrever para o fichreiro
            bit = (bit << nbits-1);
            wbuffer = (wbuffer | bit );  ///shifts 1 possição e set the last bit of the buffer to bit
            nbits--;
            count_tbits++;
    //
            cout << "teste " << "buffer= "<< wbuffer << " nbits =" << nbits << endl;
    //        cout << "tamanho do buffer= " << sizeof (wbuffer) << "bytes" << endl;
    //        cout << "tamanho do buffer= " << sizeof (int8_t) << endl;

            }
        cout << "nbits: " << nbits << endl;


        if (nbits==0/* || count_tbits==total_nbits*/)
            {
            nbits=8;
//          ofs << wbuffer;
            ofs.write(&wbuffer, 1);
            ofs.flush();
    //      wbuffer = 0x00;
            nbytes++;
            cout << "Caracter : " << wbuffer << endl;
            wbuffer=0x00;
            cout << "total bits: " << total_nbits << endl;
            };

//    }
      ofs.close();


    }

};



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



#endif
