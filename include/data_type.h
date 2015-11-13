/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   data_type.h
 * Author: zhixingfeng
 *
 * Created on November 12, 2015, 12:07 PM
 */


// this file define the data type for modeling sequencing data
#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include "stl.h"
#include <vector>


struct NtBase {
    NtBase (char base) : base(base), score_sub(0), score_del(0), score_ins(0) {}
    
    NtBase () : base('X'), score_sub(0), score_del(0), score_ins(0) {}
    char base;
    char score_sub;
    char score_del;
    char score_ins;
};

typedef vector<NtBase> NtSeq;

struct Pileup {
    
    Pileup() : refID(-1), locus(-1), refSeq ('X'), cvg(-1), cvg_ins(-1) {}
    Pileup(int refID, int locus, char refSeq, int cvg, int cvg_ins) : 
        refID(refID), locus(locus), refSeq (refSeq), cvg(cvg), cvg_ins(cvg_ins) {}
    
    int refID;
    int locus;
    char refSeq;
    int cvg;
    int cvg_ins;
    
    vector<NtSeq> readSeq;
    vector<int> readID;
    unordered_map<int, NtSeq> readSeq_group;
    
    vector<NtSeq> readSeq_ins;
    vector<int> readID_ins;
    unordered_map<int, NtSeq> readSeq_group_ins;
    
};


struct BaseFreq {
    
    BaseFreq(): refID(-1), locus(-1), refSeq ('X'), cvg(-1), cvg_ins(-1){}
    BaseFreq(int refID, int locus, char refSeq, int cvg, int cvg_ins) : 
        refID(refID), locus(locus), refSeq (refSeq), cvg(cvg), cvg_ins(cvg_ins) {}
    BaseFreq(const Pileup & obj_Pileup):  
        refID(obj_Pileup.refID), locus(obj_Pileup.locus), refSeq (obj_Pileup.refSeq), cvg(obj_Pileup.cvg), cvg_ins(obj_Pileup.cvg_ins) {}
    
    int refID;
    int locus;
    char refSeq;
    int cvg;
    int cvg_ins;
    
    unordered_map<string, int> freq;
    unordered_map<string, double> prob;
    
    unordered_map<string, int> freq_ins;
    unordered_map<string, double> prob_ins;
    
    
};


// converstion between string and nucleotide sequence.
inline NtSeq str2NtSeq (string seq) {
    NtSeq ntseq;
    for (int i=0; i<(int)seq.size(); i++) {
        ntseq.push_back(NtBase(seq[i]));
    }
    return ntseq;
}

inline string NtSeq2Str (NtSeq ntseq) {
    string seq;
    for (int i=0; i<(int)ntseq.size(); i++) {
        seq.push_back(ntseq[i].base);
    }
    return seq;
}

inline ostream & operator << (ostream & os, const Pileup & obj_Pileup) {
    // print insertion
    os << obj_Pileup.refID << "\t_" << obj_Pileup.locus << '\t' << obj_Pileup.refSeq << '\t' << obj_Pileup.cvg_ins << '\t';
    for (int i=0; i<(int)obj_Pileup.readSeq_ins.size(); i++) 
        os << NtSeq2Str(obj_Pileup.readSeq_ins[i]) << ',';
    os << '\t';
    for (int i=0; i<(int)obj_Pileup.readID_ins.size(); i++) 
        os << obj_Pileup.readID_ins[i] << ',';
    os << endl;
    // print match
    os << obj_Pileup.refID << "\t" << obj_Pileup.locus << '\t' << obj_Pileup.refSeq << '\t' << obj_Pileup.cvg << '\t';
    for (int i=0; i<(int)obj_Pileup.readSeq.size(); i++) 
        os << NtSeq2Str(obj_Pileup.readSeq[i]) << ',';
    os << '\t';
    for (int i=0; i<(int)obj_Pileup.readID.size(); i++) 
        os << obj_Pileup.readID[i] << ',';
    os << endl;
    return os;
}

inline bool operator == (const Pileup & obj_Pileup_l, const Pileup & obj_Pileup_r) {
    if (obj_Pileup_l.refID != obj_Pileup_r.refID) return false;
    if (obj_Pileup_l.locus != obj_Pileup_r.locus) return false;
    if (obj_Pileup_l.refSeq != obj_Pileup_r.refSeq) return false;
    if (obj_Pileup_l.cvg_ins != obj_Pileup_r.cvg_ins) return false;
    if (obj_Pileup_l.cvg != obj_Pileup_r.cvg) return false;
    
    if (obj_Pileup_l.readSeq_ins.size() != obj_Pileup_r.readSeq_ins.size()) return false;
    if (obj_Pileup_l.readSeq.size() != obj_Pileup_r.readSeq.size()) return false;
    if (obj_Pileup_l.readID_ins.size() != obj_Pileup_r.readID_ins.size()) return false;
    if (obj_Pileup_l.readID.size() != obj_Pileup_r.readID.size()) return false;
    if (obj_Pileup_l.readSeq_group_ins.size() != obj_Pileup_r.readSeq_group_ins.size()) return false;
    if (obj_Pileup_l.readSeq_group.size() != obj_Pileup_r.readSeq_group.size()) return false;
    
    for (int i=0; i<(int)obj_Pileup_l.readSeq_ins.size(); i++) 
        if (NtSeq2Str(obj_Pileup_l.readSeq_ins[i]) != NtSeq2Str(obj_Pileup_r.readSeq_ins[i])) return false;
    for (int i=0; i<(int)obj_Pileup_l.readSeq.size(); i++) 
        if (NtSeq2Str(obj_Pileup_l.readSeq[i]) != NtSeq2Str(obj_Pileup_r.readSeq[i])) return false;
    
    for (int i=0; i<(int)obj_Pileup_l.readID_ins.size(); i++) 
        if (obj_Pileup_l.readID_ins[i] != obj_Pileup_r.readID_ins[i]) return false;
    for (int i=0; i<(int)obj_Pileup_l.readID.size(); i++) 
        if (obj_Pileup_l.readID[i] != obj_Pileup_r.readID[i]) return false;
    
    // readSeq_group_ins and readSeq_group are NOT compared !!!
    return true;
}
#endif /* DATA_TYPE_H */

