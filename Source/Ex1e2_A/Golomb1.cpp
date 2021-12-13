#include <iostream>
#include <fstream>
#include "BitStreamV2.h"



using namespace std;

int main(){
 
    int m = 2;
    BitStream teste("teste.txt","c",1);
    teste.Read_file_tbits();

       int n = 7;  
       int q;
       int r;
            q = n/m; //codigo unario
            r = n%m; //codigo binario

       for(int i=0;i<q;i++){
       teste.Write_tbits(0);

       
             

}

