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
    jprob.clear();
    
    ifstream fs_pileupfile; open_infile(fs_pileupfile, pileupfile);
    ptr_PileupParser->setPileupFileStream(& fs_pileupfile);
    
    deque <Pileup> buf;
    //int nlines = 0;
    while (true) {
        // read line
        ptr_PileupParser->readLine();
        if (fs_pileupfile.eof()) break;
        
        // count number of lines
        //nlines ++;
        //if (nlines % 100==0) cout << "calculate joint probability: " << nlines << '\r';
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
    //cout << "calculate joint probability: " << nlines << endl;
    // scan the last buf pairwisely.
    if (buf.size() == readlen) buf.pop_front();
    
    scanBuf(buf, true);
    
    fs_pileupfile.close();
   
}

void PreCallerMultiple::scanBuf(deque<Pileup>& buf, bool is_pairwise) {
    if (is_pairwise){
        for (int i=0; i<(int)buf.size()-1; i++) {
            for (int j=i+1;j<(int)buf.size();j++) {
                count(buf[i], buf[j]);
            }
        }
    }else {
        for (int i=1; i<(int)buf.size(); i++) {
            count(buf[0], buf[i]);
        }
    }
}
void PreCallerMultiple::count(Pileup& pu_x, Pileup& pu_y) {
    if (pu_x.refID != pu_y.refID) return;
    if (pu_x.locus >= pu_y.locus) 
        throw runtime_error("Error in PreCallerMultiple::count(): pu_x.locus >= pu_y.locus.");
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
    
    // make the matrix symetric
    jprob[pu_x.refID][pu_y.locus][pu_x.locus] = jprob[pu_x.refID][pu_x.locus][pu_y.locus];
}

void PreCallerMultiple::saveJointProb(string outfile) {
    ofstream fs_outfile; open_outfile(fs_outfile, outfile);
    fs_outfile << this->jprob;
    fs_outfile.close();
}

void PreCallerMultiple::loadJointProb(string infile) {
    ifstream fs_infile; open_infile(fs_infile, infile);
    this->jprob.clear();
    string buf;
    while(true) {
        getline(fs_infile, buf);
        if (fs_infile.eof()) break;
        vector<string> buf_list = split(buf,'\t');
        if (buf_list.size() != 7)
            throw runtime_error("Error in PreCallerMultiple::loadJointProb(): incorrect format, buf size is not 7.");
        
        int refID = atoi(buf_list[0].c_str());
        vector<string> locus_str = split(buf_list[1],',');
        if (locus_str.size() != 2)
            throw runtime_error("Error in PreCallerMultiple::loadJointProb(): incorrect format, buf[1] size is not 2.");
        int locus_l = atoi(locus_str[0].c_str());
        int locus_r = atoi(locus_str[1].c_str());
        this->jprob[refID][locus_l][locus_r].cvg = atoi(buf_list[2].c_str());
        this->parseJointProb(this->jprob[refID][locus_l][locus_r].prob_mm, buf_list[3]);
        this->parseJointProb(this->jprob[refID][locus_l][locus_r].prob_mi, buf_list[4]);
        this->parseJointProb(this->jprob[refID][locus_l][locus_r].prob_im, buf_list[5]);
        this->parseJointProb(this->jprob[refID][locus_l][locus_r].prob_ii, buf_list[6]);
    }
    
    fs_infile.close();
}

void PreCallerMultiple::parseJointProb(map<string,map<string,double> >& prob, string& str) {
    if (str=="NA") return;
    vector<string> str_list = split(str,',');
    for (int i=0; (int)i<str_list.size(); i++) {
        vector<string> str_1 = split(str_list[i], ':');
        if (str_1.size() != 2)
            throw runtime_error("Error in PreCallerMultiple::parseJointProb(): str_1 size is not 2");
        vector<string> str_2 = split(str_1[0],'&');
        if(str_2.size()!=2)
            throw runtime_error("Error in PreCallerMultiple::parseJointProb(): str_2 size is not 2");
        prob[str_2[0]][str_2[1]] = atof(str_1[1].c_str());
    }
    
}

pair<double, double> PreCallerMultiple::calMaxCondProb(JointProb &prob, char refSeq, int min_cvg, bool is_norm){
    if (prob.cvg < min_cvg) return pair<double, double>(NAN,NAN);
    
    pair<double, double> rl(log(EPS), log(EPS));
    
    map<string, map<string, double> >::iterator it_i;
    map<string, double>::iterator it_j;
    
    // match vs match  
    for (it_i=prob.prob_mm.begin(); it_i!=prob.prob_mm.end(); ++it_i) {
        double cur_mprob_j = 0;
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); ++it_j) {
            cur_mprob_j += it_j->second;
        }
        
    }
    
}



