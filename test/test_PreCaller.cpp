/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../include/catch.hpp"
#include "../src/plugin/plugin.h"

TEST_CASE("Test default constructor of VarStat", "[PreCaller]") {
    VarStat varstat;
    REQUIRE(varstat.cvg == -1);
    REQUIRE(varstat.cvg_ctrl == -1);
    REQUIRE(isnan(varstat.effect_size));
    REQUIRE(varstat.locus == -1);
    REQUIRE(isnan(varstat.p_value));
}

TEST_CASE("Test constructor of VarStat", "[PreCaller]") {
    VarStat varstat(1.98, 0.01, 10, 2847, 3625);
    REQUIRE(varstat.cvg == 10);
    REQUIRE(varstat.cvg_ctrl == 2847);
    REQUIRE(varstat.effect_size == 1.98);
    REQUIRE(varstat.locus == 3625);
    REQUIRE(varstat.p_value == 0.01);
    
    vector<VarStat> varstat_vec;
    varstat_vec.push_back(VarStat(1.98, 0.01, 10, 2847, 3625));
    REQUIRE(varstat_vec[0].cvg == 10);
    REQUIRE(varstat_vec[0].cvg_ctrl == 2847);
    REQUIRE(varstat_vec[0].effect_size == 1.98);
    REQUIRE(varstat_vec[0].locus == 3625);
    REQUIRE(varstat_vec[0].p_value == 0.01);
}



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

TEST_CASE("Test PreCallerSingle callVar()", "[PreCaller]") {
    PreCallerSingle obj_PreCallerSingle;
    
    PileupParserGDA obj_PileupParserGDA;
    ErrorModelerHomo obj_ErrorModelerHomo;
    
    obj_PreCallerSingle.setPileupfile("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup");
    obj_PreCallerSingle.setPileupParser(& obj_PileupParserGDA);
    obj_PreCallerSingle.setErrorModeler(& obj_ErrorModelerHomo);
    
    obj_PreCallerSingle.loadErrorModel("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.err");
    
    obj_PreCallerSingle.callVar();
    map<int, vector<VarStat> > var_stat = obj_PreCallerSingle.getVar();
    
    
}



