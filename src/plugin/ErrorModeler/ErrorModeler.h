/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ErrorModeler.h
 * Author: zhixingfeng
 *
 * Created on November 12, 2015, 10:47 AM
 */

// Warning : all the error model assume all the read are mapped to the forward strand !!!

#ifndef ERRORMODELER_H
#define ERRORMODELER_H

#include "../../../include/headers.h"
#include "../PileupParser/PileupParser.h"
#include "../PileupParser/PileupParserGDA.h"

struct ErrorContextEffect {
    void clear(){ data.clear(); }
    unordered_map<string, vector<BaseFreq> > data;
    unordered_map<string, map<string, double> > err_rate_mean;
    unordered_map<string, map<string, double> > err_rate_sd;
};

class ErrorModeler {
public:
    ErrorModeler();
    ErrorModeler(const ErrorModeler& orig);
    virtual ~ErrorModeler();
    
    string getSignature() { return signature; }
    
    // set pileup file
    inline void setPileupFile(string & a_pileupfile)  { pileupfile = a_pileupfile; }
    
    // set plugins
    inline void setPileupParser(PileupParser * a_PileupParser){ ptr_PileupParser = a_PileupParser; }
    
    // calculate context effect of error rate or train the background model. 
    virtual void train() = 0;
    
    // get results
    inline ErrorContextEffect getErrorContextEffect () { return err_context; }
    
    // save and load
    void save();
    void load();
    
    //clear
    inline void clear() { err_context.clear(); }
    
protected:
    
    string signature;
    
    // pileup file
    string pileupfile;
    
    // plugins
    PileupParser * ptr_PileupParser;
    
    // context specific error rate
    ErrorContextEffect err_context;
    
};

#endif /* ERRORMODELER_H */

