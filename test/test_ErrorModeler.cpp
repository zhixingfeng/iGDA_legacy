/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "../include/catch.hpp"
#include "../src/plugin/plugin.h"

SCENARIO ("Test ErrorModelerHomo", "[ErrorModelerHomo][ErrorModeler]") {
    string pileupfile = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup"; 
    GIVEN("A object of ErrorModelerHomo and a pileup file " + pileupfile) {
        
        ErrorModelerHomo obj_ErrorModelerHomo;
        
        WHEN ("pileupfile has not been set and train() is called") {
            THEN ("train() should throw a expection") {
                REQUIRE_THROWS( obj_ErrorModelerHomo.train() );
            }
        }
        obj_ErrorModelerHomo.setPileupFile(pileupfile);
        WHEN ("PileupParser has not been set and train() is called") {
            THEN ("train() should throw a expection") {
                REQUIRE_THROWS( obj_ErrorModelerHomo.train() );
            }
        }
        
        PileupParserGDA obj_PileupParser;
        obj_ErrorModelerHomo.setPileupParser(& obj_PileupParser);
        obj_ErrorModelerHomo.train();
    }
}
