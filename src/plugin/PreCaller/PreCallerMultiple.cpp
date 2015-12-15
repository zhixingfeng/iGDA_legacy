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
void JointProb::calProb() {
    freq2Prob(this->prob_mm);
    freq2Prob(this->prob_mi);
    freq2Prob(this->prob_im);
    freq2Prob(this->prob_ii);
}

void JointProb::freq2Prob(map<string,map<string,double> >& prob){
    map<string, map<string, double> >::iterator it_i;
    map<string, double>::iterator it_j;
    for (it_i=prob.begin(); it_i!=prob.end(); ++it_i)
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); ++it_j)
            it_j->second /= this->cvg;
}

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
    
    // check format of pileupfile and 
    ptr_PileupParser->checkFormat(pileupfile);
    int n_mol = ptr_PileupParser->getMaxMolID(pileupfile);
    if (n_mol > MAX_NMOL){
        cerr << "nmol is " << n_mol << endl;
        throw runtime_error("Number of molecule is larger than MAX_NMOL. Recompile the source by adding -DMAX_NMOL with a lager number (Warning: larger RAM needed).");
    }
    
    // initialize reference vector of ID to seq map
    vector<string> IDmap(n_mol, "");
    
    // 
    
}