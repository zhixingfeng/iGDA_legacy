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

typedef map<int, map<int, JointProb> > JointProbVec;
typedef map<int, JointProbVec> JointProbChr;


#endif /* PRECALLERMULTIPLE_H */

