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
    inline void setPileupFile(string  a_pileupfile) {pileupfile = a_pileupfile; verifyPileupFile();}
    inline string getPileupFile(){return pileupfile;}
    
    void trainErrorModel();
    void loadErrorModel();
    
    void run();
    SeqFreq getSeqFreq();
    
    // setup plugins
    inline void setPileupParser(PileupParser * a_PileupParser) { ptr_PileupParser = a_PileupParser; }
    inline void setErrorModeler(ErrorModeler * a_ErrorModeler) {ptr_ErrorModeler = a_ErrorModeler;}
    inline void setPreCaller(PreCaller * a_PreCaller) { ptr_PreCaller = a_PreCaller; }
    
    // verification
    inline void verifyPileupFile(){fs_pileupfile = open_infile(pileupfile); fs_pileupfile.close();}
    void verifyPlugin();
    
    // get signature of plugins
    inline string getSigPileupParser() {return ptr_PileupParser->getSignature();}
    inline string getSigErrorModeler() {return ptr_ErrorModeler->getSignature();}
    inline string getSigPreCaller() {return ptr_PreCaller->getSignature();}
    
    
protected:
    // input pileup file 
    string pileupfile;
    ifstream fs_pileupfile;

    // results
    SeqFreq seqfreq;
    
    // plugins
    PileupParser * ptr_PileupParser;
    ErrorModeler * ptr_ErrorModeler;
    PreCaller * ptr_PreCaller;

    
};

#endif /* IGDA_H */

