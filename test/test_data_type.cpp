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

#ifndef TEST_DATA_TYPE_H
#define TEST_DATA_TYPE_H

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

TEST_CASE( "Test Pileup2BaseFreq", "[data_type]" ) {
    string pileupfile_gda = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup";
    string basefreqfile_gda = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.basefreq";
    string baseprobfile_gda = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.baseprob";
    
    PileupParserGDA obj_PileupParserGDA;
    
    // load pileup
    ifstream fs_pileup = open_infile(pileupfile_gda);
    obj_PileupParserGDA.setPileupFileStream(& fs_pileup);
    while (!fs_pileup.eof())
        obj_PileupParserGDA.readLine();
    fs_pileup.close();
            
    vector<Pileup> obj_Pileup = obj_PileupParserGDA.getPileup();
    
    // calculate BaseFreq and print
    ofstream fs_basefreq = open_outfile(basefreqfile_gda);
    ofstream fs_baseprob = open_outfile(baseprobfile_gda);
    for (int i=0; i<(int)obj_Pileup.size(); i++) {
        BaseFreq obj_BaseFreq = Pileup2BaseFreq(obj_Pileup[i]);
        fs_basefreq << obj_BaseFreq.freq_ins << endl;
        fs_basefreq << obj_BaseFreq.freq << endl;
        fs_baseprob << obj_BaseFreq.prob_ins << endl;
        fs_baseprob << obj_BaseFreq.prob << endl;
    }
    fs_basefreq.close();
    fs_baseprob.close();
    
    // strict test needed.
}

#endif /* TEST_DATA_TYPE_H */

