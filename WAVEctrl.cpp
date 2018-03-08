/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <fstream>

#include "WAVEctrl.h"

    wave::setFilename(std::string filename)
    {
        this->filename = filename;
    }
    
    std::string wave::getFilename()
    {
        return this->filename;
    }
    
    //http://www.cplusplus.com/reference/istream/istream/read/
    int8_t wave::openFile(void)
    {
        std::ifstream inputFile;
                
        inputFile.open(this->filename, std::ifstream::binary);
        
        if(inputFile.good())
        {
            std::cout << "File open!" << std::endl;
            
            //get the length of the whole wave file
            inputFile.seekg(0,inputFile.end);
            uint32_t fileLength = inputFile.tellg();
            inputFile.seekg(0, inputFile.beg);
            
            char * buffer = new char [4]; //create buffer for first chunk of data
            
            //get chunk name
            inputFile.read(buffer, 4);  //read in ChunkID
            this->ChunkID.assign(buffer,4);
    
            std::cout << "ChunkID = " << this->ChunkID << std::endl;
            
            //get chunk size
            inputFile.seekg(4);  //move to after ChunkID
            inputFile.read(this->ChunkSize.bytes,4);   //read in ChunkSize
            
            std::cout << "ChunkSize = ";
            std::cout << std::hex << "0x"<< this->ChunkSize.bytes4 << " = " << std::dec << this->ChunkSize.bytes4 << std::endl;
            
            //get chunk format [should be WAVE]
            inputFile.seekg(8);  //move to after ChunkID
            inputFile.read(buffer, 4);  //read in chunk format
            this->Format.assign(buffer,4);
            
            std::cout << "Format = " << this->Format << std::endl;
            
            //get subChunk1ID
            inputFile.seekg(12);  //move to after format
            inputFile.read(buffer, 4);  //read in subchunk1 name
            this->Subchunk1ID.assign(buffer,4);
            
            std::cout << "Subchunk1ID = " << this->Subchunk1ID << std::endl;
            
            //get subchunk1 size
            inputFile.seekg(16);  //move to after subchunk name
            inputFile.read(this->Subchunk1Size.bytes,4);   //read in ChunkSize
            
            std::cout << "Subchunk1Size = ";
            std::cout << std::hex << "0x"<< this->Subchunk1Size.bytes4 << " = " << std::dec << this->Subchunk1Size.bytes4 << std::endl;
            
            //Get AudioFormat
            inputFile.seekg(20);  //move to audio format varaible, 1 is uncompressed
            inputFile.read(this->AudioFormat.bytes,2);   //read in audio format
            
            std::cout << "AudioFormat = ";
            std::cout << std::dec << this->AudioFormat.bytes2;
            
            if(this->AudioFormat.bytes2 == 1) std::cout << "(uncompressed)" << std::endl;
            else
            {
                std::cout << "(some form of compression)" << std::endl;
            }
            
            //Get number of channels
            inputFile.seekg(22);  //move to number of channels
            inputFile.read(this->NumChannels.bytes,2);   //read in number of channels
            
            std::cout << "Number of Channels = ";
            std::cout << std::dec << this->NumChannels.bytes2 << std::endl;
            
            //Get sample rate
            inputFile.seekg(24);  //move to sample rate
            inputFile.read(this->SampleRate.bytes,4);   //read in sample rate
                        
            std::cout << "Sample Rate = ";
            std::cout << std::dec << this->SampleRate.bytes4 << std::endl;
            
            //Get ByteRate
            inputFile.seekg(28);  //move to byte rate
            inputFile.read(this->ByteRate.bytes,4);   //read in byterate
            
            std::cout << "Byte Rate = ";
            std::cout << std::dec << this->ByteRate.bytes4 << std::endl;
            
            //Get BlockAlign
            inputFile.seekg(32);  //move to Block Align
            inputFile.read(this->BlockAlign.bytes,2);   //read in byterate
            
            std::cout << "Block Align = ";
            std::cout << std::dec << this->BlockAlign.bytes2 << std::endl;
            
            //Get BitsperSample
            inputFile.seekg(34);  //move to Block Align
            inputFile.read(this->BitsPerSample.bytes,2);   //read in byterate
            
            std::cout << "Bits per Sample = ";
            std::cout << std::dec << this->BitsPerSample.bytes2 << std::endl;
            
            //Get Subchunk2ID
            inputFile.seekg(36);  //move to after format
            inputFile.read(buffer, 4);  //read in subchunk2 name
            this->Subchunk2ID.assign(buffer,4);
            
            std::cout << "Subchunk2ID = " << this->Subchunk2ID << std::endl;
            
            //get subchunk2 size
            inputFile.seekg(40);  //move to after subchunk name
            inputFile.read(this->Subchunk2Size.bytes,4);   //read in ChunkSize
            
            std::cout << "Subchunk2Size = ";
            std::cout << std::hex << "0x"<< this->Subchunk2Size.bytes4 << " = " << std::dec << this->Subchunk2Size.bytes4 << std::endl;
            
            //get rawData
            inputFile.seekg(44);  //move to data
            
            this->data.resize(this->Subchunk2Size.bytes4);  //resize vector to hold Raw data
            
            for(int i = 0; i < this->Subchunk2Size.bytes4; i++)
            {
                inputFile.read(buffer, 1);
                
                data[i] = buffer[0];
            }
            
            
            std::cout << "Data[0] = 0x" << std::hex << (unsigned int)this->data[0] << std::endl;
            std::cout << "Data[1] = 0x" << std::hex << (unsigned int)this->data[1] << std::endl;
            std::cout << "Data[2] = 0x" << std::hex << (unsigned int)this->data[2] << std::endl;
            
            inputFile.close();
            return 0;
        }
        else
        {
            std::cerr << "error opening file";
            
            inputFile.close();
            return -1;
        }
    }
