/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: gavin.mutch
 *
 * Created on March 6, 2018, 4:29 PM
 */

#include <cstdlib>
#include <iostream>
#include "WAVEctrl.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    wave testObj;
    
    testObj.setFilename("a2.wav");
    
    cout << testObj.getFilename();
    
    testObj.openFile();
    
    return 0;
}

