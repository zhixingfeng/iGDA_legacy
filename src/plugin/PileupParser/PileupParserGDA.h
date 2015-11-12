/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PileupParserGDA.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 6:56 PM
 */

#ifndef PILEUPPARSERGDA_H
#define PILEUPPARSERGDA_H

#include "PileupParser.h"

class PileupParserGDA : public PileupParser{
public:
    PileupParserGDA();
    PileupParserGDA(const PileupParserGDA& orig);
    virtual ~PileupParserGDA();
    
    void readLines(int nlines = 1);
    void calBaseFreq();
    
protected:
    void readLine();

};

#endif /* PILEUPPARSERGDA_H */

