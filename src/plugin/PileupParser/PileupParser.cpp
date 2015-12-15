/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PileupParser.cpp
 * Author: zhixingfeng
 * 
 * Created on November 11, 2015, 4:44 PM
 */

#include "PileupParser.h"

PileupParser::PileupParser() {
    ptr_fs_pileupfile = NULL;
    signature = "PileupParser";
}

PileupParser::PileupParser(const PileupParser& orig) {
}

PileupParser::~PileupParser() {
}

void PileupParser::groupPileup() {
    if (data_Pileup.readID_ins.size() != data_Pileup.readSeq_ins.size())
        throw runtime_error("Error in PileupParser::groupPileup(): unequal size of readID_ins and readSeq_ins");
    if (data_Pileup.readID.size() != data_Pileup.readSeq.size())
        throw runtime_error("Error in PileupParser::groupPileup(): unequal size of readID and readSeq");
    
    //for (int i=0; i<(int)data_Pileup.readID_ins.size(); i++)
    //    data_Pileup.readSeq_group_ins[data_Pileup.readID_ins[i]] = data_Pileup.readSeq_ins[i];
    //for (int i=0; i<(int)data_Pileup.readID.size(); i++) 
    //    data_Pileup.readSeq_group[data_Pileup.readID[i]] = data_Pileup.readSeq[i];
    
}

map<string, double> PileupParser::getMatchProb(map<string,double>& prob, char refseq) {
    map<string, double> prob_m;
    
    // extract prob of A, C, G, T
    map<string, double>::iterator it;
    double prob_sum = 0;
    for (it=prob.begin(); it!=prob.end(); it++) {
        if (it->first!="A" && it->first!="C" && it->first!="G" && it->first!="T") 
            continue;
        
        prob_sum += it->second;
        
        if (it->first != string(1,refseq))
            prob_m[it->first] = it->second;
        
    }
    
    // normalize prob_m
    for (it=prob_m.begin(); it!=prob_m.end(); it++) {
        if (prob_sum == 0)
            it->second = NAN;
        it->second /= prob_sum;
    }
    return prob_m;
}

map<string, double> PileupParser::getDelProb(map<string,double>& prob) {
    map<string, double> prob_d;
    map<string, double>::iterator it;
    for (it=prob.begin(); it!=prob.end(); it++) {
        if (it->first == "-")
            prob_d[it->first] = it->second;
    }
    return prob_d;
}





