/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ErrorModeler.cpp
 * Author: zhixingfeng
 * 
 * Created on November 12, 2015, 10:47 AM
 */

#include "ErrorModeler.h"

ErrorModeler::ErrorModeler() {
    signature = "ErrorModeler";
    pileupfile = "";
    ptr_PileupParser = NULL;
    
}

ErrorModeler::ErrorModeler(const ErrorModeler& orig) {
    
}

ErrorModeler::~ErrorModeler() {
}

void ErrorModeler::save(string err_context_file) {
    unordered_map<string, unordered_map<string, vector<BaseFreq> > >::iterator it_i;
    unordered_map<string, vector<BaseFreq> >::iterator it_j;
    ofstream fs_err_context_file = open_outfile(err_context_file);
    for (it_i=err_context.data.begin(); it_i!=err_context.data.end(); it_i++) {
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); it_j++) {
            fs_err_context_file << it_i->first << ',' << it_j->first << '\t';
            for (int i=0; i<(int) it_j->second.size(); i++) {
                fs_err_context_file << it_j->second[i].refID << '@' << it_j->second[i].locus << '#' << it_j->second[i].cvg_ins << ',' << it_j->second[i].cvg << '|' <<
                        it_j->second[i].prob_ins << '&' << it_j->second[i].prob << '\t';
            }
            fs_err_context_file << endl;
        }
        
    }
    
    fs_err_context_file.close();
}