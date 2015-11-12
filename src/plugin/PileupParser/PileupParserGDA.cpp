/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PileupParserGDA.cpp
 * Author: zhixingfeng
 * 
 * Created on November 11, 2015, 6:56 PM
 */

#include "PileupParserGDA.h"

PileupParserGDA::PileupParserGDA() {
    signature = "PileupParserGDA";
}

PileupParserGDA::PileupParserGDA(const PileupParserGDA& orig) {
}

PileupParserGDA::~PileupParserGDA() {
}

void PileupParserGDA::readLines(int nlines) {
    if (ptr_fs_pileupfile == NULL)
        throw runtime_error("Error in PileupParserGDA::readLines: ptr_fs_pileupfile has not been setup yet.");
}

void PileupParserGDA::readLine() {
    
}


void PileupParserGDA::calBaseFreq() {
    
}
