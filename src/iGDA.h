/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iGDA.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 4:08 PM
 */

#ifndef IGDA_H
#define IGDA_H
#include "../include/stl.h"

// SeqFreq is used for store the output of iGDA. 
// The most important output is joint probability of sequences.
struct SeqFreq{

};


class iGDA {
public:
    iGDA();
    iGDA(const iGDA& orig);
    virtual ~iGDA();
    
    void run();
    void setPileupFile(const string &pileupfile);
    
private:
    
};

#endif /* IGDA_H */

