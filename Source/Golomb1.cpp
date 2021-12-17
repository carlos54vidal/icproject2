#include <iostream>
#include <fstream>
#include <math.h>
#include "BitStreamV2.h"



using namespace std;

int main(){

    int m = 2;
    BitStream teste("teste.txt","d",0);
    teste.Read_file_tbits();

       int n = 7;
       int q;
       int r;
            q = n/m; //codigo unario
            r = n%m; //codigo binario



}

