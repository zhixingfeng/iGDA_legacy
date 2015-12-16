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
struct BaseMap {
    BaseMap(): refID(-1), locus(-1), seq(""){}
    BaseMap(int refID, int locus, string seq): refID(refID), locus(locus), seq(seq){}
    int refID;
    int locus;
    string seq;
};
        
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

inline ostream & operator << (ostream & os,  JointProb & cur_jprob) {
    if (cur_jprob.prob_mm.size() > 0)
        os << cur_jprob.prob_mm << '\t';
    else
        os << "NA" << '\t';
    
    if (cur_jprob.prob_mi.size() > 0)
        os << cur_jprob.prob_mi << '\t';
    else 
        os << "NA" << '\t';
    
    if (cur_jprob.prob_im.size() > 0)
        os << cur_jprob.prob_im << '\t';
    else
        os << "NA" << '\t';
    
    if (cur_jprob.prob_ii.size() > 0)
        os << cur_jprob.prob_ii;
    else
        os << "NA";
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
   
    void calJointProb(string jprobfile);
    void saveJointProb (string outfile);
    void loadJointProb (string infile);
    
   
    pair<double, double> calMaxCondProb(JointProb &prob, char refSeq='X', int min_cvg=1, bool is_norm=false); // first is match, second is ins
    
private:
    void scanBuf (vector<BaseMap> &IDmap_ins, vector<BaseMap> &IDmap, deque <Pileup> & buf, ofstream &fs_jprobfile, bool is_pairwise=false);
    void count(vector<BaseMap> &IDmap_ins, vector<BaseMap> &IDmap, Pileup& pu_x, Pileup & pu_y, ofstream &fs_jprobfile);
    void setIDmap(vector<BaseMap> &IDmap_ins,vector<BaseMap> &IDmap, Pileup & pu);
    void parseJointProb(map<string, map<string, double> > &prob, string & str);
    
private:
    
    int readlen;
    
};

#endif /* PRECALLERMULTIPLE_H */

