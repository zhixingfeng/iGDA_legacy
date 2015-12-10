/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreCallerMultiple.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 5:32 PM
 */

#ifndef PRECALLERMULTIPLE_H
#define PRECALLERMULTIPLE_H

#include "PreCaller.h" 

// define data structure 
struct JointProb {
    JointProb (): cvg(0) {}
    map<string, map<string, double> > freq_mm;
    map<string, map<string, double> > freq_mi;
    map<string, map<string, double> > freq_im;
    map<string, map<string, double> > freq_ii;
    
    map<string, map<string, double> > prob_mm;
    map<string, map<string, double> > prob_mi;
    map<string, map<string, double> > prob_im;
    map<string, map<string, double> > prob_ii;
    
    int cvg;
};

typedef map<int, map<int, JointProb> > JointProbVec;
typedef map<int, map<int, map<int, JointProb> > > JointProbChr;

inline ostream & operator << (ostream & os,  JointProbVec & jprobvec) {
    JointProbVec::iterator it_i;
    map<int, JointProb>::iterator it_j;
    for (it_i=jprobvec.begin(); it_i!=jprobvec.end(); ++it_i){
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); ++it_j){
            os << it_i->first << ',' << it_j->first << '\t';
            os << it_j->second.freq_mm << endl;
        }
    }
    return os;
}

inline ostream & operator << (ostream & os,  JointProbChr & jprobchr) {
    JointProbChr::iterator it;
    for (it=jprobchr.begin(); it!=jprobchr.end(); ++it){
        os << it->first << '\t' << it->second;
    }
    return os;
}


// define class
class PreCallerMultiple : public PreCaller {
public:
    PreCallerMultiple();
    PreCallerMultiple(const PreCallerMultiple& orig);
    virtual ~PreCallerMultiple();
    
    void setReadLen(int a_readlen) { readlen = a_readlen; }
    void callVar(int min_cvg=1, int min_cvg_ctrl=1, int len_l = 1, int len_r = 1);
   
    void calJointProb();
    JointProbChr getJointProb() {return jprob;}
    void saveJointProb (string outfile);
    void loadJointProb (string infile);

    void scanBuf (deque <Pileup> & buf, bool is_pairwise=false);
    
private:
    void count(Pileup &pu_x, Pileup & pu_y);
    
private:
    JointProbChr jprob;
    
    int readlen;
    
};

#endif /* PRECALLERMULTIPLE_H */

