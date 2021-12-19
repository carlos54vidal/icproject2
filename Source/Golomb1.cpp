#include <iostream>
#include <fstream>
#include <math.h>
#include "BitStreamV2.h"
#include "Dependencies/opencv2/opencv.hpp"



using namespace std;

int main(){

    int m = 2;
    BitStream teste("teste.txt","c",0);
    
    
    teste.Read(teste.rbuffer);
    
    //teste.Read_file();

    cout << "buffer" << teste.rbuffer << endl;

       int n = 7;
       int q;
       int r;
            q = n/m; //codigo unario
            r = n%m; //codigo binario



}

