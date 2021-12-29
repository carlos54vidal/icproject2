#ifndef GOLOMB_H
#define GOLOMB_H

#include <iostream>
#include <fstream>
#include <math.h>
#include "BitStream.h"

using namespace std;

class Golomb
{

    public:
    int m;
    string filename;

    uint8_t set_m(){
        cout << "Introduza o valor de m: " << endl;
        cin >> m;
        return m;
    }

    void G_encoder(int n){
       uint8_t q;
       int r;

       set_m();

            q = floor(n/m); //codigo unario
            r = n%m; //codigo binario

        BitStream bs(filename, "c", 0);

            for(int i=0;i<q;i++){
                bs.Write(0);
             }
            bs.Write(1); //unary code

            if(ceil(log2(m))==floor(log2(m))){ //checks if power of 2
                int a[16];
                int j;
                for (j=0;r>0;j++){
                    a[j]= r%2;
                    r = r/2;
                }
                for(int t=j-1;t>=0;t--){
                    bs.Write(a[t]); //binary code
                }
            }
            else{ //if not
                int b = ceil(log2(m));
                int x = pow(2,b)-m;
                int bc[16];
                     for (int k=0;k>0;k++){
                            bc[k]= r%2;
                            r = r/2;

                if (r<=x){ //primeiros 2^b-m valores
                     for(k=k-1;k>0;k--){ //maior que 0, descarta a primeira posicao do array(truncado)
                         bs.Write(bc[k]);
                     }
                }
                else{ //restantes
                    int z = r + pow(2,b)-m;
                    int bc2[16];

                    for(m=0;m>0;m++){
                        bc2[m] = z%2;
                        z = z/2;
                    }

                    for(m=m-1;m>=0;m--){
                        bs.Write(bc2[m]);
                    }

                }



            }

       }

    }

    void G_decoder(double n ){

    }



};


#endif
