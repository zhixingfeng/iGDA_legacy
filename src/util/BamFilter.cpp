/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BamFilter.cpp
 * Author: zhixingfeng
 * 
 * Created on December 29, 2015, 11:06 PM
 */

#include "BamFilter.h"

BamFilter::BamFilter() {
    
}

BamFilter::BamFilter(const BamFilter& orig) {
    
}

BamFilter::~BamFilter() {
    
}

void BamFilter::bam2Fa(string infile, string outfile) {
    BamReader reader;
    if ( !reader.Open(infile) ) 
        throw runtime_error("Error in BamFilter::bam2Fa, fail to open " + infile);
    
    
    reader.Close();
    
}


