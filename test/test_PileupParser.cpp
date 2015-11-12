/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test_PileupParser.h
 * Author: zhixingfeng
 *
 * Created on November 12, 2015, 3:48 PM
 */

#ifndef TEST_PILEUPPARSER_H
#define TEST_PILEUPPARSER_H

#include "../include/catch.hpp"
#include "../src/plugin/plugin.h"

        
SCENARIO ("Test PileupParserGDA", "[PileupParser][PileupParserGDA]") {
    string pileupfile_gda = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup"; 
    
    GIVEN ("A object of PileupParserGDA and pileupfile " + pileupfile_gda) {
 
        PileupParserGDA obj_PileupParserGDA;
        
        WHEN ("pointer ptr_fs_pileupfile is not set") {
            AND_WHEN ("readLines() is called") {
                THEN ("A expection should be thrown") {
                    REQUIRE_THROWS(obj_PileupParserGDA.readLines());
                }
            }
        }
        
        WHEN ("pointer ptr_fs_pileupfile is set") {
            ifstream fs_pileup = open_infile(pileupfile_gda);
            obj_PileupParserGDA.setPileupFileStream(& fs_pileup);
            obj_PileupParserGDA.readLines(10);
            fs_pileup.close();
        }
        
    }
}


#endif /* TEST_PILEUPPARSER_H */

