#include <iostream>
#include <fstream>



using namespace std;




class BitStream{
   private:
   public:

   const string filename;

   void Write(uint8_t bit);
     
};

 void BitStream::Write(uint8_t bit){
     uint8_t buffer;
     int bytes = 1;
     int nbytes;
     int nbits;

     if (nbits >= 8){
      nbits=0;}    
           buffer = ((buffer << 1) | bit);  ///shifts 1 possi��o e set the last bit of the buffer to bit
            nbits++;
     cout << "nbits: " << nbits << endl;


     ofstream ofs(filename, std::ofstream::app);    // para adicionar, caso o ficheiro exista usar:  std::ofstream::app

     if (nbits==8)
            {
            ofs << buffer;
            nbytes++;
            cout << "Caracter : " << buffer << endl;
            };
     ofs.close();

   };


