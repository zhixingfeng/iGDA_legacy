/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test_iGDA.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 6:31 PM
 */

#ifndef TEST_IGDA_H
#define TEST_IGDA_H

#include "../src/iGDA.h"

TEST_CASE( "Test setPileupFile", "[iGDA]" ) {
    string real_file = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup";
    string wrong_file = "wrongfile.txt";
    iGDA gda;
    REQUIRE_NOTHROW(gda.setPileupFile(real_file));
    REQUIRE_THROWS(gda.setPileupFile(wrong_file));
}

TEST_CASE( "Test getPileupFile", "[iGDA]" ) {
    string real_file = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup";
    iGDA gda;
    gda.setPileupFile(real_file);
    REQUIRE(gda.getPileupFile() == real_file);
}

TEST_CASE( "Test verifyPlugin", "[iGDA]" ) {
    iGDA gda;
    
    PileupParserGDA obj_PileupParserGDA;
    PreCallerSingle obj_PreCallerSingle;
    
    REQUIRE_THROWS(gda.verifyPlugin());
    gda.setPileupParser(& obj_PileupParserGDA);
    
    REQUIRE_THROWS(gda.verifyPlugin());
    gda.setPreCaller(& obj_PreCallerSingle);
    
    REQUIRE_NOTHROW(gda.verifyPlugin());
}


TEST_CASE( "Test signature of plugins", "[iGDA]" ) {
    iGDA gda;
    PreCaller obj_PreCaller;
    PreCallerSingle obj_PreCallerSingle;
    PreCallerMultiple obj_PreCallerMultiple;
    
    gda.setPreCaller(& obj_PreCaller);
    REQUIRE(gda.getSigPreCaller() == "PreCaller");
    
    gda.setPreCaller(& obj_PreCallerSingle);
    REQUIRE(gda.getSigPreCaller() == "PreCallerSingle");
    
    gda.setPreCaller(& obj_PreCallerMultiple);
    REQUIRE(gda.getSigPreCaller() == "PreCallerMultiple");
}

//tests to be continued after run() is completed.

#endif /* TEST_IGDA_H */

