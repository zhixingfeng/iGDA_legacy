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

#include "../../../include/headers.h"


class PileupParser {
public:
    
    PileupParser();
    PileupParser(const PileupParser& orig);
    virtual ~PileupParser();
    
    virtual void readLines(int nlines = 1)=0;

    string getSignature(){return signature;}

protected:
    virtual void readLine()=0;
    
protected:    
    vector<Pileup> data;
    string signature;
};

#endif /* PILEUPPARSER_H */

