/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test_data_type.h
 * Author: zhixingfeng
 *
 * Created on November 12, 2015, 12:45 PM
 */

#include "../include/catch.hpp"
#include "../include/headers.h"
#include "../src/plugin/plugin.h"

TEST_CASE("Test Pileup", "[data_type]") {
    Pileup obj_Pileup(0, 104, 'A', 194, 24);
    REQUIRE(obj_Pileup.refID == 0);
    REQUIRE(obj_Pileup.locus == 104);
    REQUIRE(obj_Pileup.refSeq == 'A');
    REQUIRE(obj_Pileup.cvg == 194);
    REQUIRE(obj_Pileup.cvg_ins == 24);
}

TEST_CASE("Test BaseFreq", "[data_type]") {
    SECTION("Constructor BaseFreq(int refID, int locus, char refSeq, int cvg, int cvg_ins) ") {
        BaseFreq obj_BaseFreq(0, 104, 'A', 194, 24);
        REQUIRE(obj_BaseFreq.refID == 0);
        REQUIRE(obj_BaseFreq.locus == 104);
        REQUIRE(obj_BaseFreq.refSeq == 'A');
        REQUIRE(obj_BaseFreq.cvg == 194);
        REQUIRE(obj_BaseFreq.cvg_ins == 24);
    }
    SECTION("Constructor BaseFreq(const Pileup & obj_Pileup)") {
        Pileup obj_Pileup(0, 104, 'A', 194, 24);
        BaseFreq obj_BaseFreq(obj_Pileup);
        REQUIRE(obj_BaseFreq.refID == 0);
        REQUIRE(obj_BaseFreq.locus == 104);
        REQUIRE(obj_BaseFreq.refSeq == 'A');
        REQUIRE(obj_BaseFreq.cvg == 194);
        REQUIRE(obj_BaseFreq.cvg_ins == 24);
    }
}


TEST_CASE( "Test str2NtSeq and NtSeq2Str", "[data_type]" ) {
    string seq = "CGTAGTCGTAGCGATGCTAGCGTNNNGTCGTAG";
    NtSeq ntseq = str2NtSeq(seq);
    REQUIRE(NtSeq2Str(ntseq) == seq);
}

TEST_CASE( "Test Pileup2BaseFreq", "[data_type][hide]" ) {
    string pileupfile_gda = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup";
    string basefreqfile_gda = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.basefreq";
    string baseprobfile_gda = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.baseprob";
   
    // load pileup
    ifstream fs_pileup; open_infile(fs_pileup, pileupfile_gda);
    ofstream fs_basefreq; open_outfile(fs_basefreq, basefreqfile_gda);
    ofstream fs_baseprob; open_outfile(fs_baseprob, baseprobfile_gda);
    
    PileupParserGDA obj_PileupParserGDA(& fs_pileup);
    
    while (true) {
        obj_PileupParserGDA.readLine();
        if (fs_pileup.eof()) break;
        Pileup obj_Pileup = obj_PileupParserGDA.getPileup();
        BaseFreq obj_BaseFreq = Pileup2BaseFreq(obj_Pileup);
        fs_basefreq << obj_BaseFreq.freq_ins << endl;
        fs_basefreq << obj_BaseFreq.freq << endl;
        fs_baseprob << obj_BaseFreq.prob_ins << endl;
        fs_baseprob << obj_BaseFreq.prob << endl;
    }
    
    fs_pileup.close();
    fs_basefreq.close();
    fs_baseprob.close();
    
    // strict test needed.
}

TEST_CASE("Compare and sort BaseFreq") {
    BaseFreq basefreq_l;
    BaseFreq basefreq_r;
    
    basefreq_l.refID = 0;
    basefreq_r.refID = 1;
    REQUIRE(basefreq_l <= basefreq_r);
    REQUIRE(basefreq_l < basefreq_r);
    REQUIRE(basefreq_r >= basefreq_l);
    REQUIRE(basefreq_r > basefreq_l);
    
    basefreq_l.refID = 0;
    basefreq_r.refID = 0;
    basefreq_l.locus = 20;
    basefreq_r.locus = 45;
    REQUIRE(basefreq_l <= basefreq_r);
    REQUIRE(basefreq_l < basefreq_r);
    REQUIRE(basefreq_r >= basefreq_l);
    REQUIRE(basefreq_r > basefreq_l);
    
    vector<BaseFreq> basefreq_vec;
    basefreq_vec.push_back(basefreq_r);
    basefreq_vec.push_back(basefreq_l);
    sort(basefreq_vec.begin(), basefreq_vec.end());
    REQUIRE(basefreq_vec[0].locus == basefreq_l.locus);
    REQUIRE(basefreq_vec[1].locus == basefreq_r.locus);
    
}


TEST_CASE("test insert elements into map") {
    map<string, double> x;
    x["test"]+=1;
    x["test"]+=2;
    REQUIRE(x["test"]==3);
}

/*TEST_CASE("Test the order of key in map") {
    map<string, double> x;
    map<string, double> y;
    x["CGTAGC"] = 1; y["CGTAGC"] = 1;
    x["GTCGTAGTC"] = 2; y["GTCGTAGTC"] = 2;
    x["CGTAGTCT"] = 3; y["CGTAGTCT"] = 3;
    x["AGTCGTA"] = 4; y["AGTCGTA"] = 4;
    
    map<string, double>::iterator it;
    map<string, double>::iterator it_2;
    for (it=x.begin(); it!=x.end(); it++) {
        cout << it->first << endl;
        
    }
    cout << endl;
    for (it_2=y.begin(); it_2!=y.end(); it_2++) {
        cout << it_2->first << endl;
        
    }
}
 */