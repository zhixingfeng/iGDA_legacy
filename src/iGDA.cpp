/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iGDA.cpp
 * Author: zhixingfeng
 * 
 * Created on November 11, 2015, 4:08 PM
 */

#include "iGDA.h"

iGDA::iGDA() {
    // initialize pileupfile
    pileupfile = "";
    
    // initialize plugins
    ptr_PileupParser = NULL;
    ptr_PreCaller = NULL;
}

iGDA::iGDA(const iGDA& orig) {
    
}

iGDA::~iGDA() {
}

void iGDA::run(){
    // check if pileupfile is set
    if (pileupfile == "") 
        throw runtime_error("error in iGDA::run: pileupfile has not beeb setup yet.");
    
    // check plugins
    if (ptr_PileupParser == NULL)
        throw runtime_error("error in iGDA::run: PileupParser has not beeb setup yet.");
    if (ptr_PreCaller == NULL)
        throw runtime_error("error in iGDA::run: PreCaller has not beeb setup yet.");
}


SeqFreq iGDA::getSeqFreq(){
    throw "run not implemented yet"; 
}