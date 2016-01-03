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
#include "../include/headers.h"

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
    
    void trainErrorModel(string err_model_file);
    void loadErrorModel(string a_err_model_file);
    
    void setReadLen(int a_readlen=1000){readlen = a_readlen;}
    void preCall(string out_prefix, int min_cvg=1, int min_cvg_ctrl=1, int len_l = 1, int len_r = 1);
    void run();
    SeqFreq getSeqFreq();
    
    // setup plugins
    inline void setPileupParser(PileupParser * a_PileupParser) { ptr_PileupParser = a_PileupParser; }
    void setErrorModeler(ErrorModeler * a_ErrorModeler);
    void setPreCaller(PreCaller * a_PreCaller); 
    
    // verification
    inline void verifyPileupFile(){open_infile(fs_pileupfile, pileupfile); fs_pileupfile.close();}
    void verifyPlugin();
    
    // get signature of plugins
    inline string getSigPileupParser() {return ptr_PileupParser->getSignature();}
    inline string getSigErrorModeler() {return ptr_ErrorModeler->getSignature();}
    inline string getSigPreCaller() {return ptr_PreCaller->getSignature();}
    
    
protected:
    // input pileup file 
    string pileupfile;
    ifstream fs_pileupfile;

    // error model file
    string err_model_file;
    
    // results
    SeqFreq seqfreq;
    
    // plugins
    PileupParser * ptr_PileupParser;
    ErrorModeler * ptr_ErrorModeler;
    PreCaller * ptr_PreCaller;

    // read length
    int readlen;
    
};

#endif /* IGDA_H */

