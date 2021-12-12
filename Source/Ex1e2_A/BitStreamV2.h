#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

class BitStream
{
private:
    string rfilename;
    std::string wfilename;
    char wbuffer=0;
    char rbuffer;
    float tnbytes=0;
    char buffer_size=8;
    int nbits;

public:
    fstream ifs;
    fstream ofs;
    uint8_t bit;
    float total_nbits=0;


/*------------ Parameterized Constructors-------------*/
    BitStream (string filename, char* x, long y)
    {
        total_nbits = y;
        if (x == "d"){
            wfilename = filename;
            std::filesystem::path p = filename, e = ".bin";
            p.replace_extension(e);
            rfilename = p.string();
            cout << "In = " << wfilename << endl;
        }

        if (x == "c"){
            rfilename = filename;
            std::filesystem::path p = filename, e = "bin";
            p.replace_extension(e);
            wfilename = p.string();
            cout << "Out = " << wfilename << endl;
        }


        if (total_nbits!=0){
            Read_file_tbits ();
        } else {
            Read_file();
        }
    }

/**______________________________________________________________
_______________________ Methods_________________________________

Read_file (char wb): para abrir o ficheiro e retirar a stream;
Read(): para ler a stream bit a bit;
Read_tbits(): para ler a stream bit a bit,  até ao limite de "tbits";
Write_file (char wb): para criar o ficheiro e gravar o byte;
Write(uint8_t bit): para juntar o byte bit a bit;
Write_tbits(uint8_t bit, tbits) para juntar o byte bit a bit, até ao limite de "tbits"__**/


///
    void Read_file ()
    {
        ifs.open(rfilename, std::fstream::app | std::fstream::binary | std::fstream::in | std::fstream::ate);
        cout << "filesize " <<  ifs.tellg() << endl;
        cout << "In = " <<  rfilename << endl;
        ifs.seekg (0, ios::beg);

        while (ifs.get(rbuffer)){
             Read (rbuffer);
        }
    ofs.close();
    }

 ///
    void Read_file_tbits ()
    {
        tnbytes = ceil(total_nbits/buffer_size);
        ifs.open(rfilename, std::fstream::app | std::fstream::binary | std::fstream::in | std::fstream::ate);
        cout << "Filesize = " <<  ifs.tellg() << " Bytes -> " << tnbytes << " Byte(s)" << "(" << total_nbits << " bit(s))" << endl;
        cout << "In = " <<  rfilename << endl;
        ifs.seekg (0, ios::beg);

        for (long i = 1;  i <= tnbytes; i++){
            ifs.get(rbuffer);
            tnbytes--;
            Read (rbuffer);
                    }
    ofs.close();
    }

///
    void Read(char rb)
        {
        if (tnbytes == 0 && total_nbits != 0){
                int a = static_cast<int>(total_nbits); int b = static_cast<int>(buffer_size);
                nbits = a % b;

        } else {

        nbits = buffer_size;
        }
        uint8_t rcomp = 0x80;  // 10000000

        for (int i = nbits; i > 0; i--){
            bit = ((rcomp & rb)) >> i-1; //0x80=10000000 (binário). bit= o bit mais significativo 1º n=0, depois faz o shift
            rcomp =(rcomp >> 1);

            Write(bit);    ///fazer aqui qualquer coisa com o bit, tipo: comparar, etc
        }
     }
///
    void Write_file (char wb){

        ofs.open(wfilename, std::fstream::app | std::fstream::binary);    // para adicionar, caso o ficheiro exista usar:  std::ofstream::app . std::ofstream::binary para que o output seja em binário
            ofs.write(&wb, 1);
            ofs.flush();
            ofs.close();
    }
///
    void Write(uint8_t bit)
    {
        if (nbits < buffer_size+1){            //reset do contador dos bits no buffer para saber quando o buffer está cheio e que deve escrever para o fichreiro
            bit = (bit << nbits-1);
            wbuffer = (wbuffer | bit );  ///shifts 1 possição e set the last bit of the buffer to bit
            nbits--;
            }

        if (nbits==0)
            {
            nbits=8;
            Write_file (wbuffer);
            }
    }
///
    void Write_tbits(uint8_t bit)
    {
        for(int i = 1; i = total_nbits; i++){
            if (nbits < 9){           //reset do contador dos bits no buffer para saber quando o buffer está cheio e que deve escrever para o fichreiro
                bit = (bit << nbits-1);
                wbuffer = (wbuffer | bit );  ///shifts 1 possição e set the last bit of the buffer to bit
                nbits--;
            }

            if (nbits==0)
            {
                nbits=8;
                Write_file (wbuffer);
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




#endif
