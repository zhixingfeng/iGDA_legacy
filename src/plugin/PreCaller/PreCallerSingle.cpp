/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreCallerSingle.cpp
 * Author: zhixingfeng
 * 
 * Created on November 11, 2015, 5:17 PM
 */

#include "PreCallerSingle.h"

PreCallerSingle::PreCallerSingle() {
    signature = "PreCallerSingle";
}

PreCallerSingle::PreCallerSingle(const PreCallerSingle& orig) {
}

PreCallerSingle::~PreCallerSingle() {
}

void PreCallerSingle::callVar(int min_cvg) {
    if (ptr_ErrorModeler == NULL)
        throw runtime_error("Error in PreCallerSingle::callVar: ptr_ErrorModeler is NULL.");
    if (err_context_file == "")
        throw runtime_error("Error in PreCallerSingle::callVar: err_context_file is empty.");
                
    // reference genome
    ptr_ErrorModeler->getRefGenome();
    
    // scan the pileupfile 
    ifstream fs_pileupfile; open_infile(fs_pileupfile, pileupfile);
    ptr_PileupParser->setPileupFileStream(& fs_pileupfile);
    while (true) {
        ptr_PileupParser->readLine();
        if (fs_pileupfile.eof()) break;
        
        // get frequency of current locus
        ptr_PileupParser->calBaseFreq();
        BaseFreq basefreq = ptr_PileupParser->getBaseFreq();
        if (basefreq.cvg < min_cvg) {
            varstat[basefreq.refID].push_back( VarStat(NAN, NAN, basefreq.cvg, NAN, basefreq.locus) );
            continue;
        }
        
        
        
    }
    fs_pileupfile.close();
}






