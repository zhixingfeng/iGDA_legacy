/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../include/catch.hpp"
#include "../src/plugin/plugin.h"

TEST_CASE("Test PreCaller setup resources", "[PreCaller]") {
    PreCallerSingle obj_PreCallerSingle;
    
    PileupParserGDA obj_PileupParserGDA;
    ErrorModelerHomo obj_ErrorModelerHomo;
    
    REQUIRE_THROWS(obj_PreCallerSingle.setPileupParser(& obj_PileupParserGDA));
    obj_PreCallerSingle.setPileupfile("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup");
    REQUIRE_THROWS(obj_PreCallerSingle.setErrorModeler(& obj_ErrorModelerHomo));
    
    REQUIRE_NOTHROW( obj_PreCallerSingle.setPileupParser(& obj_PileupParserGDA) );
    REQUIRE_NOTHROW( obj_PreCallerSingle.setErrorModeler(& obj_ErrorModelerHomo)  );
    
}