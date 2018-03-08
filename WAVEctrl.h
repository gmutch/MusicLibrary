/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WAVEctrl.h
 * Author: gavin.mutch
 *
 * Created on March 6, 2018, 4:30 PM
 */

//Definitions from http://soundfile.sapp.org/doc/WaveFormat/

#ifndef WAVECTRL_H
#define WAVECTRL_H

#include <string>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <iostream>

union ByteArray4
{
    uint32_t bytes4;
    char bytes[4];
};

union ByteArray2
{
      uint16_t bytes2;
      char bytes[2];  
};

typedef union ByteArray4 ByteArray4;
typedef union ByteArray2 ByteArray2;

    class wave
    {
    private:
        std::string filename;
        
        
    public:
            std::string ChunkID;
            ByteArray4 ChunkSize;
            std::string Format;

            std::string Subchunk1ID;
            ByteArray4 Subchunk1Size;
            ByteArray2 AudioFormat;
            ByteArray2 NumChannels;
            ByteArray4 SampleRate;
            ByteArray4 ByteRate;
            ByteArray2 BlockAlign;
            ByteArray2 BitsPerSample;

            std::string Subchunk2ID;
            ByteArray4 Subchunk2Size;

            std::vector<uint8_t> data;
            
            setFilename(std::string filename);
            std::string getFilename();
            
            int8_t openFile(void);
            
    };


#endif /* WAVECTRL_H */

