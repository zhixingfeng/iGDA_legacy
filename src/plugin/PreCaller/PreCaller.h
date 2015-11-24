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
    
    VarStat(): effect_size(NAN), p_value(NAN), cvg(-1), cvg_ctrl(-1), locus(-1){}
    VarStat(double effect_size, double p_value, int cvg, int cvg_ctrl, int locus):
        effect_size(effect_size), p_value(p_value), cvg(cvg), cvg_ctrl(cvg_ctrl), locus(locus){}
    double effect_size; // effect size can be defined as ratio between maximum estimated proportion / expected proportion or anything else
    double p_value; // p-value 
    int cvg; // coverage of locus. It is number of different molecules. CCS is ignored.
    int cvg_ctrl; // coverage of the control sample. Total number of molecules with the same context.
    int locus; 
    
    map<string, double> log_prob_ratio; // ratio between estimated prob and expected prob.

};



class PreCaller {
public:
    PreCaller();
    PreCaller(const PreCaller& orig);
    virtual ~PreCaller();
    
    void setPileupfile (string a_pileupfile) {pileupfile = a_pileupfile;}
    void setPileupParser (PileupParser * a_PileupParser); 
    void setErrorModeler (ErrorModeler * a_ErrorModeler); 
    
    void loadErrorModel (string err_context_file);
    virtual void callVar(int min_cvg=0) = 0;
    
    map<int, vector<VarStat> > getVar() {return varstat;} 
    string getSignature(){return signature;}
protected:
    
    string pileupfile;
    string err_context_file;
    PileupParser * ptr_PileupParser;
    ErrorModeler * ptr_ErrorModeler;
    
    //ErrorContextEffect err_context;
    map<int, vector<VarStat> > varstat;
    string signature;
};

#endif /* PRECALLER_H */

