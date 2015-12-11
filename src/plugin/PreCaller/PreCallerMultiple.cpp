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
    
    
}

void PreCallerMultiple::calJointProb() {
    if (pileupfile == "")
        throw runtime_error("Error in PreCallerMultiple::calJointProb: pileupfile is empty.");
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in PreCallerMultiple::calJointProb: ptr_PileupParser is NULL.");
    ifstream fs_pileupfile; open_infile(fs_pileupfile, pileupfile);
    ptr_PileupParser->setPileupFileStream(& fs_pileupfile);
    
    deque <Pileup> buf;
    while (true) {
        // read line
        ptr_PileupParser->readLine();
        if (fs_pileupfile.eof()) break;
        
        // group pileup, fill buffer and keep its size == readlen
        ptr_PileupParser->groupPileup();
        buf.push_back(ptr_PileupParser->getPileup());
        if (buf.size() > readlen){
            buf.pop_front();
        }
        // scan buf to calculate joint probability
        if (buf.size() == readlen)
            scanBuf(buf, false);
    }
    
    // scan the last buf pairwisely.
    scanBuf(buf, true);
    
    
    fs_pileupfile.close();
    
    
}

void PreCallerMultiple::scanBuf(deque<Pileup>& buf, bool is_pairwise) {
    if (is_pairwise){
        for (int i=0;i<(int)buf.size()-1;i++) {
            for (int j=i+1;j<(int)buf.size();j++) {
                count(buf[i], buf[j]);
            }
        }
    }else {
        
    }
}
void PreCallerMultiple::count(Pileup& pu_x, Pileup& pu_y) {
    if (pu_x.refID != pu_y.refID) return;
    if (pu_x.locus == pu_y.locus) 
        throw runtime_error("Error in PreCallerMultiple::count(): duplicated locus.");
    map<int, NtSeq>::iterator it;
    
    // pu_x is match 
    for (int i=0; i<(int)pu_x.readID.size(); i++){
        // match vs match
        it = pu_y.readSeq_group.find(pu_x.readID[i]);
        if (it != pu_y.readSeq_group.end()) {
            jprob[pu_x.refID][pu_x.locus][pu_y.locus].prob_mm[NtSeq2Str(pu_x.readSeq[i])][NtSeq2Str(it->second)] ++;
            jprob[pu_x.refID][pu_x.locus][pu_y.locus].cvg ++;
        }
        // match vs insertion
        it = pu_y.readSeq_group_ins.find(pu_x.readID[i]);
        if (it != pu_y.readSeq_group_ins.end()) 
            jprob[pu_x.refID][pu_x.locus][pu_y.locus].prob_mi[NtSeq2Str(pu_x.readSeq[i])][NtSeq2Str(it->second)] ++;
        
    }
    
    
    // pu_x is insertion 
    for (int i=0; i<(int)pu_x.readID_ins.size(); i++){
        // insertion vs match
        it = pu_y.readSeq_group.find(pu_x.readID_ins[i]);
        if (it != pu_y.readSeq_group.end()) 
            jprob[pu_x.refID][pu_x.locus][pu_y.locus].prob_im[NtSeq2Str(pu_x.readSeq_ins[i])][NtSeq2Str(it->second)] ++;

        // insertion vs insertion
        it = pu_y.readSeq_group_ins.find(pu_x.readID_ins[i]);
        if (it != pu_y.readSeq_group_ins.end())
            jprob[pu_x.refID][pu_x.locus][pu_y.locus].prob_ii[NtSeq2Str(pu_x.readSeq_ins[i])][NtSeq2Str(it->second)] ++;
    }
    
    jprob[pu_x.refID][pu_x.locus][pu_y.locus].calProb();
}

void PreCallerMultiple::saveJointProb(string outfile) {
    ofstream fs_outfile; open_outfile(fs_outfile, outfile);
    
    fs_outfile.close();
}