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
    void calProb();
    
    map<string, map<string, double> > prob_mm;
    map<string, map<string, double> > prob_mi;
    map<string, map<string, double> > prob_im;
    map<string, map<string, double> > prob_ii;
    
    int cvg;
    
private:
    void freq2Prob(map<string, map<string, double> > &prob);
};

typedef vector<vector<JointProb> > JointProbVec;
typedef map<int, JointProbVec> JointProbChr;


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
    
   
    pair<double, double> calMaxCondProb(JointProb &prob, char refSeq='X', int min_cvg=1, bool is_norm=false); // first is match, second is ins
    
private:
    void scanBuf (deque <Pileup> & buf, bool is_pairwise=false);
    void count(Pileup &pu_x, Pileup & pu_y);
    void parseJointProb(map<string, map<string, double> > &prob, string & str);
    
private:
    JointProbChr jprob;
    int readlen;
    
};

#endif /* PRECALLERMULTIPLE_H */

