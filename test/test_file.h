/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test_file.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 6:11 PM
 */

#ifndef TEST_FILE_H
#define TEST_FILE_H
#include "../include/headers.h"

TEST_CASE( "Test open_infile", "[file]" ) {
    string real_file = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup";
    string wrong_file = "wrongfile.txt";    
    REQUIRE_NOTHROW(open_infile(real_file));
    REQUIRE_THROWS(open_infile(wrong_file));
}

TEST_CASE( "Test open_outfile", "[file]" ) {
    string real_file = "./results/test_open_outfile.txt";
    string wrong_file = "./results_noexist/test_open_outfile.txt";    
    REQUIRE_NOTHROW(open_outfile(real_file));
    REQUIRE_THROWS(open_outfile(wrong_file));
}

#endif /* TEST_FILE_H */

