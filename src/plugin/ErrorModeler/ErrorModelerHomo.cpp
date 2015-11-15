/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ErrorModelerHomo.cpp
 * Author: zhixingfeng
 * 
 * Created on November 13, 2015, 12:31 PM
 */

#include "ErrorModelerHomo.h"

ErrorModelerHomo::ErrorModelerHomo() {
    signature = "ErrorModelerHomo";
}

ErrorModelerHomo::ErrorModelerHomo(const ErrorModelerHomo& orig) {
}

ErrorModelerHomo::~ErrorModelerHomo() {
}

void ErrorModelerHomo::train() {
    if (pileupfile == "")
        throw runtime_error("Error in ErrorModelerHomo::train: pileupfile has not been setup.");
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in ErrorModelerHomo::train: PileupParser has not been setup.");
    
    ifstream fs_pileupfile = open_infile(pileupfile);
    ptr_PileupParser->setPileupFileStream(& fs_pileupfile);
    while ( !fs_pileupfile.eof() ) {
        ptr_PileupParser->readLine();
        ptr_PileupParser->calBaseFreq();
        
    }
    fs_pileupfile.close();
}
