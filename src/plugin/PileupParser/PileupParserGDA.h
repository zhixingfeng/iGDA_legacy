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
    PileupParserGDA(ifstream * a_ptr_fs_pileupfile) : PileupParser(a_ptr_fs_pileupfile) { }
    virtual ~PileupParserGDA();
    
    static bool checkFormat(string pileupfile); 
    
    bool readLine();
    
    void calBaseFreq();
    
    RefGenome getRefGenome (string pileupfile);
    
protected:
    
    void parseLine(string & line, Pileup & obj_Pileup, bool is_ins);

};

#endif /* PILEUPPARSERGDA_H */

