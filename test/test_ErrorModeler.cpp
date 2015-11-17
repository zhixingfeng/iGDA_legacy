/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "../include/catch.hpp"
#include "../src/plugin/plugin.h"

TEST_CASE ("Test ErrorModelerHomo", "[ErrorModelerHomo][ErrorModeler]") {
    string pileupfile = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup"; 
    string err_context_file = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.err";
    string err_context_basefreqfile = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.err_context.baseprob";
        
    ErrorModelerHomo obj_ErrorModelerHomo;
    REQUIRE_THROWS( obj_ErrorModelerHomo.train() );
        
    obj_ErrorModelerHomo.setPileupFile(pileupfile);
    REQUIRE_THROWS( obj_ErrorModelerHomo.train() );
         
        
    PileupParserGDA obj_PileupParser;
    obj_ErrorModelerHomo.setPileupParser(& obj_PileupParser);
    obj_ErrorModelerHomo.train();
    obj_ErrorModelerHomo.save(err_context_file);
        
    // clear ErrorModel and load from saved err_context_file
    obj_ErrorModelerHomo.clear();
    obj_ErrorModelerHomo.load(err_context_file);
    
    // converted ErrorContextEffect into 
    ErrorContextEffect err_context = obj_ErrorModelerHomo.getErrorContextEffect();
    vector<BaseFreq> basefreq_vec;
    
    unordered_map<string, unordered_map<string, vector<BaseFreq> > >::iterator it_i;
    unordered_map<string, vector<BaseFreq> >::iterator it_j;
    for (it_i=err_context.data.begin(); it_i!=err_context.data.end(); it_i++) {
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); it_j++) {
            for (int i=0; i<(int) it_j->second.size(); i++) {
                basefreq_vec.push_back(it_j->second[i]);
            }
        }
    }
    
    sort(basefreq_vec.begin(), basefreq_vec.end());
    ofstream fs_err_context_file = open_outfile(err_context_basefreqfile);
    for (int i=0; i<(int)basefreq_vec.size(); i++){
        fs_err_context_file << basefreq_vec[i].prob_ins << endl;
        fs_err_context_file << basefreq_vec[i].prob << endl;
    }
    fs_err_context_file.close();
    
    //
    
}
