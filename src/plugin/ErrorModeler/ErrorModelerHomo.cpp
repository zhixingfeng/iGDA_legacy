/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ErrorModelerHomo.cpp
 * Author: zhixingfeng
 * 
 * Created on November 13, 2015, 12:31 PM
 */

#include "ErrorModelerHomo.h"

ErrorModelerHomo::ErrorModelerHomo() {
    signature = "ErrorModelerHomo";
}

ErrorModelerHomo::ErrorModelerHomo(const ErrorModelerHomo& orig) {
}

ErrorModelerHomo::~ErrorModelerHomo() {
}

void ErrorModelerHomo::train(int left, int right) {
    // check if it is good to go
    if (pileupfile == "")
        throw runtime_error("Error in ErrorModelerHomo::train: pileupfile has not been setup.");
    if (ptr_PileupParser == NULL)
        throw runtime_error("Error in ErrorModelerHomo::train: PileupParser has not been setup.");
    
    // get RefGenome
    refgenome = ptr_PileupParser->getRefGenome(pileupfile);
    
    // calculate ErrorContextEffect
    ifstream fs_pileupfile;
    open_infile(fs_pileupfile, pileupfile);
    ptr_PileupParser->setPileupFileStream(& fs_pileupfile);
    
    int nlines = 0;
    while (true) {
        
        ptr_PileupParser->readLine();
        if (fs_pileupfile.eof()) break;
        
        nlines++; if (nlines % 1000 == 0) cout << "processed " << nlines << " loci\r";
        //nlines++; cout << "processed " << nlines << " loci" << endl;
        
        ptr_PileupParser->calBaseFreq();
        BaseFreq cur_basefreq = ptr_PileupParser->getBaseFreq();
        //cout << cur_basefreq.prob_ins << endl;
        //cout << cur_basefreq.prob << endl;
        pair<string, string> local_context = getLocalContext(cur_basefreq.refID, cur_basefreq.locus, left, right);

        if (local_context.first == "" || local_context.second == "") continue;
        
        err_context.data[local_context.first][local_context.second].push_back(cur_basefreq);
        
    }
    cout << "processed " << nlines << " loci" << endl;
    fs_pileupfile.close();
}


pair<string, string> ErrorModelerHomo::getLocalContext(int refID, int locus, int left, int right) {
    int i = locus - 1;
    if (i < 0 || i >= (int)refgenome[refID].size()) return pair<string, string>("","");
    
    int i_l = i; int i_r = i;
    int k_l = 0; int k_r = 0;
    
    // search to the left side
    while (true) {
        i_l--;
        if (i_l < 0) return pair<string, string>("","");
        if (refgenome[refID][i_l] != refgenome[refID][i_l + 1]) k_l++;
        if (k_l > left) break;        
    }
    i_l++;
    
    // search to the right side
    while (true) {
        i_r++;
        if (i_r >= (int)refgenome[refID].size()) return pair<string, string>("","");
        if (refgenome[refID][i_r] != refgenome[refID][i_r-1]) k_r++;
        if (k_r > right) break;
    }
    i_r--;
    
    if (i_l < 0 || i_r >= (int)refgenome[refID].size()) return pair<string, string>("","");
   
    return pair<string, string>(refgenome[refID].substr(i_l, i - i_l), refgenome[refID].substr(i, i_r - i + 1));
}