/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BamFilter.h
 * Author: zhixingfeng
 *
 * Created on December 29, 2015, 11:06 PM
 */

#ifndef BAMFILTER_H
#define BAMFILTER_H

#include "../../include/headers.h"

class BamFilter {
public:
    BamFilter();
    BamFilter(const BamFilter& orig);
    
    static void bam2Fa(string infile, string outfile);
    static void filter(string infile, string outfile, bool is_forward, int min_matches);
    
    
    virtual ~BamFilter();
    
private:
    inline int getNumM (vector<CigarOp> &cigar) {
        int num_M = 0;
        for (int i=0; (int)cigar.size(); ++i) 
            if (cigar[i].Type=='M' || cigar[i].Type=='=' || cigar[i].Type=='X')
                num_M += cigar[i].Length;
        return num_M;
    }
};

#endif /* BAMFILTER_H */

