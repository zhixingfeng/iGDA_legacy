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
    PileupParser(ifstream * a_ptr_fs_pileupfile){ ptr_fs_pileupfile = a_ptr_fs_pileupfile; }
    virtual ~PileupParser();
    
    // basic operations 
    void setPileupFileStream (ifstream * a_ptr_fs_pileupfile) { ptr_fs_pileupfile = a_ptr_fs_pileupfile; }
        
    virtual bool readLine() = 0;
    
    virtual void calBaseFreq() = 0;
        
    // get results
    Pileup getPileup() {return data_Pileup;}
    BaseFreq getBaseFreq() {return data_BaseFreq;}
    string getSignature(){return signature;}

protected:    
    string signature;
    
    ifstream * ptr_fs_pileupfile;
    Pileup data_Pileup;
    BaseFreq data_BaseFreq;
    
};

#endif /* PILEUPPARSER_H */

