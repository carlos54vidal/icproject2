#ifndef GOLOMB_H
#define GOLOMB_H

#include <iostream>
#include <fstream>

using namespace std;

class Golomb{
 
    public:
    int m; 
    int n;
    
    void encode(){
	   ofstream rest("rest.txt");
       int q;
       int r;
       int b;
       
       q = n/m; //código unário
       r = n%m; //código binário
              
       b = log2(m);
       
       if (r < pow(2, b+1) - m) {
			//então codificar r em binário usando b bits
	   }
	   else {
			//então codificar r+2^(b+1)-m em binário usando b+1 bits
	   }
       
	   printf("The Golomb code is %d %d\n", q, r) ;
    }

    void decode(){
		
    }
    
};
#endif
