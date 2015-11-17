/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ErrorModeler.cpp
 * Author: zhixingfeng
 * 
 * Created on November 12, 2015, 10:47 AM
 */

#include "ErrorModeler.h"

ErrorModeler::ErrorModeler() {
    signature = "ErrorModeler";
    pileupfile = "";
    ptr_PileupParser = NULL;
    
}

ErrorModeler::ErrorModeler(const ErrorModeler& orig) {
    
}

ErrorModeler::~ErrorModeler() {
}

void ErrorModeler::save(string err_context_file) {
    unordered_map<string, unordered_map<string, vector<BaseFreq> > >::iterator it_i;
    unordered_map<string, vector<BaseFreq> >::iterator it_j;
    
    ofstream fs_err_context_file = open_outfile(err_context_file);
    
    for (it_i=err_context.data.begin(); it_i!=err_context.data.end(); it_i++) {
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); it_j++) {
            fs_err_context_file << it_i->first << ',' << it_j->first << '\t';
            for (int i=0; i<(int) it_j->second.size(); i++) {
                fs_err_context_file << it_j->second[i].refID << '@' << it_j->second[i].locus << '#' << it_j->second[i].cvg_ins << ',' << it_j->second[i].cvg << '|' <<
                        it_j->second[i].prob_ins << '&' << it_j->second[i].prob << '\t';
            }
            fs_err_context_file << endl;
        }
    }
    
    fs_err_context_file.close();
}

void ErrorModeler::load(string err_context_file) {
    ifstream fs_err_context_file = open_infile(err_context_file);
    while(true) {
        string cur_line;
        getline(fs_err_context_file, cur_line);
        
        if (fs_err_context_file.eof()) break;
        
        // get context
        vector<string> buf = split(cur_line, '\t');
        if (buf.size() < 2) 
            throw runtime_error("Error in ErrorModeler::load : size of buf < 2.");
        
        vector<string> context = split(buf[0],',');
        if (context.size() != 2) 
            throw runtime_error("Error in ErrorModeler::load : size of context != 2");
        
        //cout << context[0]<<','<<context[1] << endl;
        
        // parse BaseFreq of each locus
        vector<BaseFreq> basefreq_vec;
        for (int i=1; i < (int)buf.size(); i++) {
            basefreq_vec.push_back( parseLocus(buf[i]) );
        }
        err_context.data[context[0]][context[1]] = basefreq_vec;
    }
    
    fs_err_context_file.close();
}

BaseFreq ErrorModeler::parseLocus(string& buf) {
    BaseFreq basefreq;
    
    // parse level 1
    vector<string> lev_1 = split(buf, '|');
    if (lev_1.size() != 2) throw runtime_error("Error in ErrorModeler::parseLocus : size of lev_1 is not 2.");
    
    // parse level 2
    vector<string> lev_2_l = split(lev_1[0], '#');
    vector<string> lev_2_r = split(lev_1[1], '&', false);
    //cout << lev_2_l.size() << ',' << lev_2_r.size() << endl;
    
    if (lev_2_l.size() !=2 || lev_2_r.size() != 2)
        throw runtime_error("Error in ErrorModeler::parseLocus : size of lev_2 is not 2.");
    
    // parse level 3
    vector<string> lev_3_ll = split(lev_2_l[0], '@');
    vector<string> lev_3_lr = split(lev_2_l[1], ',');
    //cout << lev_3_ll.size() << ',' << lev_3_lr.size() << endl;
            
    if (lev_3_ll.size() !=2 || lev_3_lr.size() != 2)
        throw runtime_error("Error in ErrorModeler::parseLocus : size of lev_3_l* is not 2.");
    basefreq.refID = atoi(lev_3_ll[0].c_str());
    basefreq.locus = atoi(lev_3_ll[1].c_str());
    basefreq.cvg_ins = atoi(lev_3_lr[0].c_str());
    basefreq.cvg = atoi(lev_3_lr[1].c_str());
    
    
    vector<string> lev_3_rl = split(lev_2_r[0], ',');
    vector<string> lev_3_rr = split(lev_2_r[1], ',');
    for (int i=0; i<(int)lev_3_rl.size(); i++) {
        vector<string> cur_buf = split(lev_3_rl[i], ':');
        basefreq.prob_ins[cur_buf[0]] = stod(cur_buf[1].c_str());
    }
    for (int i=0; i<(int)lev_3_rr.size(); i++) {
        vector<string> cur_buf = split(lev_3_rr[i], ':');
        basefreq.prob[cur_buf[0]] = stod(cur_buf[1].c_str());
    }
    
    return basefreq;
}