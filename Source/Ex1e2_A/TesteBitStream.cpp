#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>
#include "BitStreamV2.h"



int main (int argc, char* argv[])
{
///  argv[1]=Ajuda (/?), ou caminho e nome do ficheiro original
///  argv[2]=caminho e nome do ficheiro novo
///  argv[3]=indicação da flag -r ou -w, -r para ler ou -w para escrever
///  argv[4]=indicação da flag -b, para indicar o n.º de bits a ler e escrever
///  argv[5]=valor de [-b size], para indicar o n.º de bits a ler e escrever


        if (argc<=2 || argv[1]=="/?")	{	// indicação da sintaxe de commando
		cout << "Usage: ./program_name ./original_file_name.wav ./copy_file_name.wav -r or -w [-b size] \n\n options:\n\t -b size\t Number of bits to read or write (all if not specified).\n" << endl; // \a toca um som de alerta (byte 0x07 in ASCII encoding)
	}


    if (argc==5){
        string option=argv[4];
        if (option=="-b")	{	     // indicação da sintaxe de commando
		cout << "The number of bits to read or write after the argument \"-b\", is missing\n\n options:\n\t -b size\t Number of bits to read or write (all if not specified).\n" << endl; // \a toca um som de alerta (byte 0x07 in ASCII encoding)

		}}


    if (argc==6){

        long numbits=atoi(argv[5]);

        cout << "argc=6" << endl;
        cout << numbits << endl;

    }


    else {

    if (argc==4){

//    BitStream bs("teste.txt", "c");

    BitStream bs("teste.txt", "c", 3);

//        bs.Read_file();

//    bs.settotal_nbits(2);

/*
    bs.Write_tbits (0);
    bs.Write_tbits (0);
    bs.Write_tbits (1);
    bs.Write_tbits (0);
    bs.Write_tbits (0);
    bs.Write_tbits (0);
    bs.Write_tbits (1);
    bs.Write_tbits (1);
    bs.Write_tbits (0);
    bs.Write_tbits (0);
    bs.Write_tbits (1);
    bs.Write_tbits (0);
    bs.Write_tbits (0);
    bs.Write_tbits (0);
    bs.Write_tbits (1);
    bs.Write_tbits (1);
*/

//    bs.ofs.close();

    }



    }
return 0;
}
