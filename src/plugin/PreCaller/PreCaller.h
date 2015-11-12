/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreCaller.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 4:54 PM
 */

#ifndef PRECALLER_H
#define PRECALLER_H
#include "../../../include/stl.h"

class PreCaller {
public:
    PreCaller();
    PreCaller(const PreCaller& orig);
    virtual ~PreCaller();
    
    string getSignature(){return signature;}
protected:
    string signature;
};

#endif /* PRECALLER_H */

