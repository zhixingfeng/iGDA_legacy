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
    ptr_PileupParser = NULL;
}

iGDA::iGDA(const iGDA& orig) {
    
}

iGDA::~iGDA() {
}

void iGDA::run(){
    throw "run not implemented yet";
}

void iGDA::setPileupFile(string  a_pileupfile){
    throw "run not implemented yet";
}

SeqFreq iGDA::getSeqFreq(){
    throw "run not implemented yet"; 
}