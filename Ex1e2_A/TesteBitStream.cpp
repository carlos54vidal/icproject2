#include <iostream>
#include <fstream>
#include "BitStream.h"





int main ()
{

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
}
