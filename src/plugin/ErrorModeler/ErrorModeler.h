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
    void clear(){ 
        data.clear(); 
        err_rate_mean.clear(); err_rate_sd.clear();
        err_rate_mean_ins.clear(); err_rate_sd_ins.clear();
    }
    
    unordered_map<string, unordered_map<string, vector<BaseFreq> > > data;
    
    unordered_map<string, unordered_map<string, unordered_map<string, double> > >  err_rate_mean;
    unordered_map<string, unordered_map<string, unordered_map<string, double> > > err_rate_sd;
    
    unordered_map<string, unordered_map<string, unordered_map<string, double> > > err_rate_mean_ins;
    unordered_map<string, unordered_map<string, unordered_map<string, double> > > err_rate_sd_ins;
    
    unordered_map<string, unordered_map<string, int> > total_cvg;
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
    virtual void train(int left, int right) = 0;
    void calErrorRateStat();
    
    // get results
    inline ErrorContextEffect getErrorContextEffect () { return err_context; }
    
    // save and load. Warning: load will not erase existing err_context !!!!
    void save(string err_context_file);
    void load(string err_context_file);
    
    // save mean error rate 
    void save_mean_err(string mean_err_file);
    
    //clear
    inline void clear() { err_context.clear(); }
       
protected:
    BaseFreq parseLocus(string & buf);
    
protected:
    
    string signature;
    
    // pileup file
    string pileupfile;
    
    // plugins
    PileupParser * ptr_PileupParser;
    
    // context specific error rate
    ErrorContextEffect err_context;
    
    // reference genome derived from pileupfile
    RefGenome refgenome;
};

#endif /* ERRORMODELER_H */

