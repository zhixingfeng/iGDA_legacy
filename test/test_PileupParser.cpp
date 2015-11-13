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
                    REQUIRE_THROWS(obj_PileupParserGDA.readLines());
                }
            }
        }
        
        WHEN ("pointer ptr_fs_pileupfile is set") {
            // read pileup data
            ifstream fs_pileup = open_infile(pileupfile_gda);
            obj_PileupParserGDA.setPileupFileStream(& fs_pileup);
            while (!fs_pileup.eof())
                obj_PileupParserGDA.readLine();
            fs_pileup.close();
            
            vector<Pileup> obj_Pileup = obj_PileupParserGDA.getPileup();
            
            // write read pileup data 
            ofstream fs_pileup_out = open_outfile(pileupfile_gda_out);
            for (int i=0; i<(int)obj_Pileup.size(); i++)
                fs_pileup_out << obj_Pileup[i];
            fs_pileup.close();
            
            // read written data again to validate
            ifstream fs_pileup_in = open_infile(pileupfile_gda_out);
            obj_PileupParserGDA.setPileupFileStream(& fs_pileup_in);
            obj_PileupParserGDA.clear();
            while (!fs_pileup_in.eof())
                obj_PileupParserGDA.readLine();
            fs_pileup_in.close();
            
            vector<Pileup> obj_Pileup_in = obj_PileupParserGDA.getPileup();
            REQUIRE(obj_Pileup_in.size() == obj_Pileup.size());
            
            bool is_equal = true;
            for (int i=0; i<(int)obj_Pileup_in.size(); i++)
                if ( !(obj_Pileup_in[i] == obj_Pileup[i]) ) {is_equal = false; break;}
            REQUIRE(is_equal == true);
        }
        
    }
}


#endif /* TEST_PILEUPPARSER_H */

