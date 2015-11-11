/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PileupParser.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 4:44 PM
 */

#ifndef PILEUPPARSER_H
#define PILEUPPARSER_H

#include "../../../include/stl.h"
struct PileUpLine
{
        int refID;
        int locus;
        bool is_ins;
        char refSeq;
        vector<string> readSeq;
        vector<int> readID;
        map<int, string> readSeq_group;
        int cvg;

        PileUpLine(){
                refID = -1;
                locus = -1;
                refSeq = 'X';
                cvg = 0;
        }
};

class PileupParser {
public:
    PileupParser();
    PileupParser(const PileupParser& orig);
    virtual ~PileupParser();
    
    virtual void readLines()=0;
private:

    vector<PileUpLine> data;
    
};

#endif /* PILEUPPARSER_H */

