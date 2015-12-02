/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreCallerSingle.cpp
 * Author: zhixingfeng
 * 
 * Created on November 11, 2015, 5:17 PM
 */

#include "PreCallerSingle.h"

PreCallerSingle::PreCallerSingle() {
    signature = "PreCallerSingle";
}

PreCallerSingle::PreCallerSingle(const PreCallerSingle& orig) {
}

PreCallerSingle::~PreCallerSingle() {
}

void PreCallerSingle::callVar(int min_cvg, int min_cvg_ctrl, int len_l, int len_r) {
    if (pileupfile == "")
        throw runtime_error("Error in PreCaller::callVar: pileupfile is empty.");
    if (err_context_file == "")
        throw runtime_error("Error in PreCallerSingle::callVar: err_context_file is empty.");
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in PreCaller::callVar: ptr_PileupParser is NULL.");
    if (ptr_ErrorModeler == NULL)
        throw runtime_error("Error in PreCallerSingle::callVar: ptr_ErrorModeler is NULL.");
    
    // reference genome
    ptr_ErrorModeler->setPileupFile(pileupfile);
    ptr_ErrorModeler->getRefGenome();
    
    // scan the pileupfile 
    ifstream fs_pileupfile; open_infile(fs_pileupfile, pileupfile);
    ptr_PileupParser->setPileupFileStream(& fs_pileupfile);
    while (true) {
        ptr_PileupParser->readLine();
        if (fs_pileupfile.eof()) break;
        
        // get frequency of current locus
        ptr_PileupParser->calBaseFreq();
        BaseFreq basefreq = ptr_PileupParser->getBaseFreq();
        int basefreq_ctrl_cvg = ptr_ErrorModeler->searchErrorContextEffectCvg(basefreq.refID, basefreq.locus, len_l, len_r);
        
        if (basefreq.cvg < min_cvg) {
            varstat[basefreq.refID].push_back( VarStat(NAN, NAN, basefreq.cvg, basefreq_ctrl_cvg, basefreq.locus) );
            varstat_ins[basefreq.refID].push_back( VarStat(NAN, NAN, basefreq.cvg, basefreq_ctrl_cvg, basefreq.locus) );
            varstat_del[basefreq.refID].push_back( VarStat(NAN, NAN, basefreq.cvg, basefreq_ctrl_cvg, basefreq.locus) );
            continue;
        }
        
        // get frequency of control data
        if (basefreq_ctrl_cvg < min_cvg_ctrl) {
            varstat[basefreq.refID].push_back( VarStat(NAN, NAN, basefreq.cvg, basefreq_ctrl_cvg, basefreq.locus) );
            varstat_ins[basefreq.refID].push_back( VarStat(NAN, NAN, basefreq.cvg, basefreq_ctrl_cvg, basefreq.locus) );
            varstat_del[basefreq.refID].push_back( VarStat(NAN, NAN, basefreq.cvg, basefreq_ctrl_cvg, basefreq.locus) );
            continue;
        }
        map<string, double> basefreq_ctrl_mean_ins = ptr_ErrorModeler->searchErrorContextEffectMeanIns(basefreq.refID, basefreq.locus, len_l, len_r);
        map<string, double> basefreq_ctrl_mean = ptr_ErrorModeler->searchErrorContextEffectMean(basefreq.refID, basefreq.locus, len_l, len_r);
        
        // compare to control data
        VarStat stat(NAN, NAN, basefreq.cvg, basefreq_ctrl_cvg, basefreq.locus);
        VarStat stat_ins(NAN, NAN, basefreq.cvg, basefreq_ctrl_cvg, basefreq.locus);
        VarStat stat_del(NAN, NAN, basefreq.cvg, basefreq_ctrl_cvg, basefreq.locus);
        
        map<string, double> prob_m = ptr_PileupParser->getMatchProb(basefreq.prob, basefreq.refSeq);
        map<string, double> prob_d = ptr_PileupParser->getDelProb(basefreq.prob);
        
        map<string, double> prob_m_ctrl = ptr_PileupParser->getMatchProb(basefreq_ctrl_mean, basefreq.refSeq);
        map<string, double> prob_d_ctrl = ptr_PileupParser->getDelProb(basefreq_ctrl_mean);
        
        calStat(stat, prob_m, prob_m_ctrl);
        calStat(stat_ins, basefreq.prob_ins, basefreq_ctrl_mean_ins);
        calStat(stat_del, prob_d, prob_d_ctrl);
        
        // record stat
        varstat[basefreq.refID].push_back(stat);
        varstat_ins[basefreq.refID].push_back(stat_ins);
        varstat_del[basefreq.refID].push_back(stat_del);
    }
    fs_pileupfile.close();
}

void PreCallerSingle::calStat(VarStat& stat, map<string,double>& prob, map<string,double>& prob_ctrl) {
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




