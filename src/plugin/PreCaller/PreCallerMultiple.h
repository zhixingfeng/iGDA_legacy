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

inline ostream & operator << (ostream & os,  JointProbVec & jprobvec) {
    JointProbVec::iterator it_i;
    map<int, JointProb>::iterator it_j;
    for (it_i=jprobvec.begin(); it_i!=jprobvec.end(); ++it_i){
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); ++it_j){
            os << it_i->first << ',' << it_j->first << '\t' << it_j->second.cvg << '\t';
            if (it_j->second.prob_mm.size() > 0)
                os << it_j->second.prob_mm << '\t';
            else
                os << "NA" << '\t';
            if (it_j->second.prob_mi.size() > 0)
                os << it_j->second.prob_mi << '\t';
            else 
                os << "NA" << '\t';
            if (it_j->second.prob_im.size() > 0)
                os << it_j->second.prob_im << '\t';
            else
                os << "NA" << '\t';
            if (it_j->second.prob_ii.size() > 0)
                os << it_j->second.prob_ii << endl;
            else
                os << "NA" << endl;
        }
    }
    return os;
}

inline ostream & operator << (ostream & os,  JointProbChr & jprobchr) {
    JointProbChr::iterator it_k;
    JointProbVec::iterator it_i;
    map<int, JointProb>::iterator it_j;
    for (it_k=jprobchr.begin(); it_k!=jprobchr.end(); ++it_k){
        for (it_i=it_k->second.begin(); it_i!=it_k->second.end(); ++it_i){
            for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); ++it_j){
                os << it_k->first << '\t' << it_i->first << ',' << it_j->first << '\t';
                os << it_j->second.cvg << '\t';
                
                if (it_j->second.prob_mm.size() > 0)
                    os << it_j->second.prob_mm << '\t';
                else
                    os << "NA" << '\t';
                if (it_j->second.prob_mi.size() > 0)
                    os << it_j->second.prob_mi << '\t';
                else 
                    os << "NA" << '\t';
                if (it_j->second.prob_im.size() > 0)
                    os << it_j->second.prob_im << '\t';
                else
                    os << "NA" << '\t';
                if (it_j->second.prob_ii.size() > 0)
                    os << it_j->second.prob_ii << endl;
                else
                    os << "NA" << endl;
            }
        }
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

