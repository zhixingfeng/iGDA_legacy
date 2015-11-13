/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ErrorModeler.h
 * Author: zhixingfeng
 *
 * Created on November 12, 2015, 10:47 AM
 */

#ifndef ERRORMODELER_H
#define ERRORMODELER_H

#include "../../../include/headers.h"
#include "../PileupParser/PileupParser.h"
#include "../PileupParser/PileupParserGDA.h"

class ErrorModeler {
public:
    ErrorModeler();
    ErrorModeler(const ErrorModeler& orig);
    virtual ~ErrorModeler();
    
    string getSignature(){return signature;}
    
    // 
protected:
    
    string signature;
    
    // plugins
    PileupParser * ptr_PileupParser;
};

#endif /* ERRORMODELER_H */

