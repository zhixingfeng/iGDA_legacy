/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iGDA.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 4:08 PM
 */

#ifndef IGDA_H
#define IGDA_H
#include "../include/stl.h"
#include "./plugin/plugin.h"

// SeqFreq is used for store the output of iGDA. 
// The most important output is joint probability of sequences.
struct SeqFreq{

};

// iGDA is the user-interface class. It uses other classes as plugins

class iGDA {
public:
    iGDA();
    iGDA(const iGDA& orig);
    virtual ~iGDA();
    
    // basic operations
    void setPileupFile(string  a_pileupfile);
    void run();
    SeqFreq getSeqFreq();
    
    // setup plugins
    inline void setPileupParser(PileupParser * a_PileupParser){ ptr_PileupParser = a_PileupParser;}
    inline void setPreCaller(PreCaller * a_PreCaller){ ptr_PreCaller = a_PreCaller; }
    
private:
    // input pileup file 
    string pileupfile;
    
    // results
    SeqFreq seqfreq;
    
    // plugins
    PileupParser * ptr_PileupParser;
    PreCaller * ptr_PreCaller;
    
};

#endif /* IGDA_H */

