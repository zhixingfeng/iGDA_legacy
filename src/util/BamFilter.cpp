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
    // open bam file
    BamReader reader;
    if ( !reader.Open(infile) ) 
        throw runtime_error("Error in BamFilter::bam2Fa, fail to open " + infile);
    BamAlignment al;
    
    // open output fasta file
    ofstream fs_outfile; open_outfile(fs_outfile, outfile);
    while ( reader.GetNextAlignment(al) ) {
        fs_outfile << '>' << al.Name << endl;
        fs_outfile << al.QueryBases << endl;        
    }
    
    fs_outfile.close();
    reader.Close();
    
}

void BamFilter::filter(string infile, string outfile, bool is_forward, int min_matches) {
    // open bam file
    BamReader reader;
    if ( !reader.Open(infile) ) 
        throw runtime_error("Error in BamFilter::filter, fail to open " + infile);
    BamAlignment al;
    
    // open output bam file
    const SamHeader header = reader.GetHeader();
    const RefVector references = reader.GetReferenceData();
    BamWriter writer;
    if ( !writer.Open(outfile, header, references) ) 
        throw runtime_error("Error in BamFilter::filter, fail to open " + outfile);
        
    while ( reader.GetNextAlignment(al) ) {
        // get numer of matches
        vector<CigarOp> cigar = al.CigarData;
        int num_M = 0;
        for (int i=0; i<(int)cigar.size(); ++i) 
            if (cigar[i].Type=='M' || cigar[i].Type=='=' || cigar[i].Type=='X')
                num_M += cigar[i].Length;
        
        // remove backward reads
        if (is_forward) 
            if (al.IsReverseStrand())
                continue;
        
        // remove reads with too few matches.
        if (num_M < min_matches)
            continue;
        writer.SaveAlignment(al);
    }
    reader.Close();
    writer.Close();
}