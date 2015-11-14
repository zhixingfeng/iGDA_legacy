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


#endif /* TEST_DATA_TYPE_H */

