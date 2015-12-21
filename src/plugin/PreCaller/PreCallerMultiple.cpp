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
    freq2prob(this->prob_mm);
    freq2prob(this->prob_mi);
    freq2prob(this->prob_im);
    freq2prob(this->prob_ii);
    
    freq2prob(this->prob_mm_rev);
    freq2prob(this->prob_mi_rev);
    freq2prob(this->prob_im_rev);
    freq2prob(this->prob_ii_rev);
}
void JointProb::calCondProb() {
    jprob2cprob(this->prob_mm, &this->freq_m);
    jprob2cprob(this->prob_mi);
    jprob2cprob(this->prob_im, &this->freq_i);
    jprob2cprob(this->prob_ii);
    
    jprob2cprob(this->prob_mm_rev, &this->freq_m_rev);
    jprob2cprob(this->prob_mi_rev);
    jprob2cprob(this->prob_im_rev, &this->freq_i_rev);
    jprob2cprob(this->prob_ii_rev);
}

void JointProb::freq2prob(map<string,map<string,double> >& prob){
    map<string, map<string, double> >::iterator it_i;
    map<string, double>::iterator it_j;
    for (it_i=prob.begin(); it_i!=prob.end(); ++it_i)
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); ++it_j)
            it_j->second /= this->cvg;
}

void JointProb::jprob2cprob(map<string,map<string,double> >& prob, map<string, double> * mfreq) {
    map<string, map<string, double> >::iterator it_i;
    map<string, double>::iterator it_j;
    for (it_i=prob.begin(); it_i!=prob.end(); ++it_i) {
        double cur_sum = 0;
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); ++it_j)
            cur_sum += it_j->second;
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); ++it_j)
            it_j->second /= cur_sum;
        if (mfreq != NULL)
            (*mfreq)[it_i->first] = cur_sum; 
    }
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
    if (outprefix == "")
        throw runtime_error("Error in PreCallerMultiple::callVar: outprefix is empty.");
    if (err_context_file == "")
        throw runtime_error("Error in PreCallerMultiple::callVar: err_context_file is empty.");
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in PreCallerMultiple::callVar: ptr_PileupParser is NULL.");
    if (ptr_ErrorModeler == NULL)
        throw runtime_error("Error in PreCallerMultiple::callVar: ptr_ErrorModeler is NULL.");
    
    // calculate pairwise conditional probability ( use jprob* for function names and variables here for historical reason)
    string cprobfile = outprefix + ".cprob";
    this->calCondProb(cprobfile);
    
    // get reference genome
    ptr_ErrorModeler->setPileupFile(this->pileupfile);
    ptr_ErrorModeler->getRefGenome();
    
    // scan cprobfile
    ifstream fs_cprobfile; open_infile(fs_cprobfile, cprobfile+".sorted");
    ofstream fs_ratiofile; open_outfile(fs_ratiofile, cprobfile+".sorted.ratio");
    int refID, locus_l, locus_r, mcvg;
    string refSeq;
    
    while(true) {
        JointProb cur_cprob;
        this->readCondProb(fs_cprobfile, refID, locus_l, locus_r, refSeq, mcvg, cur_cprob);
        if (fs_cprobfile.eof()) break;
        
        pair<string, string> cur_context = ptr_ErrorModeler->getLocalContext(refID, locus_l, len_l, len_r);
        int cvg_ctrl = ptr_ErrorModeler->searchErrorContextEffectCvg(refID, locus_l, len_l, len_r);
        map<string, double> prob_ctrl = ptr_ErrorModeler->searchErrorContextEffectMean(refID, locus_l, len_l, len_r);
        map<string, double> prob_ctrl_ins = ptr_ErrorModeler->searchErrorContextEffectMeanIns(refID, locus_l, len_l, len_r);
        
        double max_prob_mm = this->calProbRatio(cur_cprob.prob_mm, prob_ctrl, refSeq);
        double max_prob_im = this->calProbRatio(cur_cprob.prob_im, prob_ctrl, refSeq);
        double max_prob_mi = this->calProbRatio(cur_cprob.prob_mi, prob_ctrl_ins, refSeq);
        double max_prob_ii = this->calProbRatio(cur_cprob.prob_ii, prob_ctrl_ins, refSeq);
        
        fs_ratiofile << refID << '\t' << locus_l << '\t' << locus_r << '\t' << cur_cprob.cvg << '\t' << refSeq << '\t' << mcvg << '\t';
        fs_ratiofile << max_prob_mm << '\t' << max_prob_im << '\t' << max_prob_mi << '\t' << max_prob_ii << '\t';
        fs_ratiofile << cur_cprob << '\t' << cur_context << '\t';
        if (prob_ctrl.size() > 0)
            fs_ratiofile << prob_ctrl << '\t';
        else
            fs_ratiofile << "NA" << '\t';
        if (prob_ctrl_ins.size() > 0)
            fs_ratiofile << prob_ctrl_ins << endl;
        else
            fs_ratiofile << "NA" << endl;
        
        
    }
    
    fs_cprobfile.close();
    fs_ratiofile.close();
   
}
void PreCallerMultiple::calCondProb(string cprobfile) {
    if (pileupfile == "")
        throw runtime_error("Error in PreCallerMultiple::calCondProb: pileupfile is empty.");
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in PreCallerMultiple::calCondProb: ptr_PileupParser is NULL.");
    
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
    ofstream fs_cprobfile; open_outfile(fs_cprobfile, cprobfile);
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
        if (buf.size() == readlen)
            scanBuf(IDmap_ins, IDmap, buf, fs_cprobfile, false);
    }
    // scan the last buf pairwisely.
    if (buf.size() == readlen) buf.pop_front();
    
    scanBuf(IDmap_ins, IDmap, buf, fs_cprobfile, true);
    
    fs_pileupfile.close();
    fs_cprobfile.close();
    
    // sort cprobfile
    string cmd = "sort -k 1 -k 2 -k 3 -g " + cprobfile + " > " + cprobfile + ".sorted";
    cout << cmd << endl;
    system(cmd.c_str());
    cout << "done" << endl;
}

void PreCallerMultiple::scanBuf(vector<BaseMap> &IDmap_ins, vector<BaseMap>& IDmap, deque<Pileup>& buf, ofstream &fs_cprobfile, bool is_pairwise) {
    if (is_pairwise){
        for (int i=0; i<(int)buf.size()-1; i++) {
            setIDmap(IDmap_ins, IDmap, buf[i]);
            for (int j=i+1;j<(int)buf.size();j++) {
                this->count(IDmap_ins, IDmap, buf[i], buf[j], fs_cprobfile);
            }
        }
    }else {
        setIDmap(IDmap_ins, IDmap, buf[0]);
        for (int i=1; i<(int)buf.size(); i++) {
            this->count(IDmap_ins, IDmap, buf[0], buf[i], fs_cprobfile);
        }
    }    
}

void PreCallerMultiple::count(vector<BaseMap> &IDmap_ins, vector<BaseMap>& IDmap, Pileup& pu_x, Pileup& pu_y, ofstream &fs_cprobfile) {
    if (pu_x.refID != pu_y.refID || pu_x.refID == -1 || pu_x.locus == -1) return;
    if (pu_x.locus >= pu_y.locus) 
        throw runtime_error("Error in PreCallerMultiple::count(): pu_x.locus >= pu_y.locus.");
    
    if (pu_y.readID_ins.size() != pu_y.readSeq_ins.size())
        throw runtime_error("Error in PreCallerMultiple::count(): unequal size of readID_ins and readSeq_ins");
    if (pu_y.readID.size() != pu_y.readSeq.size())
        throw runtime_error("Error in PreCallerMultiple::count(): unequal size of readID and readSeq");
    
    JointProb cur_cprob;
    
    // insertion of pu_y vs insertion of pu_x
    for (int i=0; i<(int)pu_y.readID_ins.size(); ++i) {
        if (IDmap_ins[pu_y.readID_ins[i]].refID != pu_y.refID) continue;
        if (IDmap_ins[pu_y.readID_ins[i]].locus != pu_x.locus) continue;
        cur_cprob.prob_ii[NtSeq2Str(pu_y.readSeq_ins[i])][IDmap_ins[pu_y.readID_ins[i]].seq]++;
        cur_cprob.prob_ii_rev[IDmap_ins[pu_y.readID_ins[i]].seq][NtSeq2Str(pu_y.readSeq_ins[i])]++;
    }
    
    // match of pu_y vs insertion of pu_x
    for (int i=0; i<(int)pu_y.readID.size(); ++i) {
        if (IDmap_ins[pu_y.readID[i]].refID != pu_y.refID) continue;
        if (IDmap_ins[pu_y.readID[i]].locus != pu_x.locus) continue;
        cur_cprob.prob_mi[NtSeq2Str(pu_y.readSeq[i])][IDmap_ins[pu_y.readID[i]].seq]++;
        cur_cprob.prob_mi_rev[IDmap_ins[pu_y.readID[i]].seq][NtSeq2Str(pu_y.readSeq[i])]++;
    }
    
    // insertion of pu_y vs match of pu_x
    for (int i=0; i<(int)pu_y.readID_ins.size(); ++i) {
        if (IDmap[pu_y.readID_ins[i]].refID != pu_y.refID) continue;
        if (IDmap[pu_y.readID_ins[i]].locus != pu_x.locus) continue;
        cur_cprob.prob_im[NtSeq2Str(pu_y.readSeq_ins[i])][IDmap[pu_y.readID_ins[i]].seq]++;
        cur_cprob.prob_im_rev[IDmap[pu_y.readID_ins[i]].seq][NtSeq2Str(pu_y.readSeq_ins[i])]++;
    }
    
    // match of pu_y vs match of pu_x
    for (int i=0; i<(int)pu_y.readID.size(); ++i) {
        if (IDmap[pu_y.readID[i]].refID != pu_y.refID) continue;
        if (IDmap[pu_y.readID[i]].locus != pu_x.locus) continue;
        cur_cprob.prob_mm[NtSeq2Str(pu_y.readSeq[i])][IDmap[pu_y.readID[i]].seq]++;
        cur_cprob.prob_mm_rev[IDmap[pu_y.readID[i]].seq][NtSeq2Str(pu_y.readSeq[i])]++;
        ++cur_cprob.cvg;
    }
    
    // normalized to get probability 
    //cur_cprob.calProb();
    cur_cprob.calCondProb();
            
    // print joint probability 
    fs_cprobfile << pu_x.refID << '\t' << pu_x.locus << '\t' << pu_y.locus << '\t' << cur_cprob.cvg << '\t';
    fs_cprobfile << pu_x.refSeq << '\t' << pu_x.cvg << '\t';
    fs_cprobfile << cur_cprob << '\t';
    if (cur_cprob.freq_m.size() >0)
        fs_cprobfile << cur_cprob.freq_m << '\t';
    else
        fs_cprobfile << "NA" << '\t';
    if (cur_cprob.freq_i.size() >0)
        fs_cprobfile << cur_cprob.freq_i << endl;
    else
        fs_cprobfile << "NA" << endl;
    
                
    fs_cprobfile << pu_y.refID << '\t' << pu_y.locus << '\t' << pu_x.locus << '\t' << cur_cprob.cvg << '\t';
    fs_cprobfile << pu_y.refSeq << '\t' << pu_y.cvg << '\t';
    if (cur_cprob.prob_mm_rev.size() > 0)
        fs_cprobfile << cur_cprob.prob_mm_rev << '\t';
    else
        fs_cprobfile << "NA" << '\t';
    if (cur_cprob.prob_mi_rev.size() > 0)
        fs_cprobfile << cur_cprob.prob_mi_rev << '\t';
    else 
        fs_cprobfile << "NA" << '\t';
    if (cur_cprob.prob_im_rev.size() > 0)
        fs_cprobfile << cur_cprob.prob_im_rev << '\t';
    else
        fs_cprobfile << "NA" << '\t';
    if (cur_cprob.prob_ii_rev.size() > 0)
        fs_cprobfile << cur_cprob.prob_ii_rev << '\t';
    else
        fs_cprobfile << "NA" << '\t';
    
    if (cur_cprob.freq_m_rev.size() >0)
        fs_cprobfile << cur_cprob.freq_m_rev << '\t';
    else
        fs_cprobfile << "NA" << '\t';
    if (cur_cprob.freq_i_rev.size() >0)
        fs_cprobfile << cur_cprob.freq_i_rev << endl;
    else
        fs_cprobfile << "NA" << endl;
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

void PreCallerMultiple::readCondProb(ifstream& fs_cprobfile, int& refID, int& locus_l, int& locus_r, string &refSeq, int &mcvg, JointProb& cur_cprob) {
    string buf;
    getline(fs_cprobfile, buf) ;
    if (fs_cprobfile.eof()) return;
    
    vector<string> buf_list = split(buf,'\t');
    if (buf_list.size() != 12)
            throw runtime_error("Error in PreCallerMultiple::readCondProb(): incorrect format, buf size is not 12.");
        
    refID = atoi(buf_list[0].c_str());
    locus_l = atoi(buf_list[1].c_str());
    locus_r = atoi(buf_list[2].c_str());
    cur_cprob.cvg = atoi(buf_list[3].c_str());
    refSeq = buf_list[4];
    mcvg = atoi(buf_list[5].c_str());
    
    this->parseCondProb(cur_cprob.prob_mm, buf_list[6]);
    this->parseCondProb(cur_cprob.prob_mi, buf_list[7]);
    this->parseCondProb(cur_cprob.prob_im, buf_list[8]);
    this->parseCondProb(cur_cprob.prob_ii, buf_list[9]);
    
    this->parseMargProb(cur_cprob.freq_m, buf_list[10]);
    this->parseMargProb(cur_cprob.freq_i, buf_list[11]);
}

void PreCallerMultiple::parseCondProb(map<string,map<string,double> >& prob, string& str) {
    if (str=="NA") return;
    vector<string> str_list = split(str,',');
    for (int i=0; (int)i<str_list.size(); i++) {
        vector<string> str_1 = split(str_list[i], ':');
        if (str_1.size() != 2)
            throw runtime_error("Error in PreCallerMultiple::parseCondProb(): str_1 size is not 2");
        vector<string> str_2 = split(str_1[0],'&');
        if(str_2.size()!=2)
            throw runtime_error("Error in PreCallerMultiple::parseCondProb(): str_2 size is not 2");
        prob[str_2[0]][str_2[1]] = atof(str_1[1].c_str());
    }
}

void PreCallerMultiple::parseMargProb(map<string,double>& prob, string& str) {
    if (str == "NA") return;
    vector<string> str_list = split(str, ',');
    for (int i=0; i<(int)str_list.size(); i++) {
        vector<string> str_1 = split(str_list[i], ':');
        if (str_1.size() != 2)
            throw runtime_error("Error in PreCallerMultiple::parseMargProb(): str_1 size is not 2");
        prob[str_1[0]] = atof(str_1[1].c_str());
    }
}

double PreCallerMultiple::calProbRatio(map<string,map<string,double> >& prob, map<string,double> & prob_ctrl, string &refSeq) {
    double max_ratio = NAN;
    map<string,map<string,double> >::iterator it_i;
    map<string,double>::iterator it_j;
    map<string,double>::iterator it_ctrl;
    
    for (it_i=prob.begin(); it_i!=prob.end(); ++it_i) {
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); ++it_j) {
            it_ctrl = prob_ctrl.find(it_j->first);
            if (it_ctrl == prob_ctrl.end()) {
                it_j->second = NAN; continue;
            }
            if (it_ctrl->second < EPS) {
                it_j->second = NAN; continue;
            }
            it_j->second /= it_ctrl->second;
            if (std::isnan(max_ratio) || (it_j->second > max_ratio && it_j->first!=refSeq)) 
                max_ratio = it_j->second;
        }
    }
    
    return max_ratio;
}
