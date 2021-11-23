#include <iostream>
#include <fstream>

//00000000 0
//00000001 1
//00000010 2
//00000100 4
//00001000 8
//00010000 16
//00100000 32
//01000000 64
//10000000 128

using namespace std;


class BitStream{
    private:
     int i=1;
     int x;
     int z = 10;
   public:
     uint8_t write_bit(uint8_t c){
     uint8_t buffer=0;
     int x;
     int z = 10;
     switch(i){
          case 1:
               x = 128; break;
          case 2:
               x = 64;break;
          case 3:
               x = 32; break;
          case 4:
               x = 16; break;
          case 5:
               x = 8; break;
          case 6:
               x = 4; break;
          case 7:
               x = 2; break;
          case 8:
               x = 1; break;     
     }
     if(c == 0){                                                   
          buffer = (c >> i);
          i++;
     }
     else {
          buffer = c >> i;
          buffer || x;
          i++;
     }
  

     return buffer;
     
   }
    
};



