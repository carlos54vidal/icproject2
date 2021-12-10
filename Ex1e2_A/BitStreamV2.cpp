#ifndef BITSTREAM_H
#define BITSTREAM_H


#include <iostream>
#include <fstream>
//#include <filesystem>

using namespace std;
//using namespace std::filesystem;

class BitStream //(const stream "filename", char x)
{
private:
    string wfilename;
    string rfilename;
    long count_tbits=0;//contador do total de bits
    int nbits=8;
    char wbuffer=0;
    char rbuffer;

public:
    fstream ifs;
    fstream ofs;
    long total_nbits;
    uint8_t rcomp = 0x80;  // 10000000
    uint8_t bit;
    uint8_t firstBit = rbuffer & rcomp; // Extract the first bit of x
    int bytes = 1;
    int nbytes;


/*------------ Parameterized Constructors-------------*/
    BitStream (string filename, char* x)
    {

        if (x == "w"){
//        fs::path p = filename, e = ".bin";
//        filename = p.replace_extention(e);
            wfilename=filename;
        }
        if (x == "r"){
            rfilename=filename;
        }
    }

/*______________________________________________________________
_______________________ Methods_________________________________

Read_file (char wb): para abrir o ficheiro e retirar a stream;
Read(): para ler a stream bit a bit;
Read_tbits(): para ler a stream bit a bit,  até ao limite de "tbits";
Write_file (char wb): para criar o ficheiro e gravar o byte;
Write(uint8_t bit): para juntar o byte bit a bit;
Write_tbits(uint8_t bit, tbits) para juntar o byte bit a bit, até ao limite de "tbits"__*/

    void Read_file (){

        ifs.open(rfilename, std::fstream::app | std::fstream::binary | std::fstream::in | std::fstream::ate);
        ifs.get(rbuffer);
        Read (rbuffer);
        }

    void Read(char rb)
        {
        int nbits = 8;
        int n = 0;

        for(int i = 8; i > 0; i--){

            bit = (rb << n) & rcomp; //0x80=10000000 (binário). bit= o bit mais significativo 1º n=0, depois faz o shift
            n=1;

    ///fazer aqui qualquer coisa com o bit, tipo: comparar, etc

        nbits--; /// contador do bit que está a ser lido no byte
        }

 //   if(nbits = 1){
    ///    fazer aqui qualquer coisa com o byte
 //       nbits = 8;
 //       }
    }

    void Write_file (char wb){

        ofs.open(wfilename, std::fstream::app | std::fstream::binary);    // para adicionar, caso o ficheiro exista usar:  std::ofstream::app . std::ofstream::binary para que o output seja em binário
    //    ;
            ofs.write(&wb, 1);
            ofs.flush();
    //      wbuffer = 0x00;
            nbytes++;
            cout << "Caracter : " << wb << endl;
            wbuffer=0x00;
            ofs.close();
    }

    void Write(uint8_t bit)
    {

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

        if (nbits==0)
            {
            nbits=8;
            Write_file (wbuffer);
            cout << "total bits: " << total_nbits << endl;
            }

    }
        void Write_tbits(uint8_t bit, int tbits)
    {
    for(int i=0; i<tbits; i++){
        if (nbits < 9){           //reset do contador dos bits no buffer para saber quando o buffer está cheio e que deve escrever para o fichreiro
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

        if (nbits==0)
            {
            nbits=8;
            Write_file (wbuffer);
            cout << "total bits: " << total_nbits << endl;
            }
    }

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

int main (){

///bs ("novo_ficheiro.txt", "w");

    BitStream bs("teste.txt", "w");

    bs.Write (0); //1
    bs.Write (1);//2
    bs.Write (0);//3
    bs.Write (0);//4
    bs.Write (0);//5
    bs.Write (0);//6
    bs.Write (0);//7
    bs.Write (0);//8
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
}



#endif
