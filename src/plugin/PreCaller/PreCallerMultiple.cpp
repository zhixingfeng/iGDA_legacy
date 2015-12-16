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
    
    // check format of pileupfile and 
    ptr_PileupParser->checkFormat(pileupfile);
    int n_mol = ptr_PileupParser->getMaxMolID(pileupfile);
    if (n_mol > MAX_NMOL){
        cerr << "nmol is " << n_mol << endl;
        throw runtime_error("Number of molecule is larger than MAX_NMOL. Recompile the source by adding -DMAX_NMOL with a lager number (Warning: larger RAM needed).");
    }
    
   
    
    // scanf pileupfile
    //ifstream fs_pileupfile; open_infile(fs_pileupfile, pileupfile);
    //ptr_PileupParser->setPileupFileStream(& fs_pileupfile);
    
    /*deque <Pileup> buf;
    while(true) {
        ptr_PileupParser->readLine();
        if (fs_pileupfile.eof()) break;
        
    }
    fs_pileupfile.close();
    */
}
void PreCallerMultiple::calJointProb(string jprobfile) {
    if (pileupfile == "")
        throw runtime_error("Error in PreCallerMultiple::calJointProb: pileupfile is empty.");
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in PreCallerMultiple::calJointProb: ptr_PileupParser is NULL.");
    
    // check format of pileupfile and calculate number of molecules
    ptr_PileupParser->checkFormat(pileupfile);
    int n_mol = ptr_PileupParser->getMaxMolID(pileupfile);
    if (n_mol > MAX_NMOL){
        cerr << "nmol is " << n_mol << endl;
        throw runtime_error("Number of molecule is larger than MAX_NMOL. Recompile the source by adding -DMAX_NMOL with a lager number (Warning: larger RAM needed).");
    }
    vector<BaseMap> IDmap_ins(n_mol + 1, BaseMap()); // use n_mol + 1 to be safer
    vector<BaseMap> IDmap(n_mol + 1, BaseMap());
    
    // scan pileupfile
    ofstream fs_jprobfile; open_outfile(fs_jprobfile, jprobfile);
    ifstream fs_pileupfile; open_infile(fs_pileupfile, pileupfile);
    ptr_PileupParser->setPileupFileStream(& fs_pileupfile);
    
    deque <Pileup> buf;
    while (true) {
        // read line
        ptr_PileupParser->readLine();
        if (fs_pileupfile.eof()) break;
        
        // group pileup, fill buffer and keep its size == readlen
        buf.push_back(ptr_PileupParser->getPileup());
        if (buf.size() > readlen){
            buf.pop_front();
        }
        // scan buf to calculate joint probability
        //if (buf.size() == readlen)
            //scanBuf(IDmap_ins, IDmap, buf, fs_jprobfile, false);
    }
    // scan the last buf pairwisely.
    if (buf.size() == readlen) buf.pop_front();
    
    scanBuf(IDmap_ins, IDmap, buf, fs_jprobfile, true);
    
    fs_pileupfile.close();
    fs_jprobfile.close();
    
    // sort jprobfile
    string cmd = "sort -k 1 -k 2 -k 3 -g " + jprobfile + " > " + jprobfile + ".sorted";
    cout << cmd << endl;
    system(cmd.c_str());
    cout << "done" << endl;
}

void PreCallerMultiple::scanBuf(vector<BaseMap> &IDmap_ins, vector<BaseMap>& IDmap, deque<Pileup>& buf, ofstream &fs_jprobfile, bool is_pairwise) {
    if (is_pairwise){
        for (int i=0; i<(int)buf.size()-1; i++) {
            setIDmap(IDmap_ins, IDmap, buf[i]);
            for (int j=i+1;j<(int)buf.size();j++) {
                this->count(IDmap_ins, IDmap, buf[i], buf[j], fs_jprobfile);
            }
        }
    }else {
        setIDmap(IDmap_ins, IDmap, buf[0]);
        for (int i=1; i<(int)buf.size(); i++) {
            this->count(IDmap_ins, IDmap, buf[0], buf[i], fs_jprobfile);
        }
    }    
}

void PreCallerMultiple::count(vector<BaseMap> &IDmap_ins, vector<BaseMap>& IDmap, Pileup& pu_x, Pileup& pu_y, ofstream &fs_jprobfile) {
    if (pu_x.refID != pu_y.refID || pu_x.refID == -1 || pu_x.locus == -1) return;
    if (pu_x.locus >= pu_y.locus) 
        throw runtime_error("Error in PreCallerMultiple::count(): pu_x.locus >= pu_y.locus.");
    
    if (pu_y.readID_ins.size() != pu_y.readSeq_ins.size())
        throw runtime_error("Error in PreCallerMultiple::count(): unequal size of readID_ins and readSeq_ins");
    if (pu_y.readID.size() != pu_y.readSeq.size())
        throw runtime_error("Error in PreCallerMultiple::count(): unequal size of readID and readSeq");
    
    JointProb cur_jprob;
    
    // insertion of pu_y vs insertion of pu_x
    for (int i=0; i<(int)pu_y.readID_ins.size(); ++i) {
        if (IDmap_ins[pu_y.readID_ins[i]].refID != pu_y.refID) continue;
        if (IDmap_ins[pu_y.readID_ins[i]].locus != pu_x.locus) continue;
        cur_jprob.prob_ii[NtSeq2Str(pu_y.readSeq_ins[i])][IDmap_ins[pu_y.readID_ins[i]].seq]++;
    }
    
    // match of pu_y vs insertion of pu_x
    for (int i=0; i<(int)pu_y.readID.size(); ++i) {
        if (IDmap_ins[pu_y.readID[i]].refID != pu_y.refID) continue;
        if (IDmap_ins[pu_y.readID[i]].locus != pu_x.locus) continue;
        cur_jprob.prob_mi[NtSeq2Str(pu_y.readSeq[i])][IDmap_ins[pu_y.readID[i]].seq]++;
    }
    
    // insertion of pu_y vs match of pu_x
    for (int i=0; i<(int)pu_y.readID_ins.size(); ++i) {
        if (IDmap[pu_y.readID_ins[i]].refID != pu_y.refID) continue;
        if (IDmap[pu_y.readID_ins[i]].locus != pu_x.locus) continue;
        cur_jprob.prob_im[NtSeq2Str(pu_y.readSeq_ins[i])][IDmap[pu_y.readID_ins[i]].seq]++;
    }
    
    // match of pu_y vs match of pu_x
    for (int i=0; i<(int)pu_y.readID.size(); ++i) {
        if (IDmap[pu_y.readID[i]].refID != pu_y.refID) continue;
        if (IDmap[pu_y.readID[i]].locus != pu_x.locus) continue;
        cur_jprob.prob_mm[NtSeq2Str(pu_y.readSeq[i])][IDmap[pu_y.readID[i]].seq]++;
        ++cur_jprob.cvg;
    }
    
    // normalized to get probability 
    cur_jprob.calProb();
    
    // print joint probability 
    fs_jprobfile << pu_y.refID << '\t' << pu_x.locus << '\t' << pu_y.locus << '\t' << cur_jprob.cvg << '\t';
    fs_jprobfile << cur_jprob << endl;
    
    fs_jprobfile << pu_y.refID << '\t' << pu_y.locus << '\t' << pu_x.locus << '\t' << cur_jprob.cvg << '\t';
    fs_jprobfile << cur_jprob << endl;
    
}

void PreCallerMultiple::setIDmap(vector<BaseMap> &IDmap_ins, vector<BaseMap>& IDmap, Pileup& pu) {
    if (pu.readID_ins.size() != pu.readSeq_ins.size())
        throw runtime_error("Error in PreCallerMultiple::setIDmap(): unequal size of readID_ins and readSeq_ins");
    if (pu.readID.size() != pu.readSeq.size())
        throw runtime_error("Error in PreCallerMultiple::setIDmap(): unequal size of readID and readSeq");
    
    // insertion
    for (int i=0; i<(int) pu.readID_ins.size(); ++i) {
        IDmap_ins[pu.readID_ins[i]].refID = pu.refID;
        IDmap_ins[pu.readID_ins[i]].locus = pu.locus;
        IDmap_ins[pu.readID_ins[i]].seq = NtSeq2Str(pu.readSeq_ins[i]);
    }
    
    // match and del
    for (int i=0; i<(int) pu.readID.size(); ++i) {
        IDmap[pu.readID[i]].refID = pu.refID;
        IDmap[pu.readID[i]].locus = pu.locus;
        IDmap[pu.readID[i]].seq = NtSeq2Str(pu.readSeq[i]);
    }
    
}