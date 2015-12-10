/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreCallerMultiple.cpp
 * Author: zhixingfeng
 * 
 * Created on November 11, 2015, 5:32 PM
 */

#include "PreCallerMultiple.h"

PreCallerMultiple::PreCallerMultiple() {
    readlen = 1000;
    signature = "PreCallerMultiple";
}

PreCallerMultiple::PreCallerMultiple(const PreCallerMultiple& orig) {
}

PreCallerMultiple::~PreCallerMultiple() {
}

void PreCallerMultiple::callVar(int min_cvg, int min_cvg_ctrl, int len_l, int len_r) {
    if (pileupfile == "")
        throw runtime_error("Error in PreCallerMultiple::callVar: pileupfile is empty.");
    if (err_context_file == "")
        throw runtime_error("Error in PreCallerMultiple::callVar: err_context_file is empty.");
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in PreCallerMultiple::callVar: ptr_PileupParser is NULL.");
    if (ptr_ErrorModeler == NULL)
        throw runtime_error("Error in PreCallerMultiple::callVar: ptr_ErrorModeler is NULL.");
    
    
}

void PreCallerMultiple::calJointProb() {
    if (pileupfile == "")
        throw runtime_error("Error in PreCallerMultiple::calJointProb: pileupfile is empty.");
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in PreCallerMultiple::calJointProb: ptr_PileupParser is NULL.");
    ifstream fs_pileupfile; open_infile(fs_pileupfile, pileupfile);
    ptr_PileupParser->setPileupFileStream(& fs_pileupfile);
    
    deque <Pileup> buf;
    while (true) {
        // read line
        ptr_PileupParser->readLine();
        if (fs_pileupfile.eof()) break;
        
        // fill buffer and keep its size == readlen
        buf.push_back(ptr_PileupParser->getPileup());
        if (buf.size() > readlen)
            buf.pop_front();
        
        // scan buf to calculate joint probability
        
    }
    
    // check if readlen is larger than genome size
    if (buf.size() < readlen) 
        throw runtime_error("Error in PreCallerMultiple::calJointProb: readlen is larger than genome size.");
    
    fs_pileupfile.close();
    
    
}