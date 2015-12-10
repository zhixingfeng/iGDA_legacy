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

struct JointProb {
    JointProb (): cvg(0), prob_del(0) {}
    map<string, map<string, double> > prob;
    map<string, map<string, double> > prob_ins;
    double prob_del;
    
    int cvg;
};

typedef map<int, map<int, JointProb> > JointProbVec;
typedef map<int, map<int, map<int, JointProb> > > JointProbChr;
        
class PreCallerMultiple : public PreCaller {
public:
    PreCallerMultiple();
    PreCallerMultiple(const PreCallerMultiple& orig);
    virtual ~PreCallerMultiple();
    
    void setReadLen(int a_readlen) { readlen = a_readlen; }
    void callVar(int min_cvg=1, int min_cvg_ctrl=1, int len_l = 1, int len_r = 1);
   
    void calJointProb();
    JointProbChr getJointProb() {return jprob;}
    void saveJointProb (string outprefix);
    void loadJointProb (string inprefix);

private:
    JointProbChr jprob;
    
    int readlen;
    
};

#endif /* PRECALLERMULTIPLE_H */

