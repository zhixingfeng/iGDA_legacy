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
    
    // basic operations 
    void setPileupFileStream (fstream * a_ptr_fs_pileupfile) { ptr_fs_pileupfile = a_ptr_fs_pileupfile; }
    virtual void readLines(int nlines = 1)=0;
    virtual void calBaseFreq() = 0;

    // get results
    vector<Pileup> getPileup() {return data_Pileup;}
    vector<BaseFreq> getBaseFreq() {return data_BaseFreq;}
    string getSignature(){return signature;}

protected:
    virtual void readLine()=0;
    
protected:    
    fstream * ptr_fs_pileupfile;
    vector<Pileup> data_Pileup;
    vector<BaseFreq> data_BaseFreq;
    string signature;
};

#endif /* PILEUPPARSER_H */

