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
    string pileupfile_gda_out = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup.out";
    
    GIVEN ("A object of PileupParserGDA and pileupfile " + pileupfile_gda) {
 
        PileupParserGDA obj_PileupParserGDA;
        
        WHEN ("pointer ptr_fs_pileupfile is not set") {
            AND_WHEN ("readLines() is called") {
                THEN ("A expection should be thrown") {
                    REQUIRE_THROWS(obj_PileupParserGDA.readLine());
                }
            }
        }
        
        WHEN ("pointer ptr_fs_pileupfile is set") {
            // read and write pileup data
            ifstream fs_pileup = open_infile(pileupfile_gda);
            ofstream fs_pileup_out = open_outfile(pileupfile_gda_out);
            
            obj_PileupParserGDA.setPileupFileStream(& fs_pileup);
            while (true) {
                obj_PileupParserGDA.readLine();
                if (fs_pileup.eof()) break;
                fs_pileup_out << obj_PileupParserGDA.getPileup();
            }
            fs_pileup.close();
            fs_pileup_out.close();

            // check written file
            ifstream fs_pileup_in = open_infile(pileupfile_gda_out);
            fs_pileup = open_infile(pileupfile_gda);
            
            PileupParserGDA obj_PileupParserGDA_in( & fs_pileup_in);
            while (true){
                bool is_end = obj_PileupParserGDA.readLine();
                bool is_end_out = obj_PileupParserGDA_in.readLine();
                REQUIRE(is_end == is_end_out);
                if (is_end) break;
                REQUIRE(obj_PileupParserGDA.getPileup() == obj_PileupParserGDA_in.getPileup());
            }
            
        }
        
    }
}


#endif /* TEST_PILEUPPARSER_H */

