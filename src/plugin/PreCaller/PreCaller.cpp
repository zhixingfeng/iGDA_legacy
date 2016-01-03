/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreCaller.cpp
 * Author: zhixingfeng
 * 
 * Created on November 11, 2015, 4:54 PM
 */

#include "PreCaller.h"

PreCaller::PreCaller() {
    pileupfile = "";
    outprefix = "";
    ptr_PileupParser = NULL;
    ptr_ErrorModeler = NULL;
    signature = "PreCaller";
    this->readlen = 1000;
}

PreCaller::PreCaller(const PreCaller& orig) {
}

PreCaller::~PreCaller() {
}

void PreCaller::setPileupParser(PileupParser* a_PileupParser) {
    ptr_PileupParser = a_PileupParser;
}

void PreCaller::setErrorModeler(ErrorModeler* a_ErrorModeler) {
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in PreCaller::setErrorModeler: ptr_PileupParser is NULL.");
    ptr_ErrorModeler = a_ErrorModeler;
    ptr_ErrorModeler->setPileupParser(ptr_PileupParser);
}

void PreCaller::loadErrorModel(string a_err_context_file) {
    if (ptr_ErrorModeler == NULL)
        throw runtime_error("Error in PreCaller::loadErrorModel: ptr_ErrorModeler is NULL.");
    err_context_file = a_err_context_file;
    ptr_ErrorModeler->load(err_context_file);
    ptr_ErrorModeler->calErrorRateStat();
}

void PreCaller::writeVar(string out_prefix) {
    ofstream fs_out; open_outfile(fs_out, out_prefix + ".var.match");
    map<int, vector<VarStat> >::iterator it;
    for (it=varstat.begin(); it!=varstat.end(); it++) 
        for (int i=0; i<(int)it->second.size(); i++)
            fs_out << it->second[i] << endl;
    fs_out.close();

    open_outfile(fs_out, out_prefix + ".var.ins");
    for (it=varstat_ins.begin(); it!=varstat_ins.end(); it++) 
        for (int i=0; i<(int)it->second.size(); i++)
            fs_out << it->second[i] << endl;
    fs_out.close();
    
    open_outfile(fs_out, out_prefix + ".var.del");
    for (it=varstat_del.begin(); it!=varstat_del.end(); it++) 
        for (int i=0; i<(int)it->second.size(); i++)
            fs_out << it->second[i] << endl;
    fs_out.close();
    
}

void PreCaller::calStat(VarStat& stat, map<string,double>& prob, map<string,double>& prob_ctrl) {
    stat.log_prob_ratio.clear();
    map<string,double>::iterator it;
    map<string,double>::iterator it_ctrl;
    
    stat.effect_size = log(EPS);
    for (it=prob.begin(); it!=prob.end(); it++) {
        it_ctrl = prob_ctrl.find(it->first);
        if (it_ctrl == prob_ctrl.end()) {
            stat.log_prob_ratio[it->first] = NAN; 
            continue;
        }
        if (it_ctrl->second < EPS) {
            stat.log_prob_ratio[it->first] = NAN; 
            continue;
        }
        stat.log_prob_ratio[it->first] = log(it->second / it_ctrl->second);
        if (stat.log_prob_ratio[it->first] > stat.effect_size)
            stat.effect_size = stat.log_prob_ratio[it->first];
    }
}


