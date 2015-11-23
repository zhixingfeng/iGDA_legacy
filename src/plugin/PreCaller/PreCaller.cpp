/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreCaller.cpp
 * Author: zhixingfeng
 * 
 * Created on November 11, 2015, 4:54 PM
 */

#include "PreCaller.h"

PreCaller::PreCaller() {
    ptr_PileupParser = NULL;
    ptr_ErrorModeler = NULL;
    signature = "PreCaller";
}

PreCaller::PreCaller(const PreCaller& orig) {
}

PreCaller::~PreCaller() {
}

void PreCaller::setPileupParser(PileupParser* a_PileupParser) {
    if (pileupfile == "")
        throw runtime_error("Error in PreCaller::setPileupParser: pileupfile is empty.");
    ptr_PileupParser = a_PileupParser;
}

void PreCaller::setErrorModeler(ErrorModeler* a_ErrorModeler) {
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in PreCaller::setErrorModeler: ptr_PileupParser is NULL.");
    ptr_ErrorModeler = a_ErrorModeler;
}