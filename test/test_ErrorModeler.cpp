/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "../include/catch.hpp"
#include "../src/plugin/plugin.h"

TEST_CASE ("Test ErrorModelerHomo train(), save() and load()", "[ErrorModelerHomo][ErrorModeler]") {
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
    
    // converted ErrorContextEffect into basefreq
    ErrorContextEffect err_context = obj_ErrorModelerHomo.getErrorContextEffect();
    vector<BaseFreq> basefreq_vec;
    
    map<string, map<string, vector<BaseFreq> > >::iterator it_i;
    map<string, vector<BaseFreq> >::iterator it_j;
    for (it_i=err_context.data.begin(); it_i!=err_context.data.end(); it_i++) {
        for (it_j=it_i->second.begin(); it_j!=it_i->second.end(); it_j++) {
            for (int i=0; i<(int) it_j->second.size(); i++) {
                basefreq_vec.push_back(it_j->second[i]);
            }
        }
    }
    
    sort(basefreq_vec.begin(), basefreq_vec.end());
    ofstream fs_err_context_file; open_outfile(fs_err_context_file, err_context_basefreqfile);
    for (int i=0; i<(int)basefreq_vec.size(); i++){
        fs_err_context_file << basefreq_vec[i].prob_ins << endl;
        fs_err_context_file << basefreq_vec[i].prob << endl;
    }
    fs_err_context_file.close();
    
    // check converted BaseFreq
    ifstream fs_check_baseprob;
    open_infile(fs_check_baseprob, "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.baseprob");
    ifstream fs_check_baseprob_converted;
    open_infile(fs_check_baseprob_converted, "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.err_context.baseprob");
    string cur_line;
    string cur_line_converted;
    // ignore first two lines of fs_check_baseprob
    getline(fs_check_baseprob, cur_line); getline(fs_check_baseprob, cur_line);
    getline(fs_check_baseprob, cur_line); getline(fs_check_baseprob, cur_line);
    while(true) {
        getline(fs_check_baseprob, cur_line);
        getline(fs_check_baseprob_converted, cur_line_converted);
        if (fs_check_baseprob.eof() || fs_check_baseprob_converted.eof()) break;
        vector<string> buf = split(cur_line,',');
        vector<string> buf_converted = split(cur_line_converted, ',');
        sort(buf.begin(), buf.end());
        sort(buf_converted.begin(), buf_converted.end());
        REQUIRE(buf.size() == buf_converted.size());
        for (int i=0; i<(int)buf.size(); i++) {
            REQUIRE(buf[i] == buf_converted[i]);
        }
    }
    
    fs_check_baseprob.close();
    fs_check_baseprob_converted.close();   
    
    
    
}


TEST_CASE ("Test ErrorModelerHomo save_mean_err()", "[ErrorModelerHomo][ErrorModeler]") {
    string pileupfile = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup"; 
    string err_mean_file = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.err.mean"; 
    
    ErrorModelerHomo obj_ErrorModelerHomo;
    obj_ErrorModelerHomo.setPileupFile(pileupfile);
    PileupParserGDA obj_PileupParser;
    obj_ErrorModelerHomo.setPileupParser(& obj_PileupParser);
    
    obj_ErrorModelerHomo.train();

    obj_ErrorModelerHomo.calErrorRateStat();
    
    obj_ErrorModelerHomo.save_mean_err(err_mean_file);
    //obj_ErrorModelerHomo.save(err_mean_file + ".raw");
}


TEST_CASE ("Test ErrorModeler getLocalContext()", "[ErrorModeler]") {
    string pileupfile = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup"; 
    
    PileupParserGDA obj_PileupParser;
    ErrorModelerHomo obj_ErrorModeler;
    
    REQUIRE_THROWS(obj_ErrorModeler.getRefGenome());
    obj_ErrorModeler.setPileupFile(pileupfile);
    REQUIRE_THROWS(obj_ErrorModeler.getRefGenome());
    obj_ErrorModeler.setPileupParser(& obj_PileupParser);
    REQUIRE_THROWS(obj_ErrorModeler.getLocalContext(0,100,1,1));
    obj_ErrorModeler.getRefGenome();
    pair<string, string> context = obj_ErrorModeler.getLocalContext(0,100,1,1);
    REQUIRE(context.first == "AA");
    REQUIRE(context.second == "TA");

}


TEST_CASE ("Test ErrorModelerHomo searchErrorContextEffect*() ", "[ErrorModelerSeach]") {
    PileupParserGDA obj_PileupParser;
    ErrorModelerHomo obj_ErrorModeler;
    string pileupfile = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup"; 
    
    obj_ErrorModeler.setPileupFile(pileupfile);
    obj_ErrorModeler.setPileupParser(& obj_PileupParser);
    obj_ErrorModeler.getRefGenome();
    
    obj_ErrorModeler.load("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.err");
    obj_ErrorModeler.calErrorRateStat();
                
       
    pair<string, string> context = obj_ErrorModeler.getLocalContext(0, 100, 1, 1);
    REQUIRE(context.first=="AA");
    REQUIRE(context.second=="TA");
    
    vector<BaseFreq> basefreq = obj_ErrorModeler.searchErrorContextEffect(0, 100, 1, 1);
    REQUIRE(basefreq.size() == 7);
    REQUIRE(basefreq[0].prob_ins["C"] == Approx(0.0103093));
    REQUIRE(basefreq[0].prob_ins["CT"] == Approx(0.00515464));
    REQUIRE(basefreq[0].prob_ins["G"] == Approx(0.0206186));
    REQUIRE(basefreq[0].prob_ins["T"] == Approx(0.0309278));
    REQUIRE(basefreq[0].prob["-"] == Approx(0.0309278));
    REQUIRE(basefreq[0].prob["C"] == Approx(0.00515464));
    REQUIRE(basefreq[0].prob["T"] == Approx(0.963918));
    
    map<string, double> basefreq_mean_ins = obj_ErrorModeler.searchErrorContextEffectMeanIns(0, 100, 1, 1);
    map<string, double> basefreq_mean = obj_ErrorModeler.searchErrorContextEffectMean(0, 100, 1, 1);
    int basefreq_cvg = obj_ErrorModeler.searchErrorContextEffectCvg(0, 100, 1, 1);
    REQUIRE(basefreq_cvg == 1358);
    REQUIRE( basefreq_mean_ins["C"] == Approx(0.0132548) );
    REQUIRE( basefreq_mean_ins["CT"] == Approx(0.000736377) );
    REQUIRE( basefreq_mean_ins["G"] == Approx(0.011782) );
    REQUIRE( basefreq_mean_ins["GCC"] == Approx(0.000736377) );
    REQUIRE( basefreq_mean_ins["GG"] == Approx(0.00147275) );
    REQUIRE( basefreq_mean_ins["T"] == Approx(0.0434462) );
    REQUIRE( basefreq_mean_ins["TT"] == Approx(0.00368189) );
    REQUIRE( basefreq_mean["-"] == Approx(0.0294551) );
    REQUIRE( basefreq_mean["A"] == Approx(.000736377) );
    REQUIRE( basefreq_mean["C"] == Approx(0.00220913) );
    REQUIRE( basefreq_mean["G"] == Approx(0.00515464) );
    REQUIRE( basefreq_mean["T"] == Approx(0.962445) );
    
}