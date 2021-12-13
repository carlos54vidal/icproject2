#include <iostream>
#include <fstream>



using namespace std;

class Golomb{
 
    public:
    uint8_t m;


    void set_m(){
        cout << "Introduza o valor de m: " << endl;
        cin >> m; 
    }


    void encode(uint_t m){
       uint_t q;
       uint_t r;

       
       
            q = floor(n/m); //codigo unario
            r = n%m; //codigo binario

            for(i=0;i<q;i++){
                bs.Write_tbits(0);
             }

            bs.Write_tbits(1); //unary code

            
            if(ceil(log2(m))==floor(log2(m))){ //checks if power of 2
                int a[16];
                for (j=0;r>0;j++){
                    a[j]= r%2;
                    r = r/2;
                }

                for(j=j-1;j>=0;j--){
                    bs.Write_tbits(a[j]); //binary code
                }
            }

            else{ //if not

                int b = ceil(log2(m));
                int x = pow(2,b)-m;
                int bc[16];
                     for (k=0;k>0;k++){
                            bc[j]= r%2;
                            r = r/2;

                if (r<=x){ //primeiros 2^b-m valores
                     for(k=k-1;k>0;k--){ //maior que 0, descarta a primeira posicao do array(truncado)
                         bs.Write_tbits(bc[k]);
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
                        bs.Write_tbits(bc2[m]);
                    }

                }   


                
            }    

       } 
         



    }

    void decode( ){



    }



}
