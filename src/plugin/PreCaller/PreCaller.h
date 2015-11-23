/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreCaller.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 4:54 PM
 */

#ifndef PRECALLER_H
#define PRECALLER_H
#include "../../../include/headers.h"
#include "../PileupParser/PileupParser.h"
#include "../PileupParser/PileupParserGDA.h"
#include "../ErrorModeler/ErrorModeler.h"
#include "../ErrorModeler/ErrorModelerHomo.h"

struct VarStat {
    double effect_size; // effect size can be defined as ratio between estimated proportion / expected proportion or anything else
    int cvg; // coverage of locus. It is number of different molecules. CCS is ignored.
    int cvg_ctrl; // coverage of the control sample. Total number of molecules with the same context.
};



class PreCaller {
public:
    PreCaller();
    PreCaller(const PreCaller& orig);
    virtual ~PreCaller();
    
    void setPileupfile (string a_pileupfile) {pileupfile = a_pileupfile;}
    void setPileupParser (PileupParser * a_PileupParser); 
    void setErrorModeler (ErrorModeler * a_ErrorModeler); 
    
    virtual void callVar() = 0;
    map<int, vector<VarStat> > getVar() {return varstat;} 
    string getSignature(){return signature;}
protected:
    
    string pileupfile;
    PileupParser * ptr_PileupParser;
    ErrorModeler * ptr_ErrorModeler;
    
    map<int, vector<VarStat> > varstat;
    string signature;
};

#endif /* PRECALLER_H */

