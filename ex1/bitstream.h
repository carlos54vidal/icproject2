#ifndef BITSTREAM_H
#define BITSTREAM_H


class Bitstream
{
    public:
        Bitstream(S W);
        virtual ~Bitstream();

        /** Loads an text file from a given file path.
     * @Returns true if the file was successfully loaded
     */
    bool load (string filePath);

    /** Saves an audio file to a given file path.
     * @Returns true if the file was successfully saved
     */
    bool save (std::string filePath, AudioFileFormat format = AudioFileFormat::Wave);

    protected:

    private:
        void writebit (S w){

        }
         void readbit (S w)

};

//=============================================================
/* IMPLEMENTATION */
//=============================================================
/*
writebit: função para escrever os bits para o buffer
readbit: função para ler os bits do buffer
bs: função/classe para ler ou escrever o byte do/para o ficheiro. Primeiro argumento="path/nome_do_ficheiro", segundo argumento="w" para write ou "r" para read.
*/
//=============================================================

template <class T>

void Bitstream<T> bs(string filePath, char l){    // se l="w" vai executar escrever(write), se l="r" vai executar ler (read)

ofstream ofs(filePath, ios::binary | ios::out);
ifstream ifs (filePath, ios::binary | ios::in );

unsigned char buffer;        /// buffer= o byte para o qual vamos escrever ou do qual vamos ler os bits


///ler
if (l="r"){
while(ifs.get(buffer)) {



}
}
///escrever
if (l="w"){


ofs << buffer << endl;

}
{
    if (ofs.is_open())
    {
        for (size_t i = 0; i < fileData.size(); i++)
        {
            char value = (char) fileData[i];
            ofs.write (&value, sizeof (char));
        }

        ofs.close();

        return true;
    }

    return false;
}

{
        // check the file exists
    if (! file.good())
    {
        reportError ("ERROR: File doesn't exist or otherwise can't load file\n"  + filePath);
        return false;
    }

    std::vector<uint8_t> fileData;

	file.unsetf (std::ios::skipws);

	file.seekg (0, std::ios::end);
	size_t length = file.tellg();
	file.seekg (0, std::ios::beg);

	// allocate
	fileData.resize (length);

	file.read(reinterpret_cast<char*> (fileData.data()), length);
	file.close();

	if (file.gcount() != length)
	{
		reportError ("ERROR: Couldn't read entire file\n" + filePath);
		return false;
}

}



//=============================================================
template <class T>

void Bitstream<T> writeBit(unsigned char bit){  /* Write the least significant bit of the argument */

ofstream ofs ("filename.txt");
uint8_t buffer = 0x00;
int nbits = 0;
int bytes = 2;
int nbytes = 0;
uint8_t bit = 1;
uint8_t comp = 0xFF;


while (nbytes < bytes){
    int nbits = 0;
    for(int i = 0; i < 8; i++){
           buffer = ((buffer << 1) | bit);  ///shift 1 possição e set the last bit of the buffer to bit
            nbits++;
}

cout << "teste" << "buffer= "<< buffer << "nbits =" << nbits << endl;
cout << "tamanho do buffer= " << sizeof (buffer) << "bytes" << endl;
cout << "tamanho do buffer= " << sizeof (int8_t) << endl;

    if(nbits = 8)
        {
        ofs << buffer;
        ofs.flush();
        buffer = 0x00;
        nbytes++;
    }

  }
ofs.close();

return 0;

}






/*
 buffer = buffer | (i<<(7-nbits)); //Did it write the right bit to ostream ?
 nbits++;

}
*/


//=============================================================

template <class T>
void Bitstream<T> readbit(int unsigned char bit){

size_t
sizeof (buffer)

ifstream ifs ("filename.txt")

uint8_t bit = 0x80;  // 10000000
uint8_t buffer;
uint8_t firstBit = buffer & bit; // Extract the first bit of x


while (ifs.get(buffer)) {

    sizeof (buffer)
    int nbits = 8;
    int n = 0;
    for(int i = 8; i > 0; i--){
            bit = (buffer << n) & 0x80; //0x80=10000000 (binário). bit= o bit mais significativo 1º n=0, depois faz o shift
            n=1;

///fazer aqui qualquer coisa com o bit, tipo: comparar, etc


        nbits-- /// contador do bit que está a ser lido no byte
        }

    if(nbits = 1){

///    fazer aqui qualquer coisa com o byte

        nbits = 8;
    }




/*    i = (1 & buffer>>(7-nbits)); //This could be the problem, I'm not getting the writing bit
    nbits++;*/




}







#endif // BITSTREAM_H
