#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <string>
#include <iostream>
#include <fstream>
#include "Dependencies/opencv2/opencv.hpp"
#include "Dependencies/AudioFile/AudioFile.h"
#include <filesystem> /** It needs a compiler that supports the C++17 language standard, which is implemented e.g. on the g++ compiler from the version 8 onwards,
                        but it´s recommended a g++ version release 9 or newer for full support. https://gcc.gnu.org/gcc-9/changes.html#cxx **/

using namespace cv;
using namespace std;
using namespace std::filesystem;/** It needs a compiler that supports the C++17 language standard, which is implemented e.g. on the g++ compiler from the version 8 onwards,
                                but it´s recommended the g++ version release 9 or newer for full support. https://gcc.gnu.org/gcc-9/changes.html#cxx **/

class BitStream
{
private:
    long tnbytes=0;///corresponds to the total number of Bytes to be read, on the case of an intended limit for the number of bits.
    char buffer_size=8;/// the default buffer size. Specially used to construct the wbuffer attribute (which is the "buffer" to be written to the file)
    int nbits;///attribute used to count the bit, or number of bits that are being processed.

public:
    fstream ifs; ///the object name for the input stream.
    fstream ofs; /// the object name for the output stream.
    int bit; /// bit attribute
    int total_nbits=0; /// the limited number of bits to be treated. (value to be imputed/adquired from the user)
    string file_extension;/// is required, to now how to handle the data extraction.
    string rfilename;/// the name of the input file.
    string wfilename; /// the name of the output file.
    using rbuffer_type = char;
    using wbuffer_type = char;
    char t_rbuffer;




/**------------ Parameterized Constructors-------------*/

/** the tree attributes inserted to the constructor are:
     "filename": The name of the decoded file (and realtive path, if necessary). For coding it means the name of the file to be coded, for decoding,
                it means the name of the produced file with the decoded data. It should include the correct extension, according to the datata type:
                 normaly .txt for text, .wav for audio and .png for image.
            "x": is the method that is intended to use: "c" for coding and "d" for decoding.
            "y": is the number of bits to be processed: "0" (zero) for all the bits of the original file, any other number to limit that process.
                Being that any value greater that the actual reading file size, is going to result in no limit.

This constructor is also going to set the extension of the coded file, whether it is for the reading method or the writing method, base on the name
of the inputed file name (and path), changing only the extension to ".bin".
 **/
    BitStream (string filename, const char* x, int y){
        
        rbuffer_type rbuffer = 0;
        total_nbits = y;

        if (x == "d") {
            wfilename = filename;
            std::filesystem::path p1 = filename, e = "bin";
            file_extension = std::filesystem::path(p1).extension().string();
            cout << "ext = " << file_extension << endl;
            p1.replace_extension(e);
            rfilename = p1.string();
            cout << "Out = " << wfilename << endl;
        }

        if (x == "c"){
            rfilename = filename;
            std::filesystem::path p2 = filename, e = "bin";
            file_extension = std::filesystem::path(p2).extension().string();
            cout << "ext = " << file_extension << endl;
            p2.replace_extension(e);
            wfilename = p2.string();
            cout << "Out = " << wfilename << endl;
        }
               
        if (file_extension == ".txt") {
            using rbuffer_type = char;
        }
        if (file_extension == ".wav") {
            using rbuffer_type = double;
        }
        if (file_extension == ".png") {
            using rbuffer_type = uint8_t;
        }
           

//        if (y != 0) {
//            Read_file_tbits (file_extension);
//        } else {
//            Read_file(file_extension);
//        }
    }

/**______________________________________________________________
_______________________ Methods_________________________________

Read_file (char wb): para abrir o ficheiro e retirar a stream;
Read(): para ler a stream bit a bit;
Read_tbits(): para ler a stream bit a bit,  até ao limite de "tbits";
Write_file (char wb): para criar o ficheiro e gravar o byte;
Write(uint8_t bit): para juntar o byte bit a bit;
Write_tbits(uint8_t bit, tbits) para juntar o byte bit a bit, até ao limite de "tbits"__**/


/// Method for reading a file sample by sample, character or text, with no limits.
    double Read_Audio_file ()
    {
            AudioFile<double> audioFile;

            audioFile.load(rfilename);
            double rbuffer{};
//            rbuffer = static_cast<double>(rbuffer);
            int channels = audioFile.getNumChannels();
            int numSamples = audioFile.getNumSamplesPerChannel();

            for (int i = 0; i <= numSamples; i++){
                for (int c = 0; c <= channels; c++){
                rbuffer = audioFile.samples[c][i];
                }
            }
    }

    rbuffer_type Read_Text_file (){
        if (!ifs.is_open()){
            ifs.open(rfilename, std::istream::app | std::istream::binary | std::istream::in);
            if (ifs.fail()){
                cout << "the file can't be found " << ifs.rdstate() << endl;
            }

        }            
            cout << "filesize 117 " <<  ifs.tellg() << endl;
            cout << "In = " <<  rfilename << endl;

 //           rbuffer = static_cast<char>(rbuffer);
            while (ifs.get(t_rbuffer)){
                return t_rbuffer;
 //            Read (rbuffer); // it was used to "chain" the methods together, to copy the bits to a new file with no treatment.
                }
            ofs.close();
        }

    Vec3b Read_Image_file (){
        cv::Mat img = cv::imread(rfilename);

        if (img.empty()){
            cout << "Error : Image cannot be loaded..!!" << endl;
        }
        uint8_t* pixelPtr = (uint8_t*)img.data;

        int cn = img.channels(); //gives us the colour channels (which colours they are)

            for (int r = 0; r < img.rows; r++){
                for (int c = 0; c < img.cols; c++){
                    Vec3b rbuffer = img.at<cv::Vec3b>(r,c);
                    return rbuffer;
                }
            }
    
    }

 /// Method for reading a file sample by sample, character or text, with bit limits.

    char Read_Text_file_tbits (){

        tnbytes = ceil(total_nbits/buffer_size);
        
            ifs.open(rfilename, std::fstream::app | std::fstream::binary | std::fstream::in | std::fstream::ate);
            if (ifs.fail()){
            cout << "the file "<< rfilename << " can't be found 158 " << ifs.rdstate() << endl;
            }
            cout << "Filesize 160 = " <<  ifs.tellg() << " Bytes -> " << tnbytes << " Byte(s)" << "(" << total_nbits << " bit(s))" << endl;
            cout << "In = " <<  rfilename << endl;
            ifs.seekg (0, ios::beg);
            char rbuffer{};
            for (long i = 1;  i <= tnbytes; i++){
                ifs.get(rbuffer);
                tnbytes--;
//            Read (rbuffer); // it was used to "chain" the methods together, to copy the bits to a new file with no treatment.
                return rbuffer;
            }

            
            ofs.close();
        }

        double Read_Audio_file_tbits (){


            AudioFile<double> audioFile;

            audioFile.load(rfilename);

            int channels = audioFile.getNumChannels();
            int numSamples = audioFile.getNumSamplesPerChannel();
            double rbuffer{};
            for (long i = 1;  i <= tnbytes; i++){
                for (int c = 0; c < channels; c++){
                    for (int i = 0; i < numSamples; i++){
                    rbuffer = audioFile.samples[c][i];
                    }
                }
                tnbytes--;
            }
        }
 

/** Method for extraction of each bit from the buffer. The buffer size should correspond to the sample, character or pixel size.
It starts reading from the least significant bit towards the most significant bit. It also works for either Read_file methods.**/
    void Read(uint8_t rb){

        if (tnbytes == 0 && total_nbits != 0){
                int a = static_cast<int>(total_nbits); int b = static_cast<int>(buffer_size);
                nbits = a % b;

        } else {

        nbits = buffer_size;
        }
        uint8_t rcomp = 0x80;  // 10000000

        for (int i = nbits; i > 0; i--){
            bit = ((rcomp & rb)) >> i-1; //0x80=10000000 (binário). bit= o bit mais significativo 1º n=0, depois faz o shift
            rcomp =(rcomp >> 1);

            Write(bit);    ///fazer aqui qualquer coisa com o bit, tipo: comparar, etc
        }
     }

/// Method for writing the produced buffer to the new file with no limit number of bits parameter.
    void Write_Text_file (char wb){
            ofs.open(wfilename, std::fstream::app | std::fstream::binary);    // para adicionar, caso o ficheiro exista usar:  std::ofstream::app . std::ofstream::binary para que o output seja em binário
            ofs.write(&wb, 1);
                if (ifs.bad()){
            cout << "the file can't be found " << ifs.rdstate() << endl;
            }
//              ofs.flush();
                ofs.close();
        }

        void Write_Audio_file (double wb){
            AudioFile<double> audioFile;
            AudioFile<double> audioFileOut;
            wb = static_cast<double>(wb);

            audioFile.load(rfilename);

            audioFileOut.setNumChannels(audioFile.getNumChannels());
            audioFileOut.setNumSamplesPerChannel(audioFile.getNumSamplesPerChannel());

            int channels = audioFile.getNumChannels();
            int numSamples = audioFile.getNumSamplesPerChannel();

            for (int c = 0; c < channels; c++){
                for (int i = 0; i < numSamples; i++)
                {
                audioFileOut.samples[c][i] = wb;
                }
            }
            audioFile.save (wfilename, AudioFileFormat::Wave);
        }

        void Write_Image_file (uint8_t wb){
            cv::Mat img = cv::imread(rfilename);
            if (img.empty()){
                cout << "Error : Image cannot be loaded..!!" << endl;
            }

            cv::Mat img2 = cv::Mat::zeros(cv::Size(img.rows, img.cols), CV_8UC3);

            for (int r = 0; r < img.rows; r++){
                for (int c = 0; c < img.cols; c++){
                    img2.at<cv::Vec3b>(r,c);
                }
            }
            imwrite(wfilename, img2);
        }


/// Method for constructing the buffer bit by bit, starting from the most significant bit towards the least significant bit.
    void Write(uint8_t bit)
    {
        uint8_t wbuffer{};
        wbuffer = static_cast<uint8_t>(wbuffer);
        if (nbits < buffer_size+1){            //reset do contador dos bits no buffer para saber quando o buffer está cheio e que deve escrever para o fichreiro
            bit = (bit << nbits-1);
            wbuffer = (wbuffer | bit );  ///shifts 1 possition and set the last bit of the buffer to bit
            nbits--;
            }

        if (nbits==0){
            nbits=buffer_size;
            if (file_extension == ".txt") {
                Write_Text_file(wbuffer);
            }
            if (file_extension == ".wav") {
                Write_Audio_file(wbuffer);
            }
            if (file_extension == ".png") {
                Write_Image_file(wbuffer);
            }
        }
    }

/** Method for writing the produced buffer to the new file with limited bits parameter. The minimum bit size established for I/O
operations on C++ is "8bits" so, when the user establish a smaller number of bits or a number of bits that is not multiple of "8",
 it fills the remaining bits with "0" to complete the buffer.**/
    void Write_tbits(uint8_t bit)
    {
        uint8_t wbuffer = static_cast<uint8_t>(wbuffer);
        for(int i = 1; i = total_nbits; i++){
            if (nbits < buffer_size+1){           //reset do contador dos bits no buffer para saber quando o buffer está cheio e que deve escrever para o fichreiro
                bit = (bit << nbits-1);
                wbuffer = (wbuffer | bit );  ///shifts 1 possição e set the last bit of the buffer to bit
                nbits--;
            }

            if (nbits==0){
                nbits=buffer_size;
                if (file_extension == ".txt") {
                    Write_Text_file(wbuffer);
                }
                if (file_extension == ".wav") {
                    Write_Audio_file(wbuffer);
                }
                if (file_extension == ".png") {
                    Write_Image_file(wbuffer);
                }                   
            }
        }

    }




};



/// função relativa ao processamento do ficheiro///
/*
string bs (string filename, char* t){

fstream file(filename);

file.open(filename);

if (!file.fail()){

   cout << "the file already exists" << endl;

}

return (filename, t);

};

*/




#endif
