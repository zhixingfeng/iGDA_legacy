/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreCallerSingle.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 5:17 PM
 */

#ifndef PRECALLERSINGLE_H
#define PRECALLERSINGLE_H

#include "PreCaller.h"
class PreCallerSingle : public PreCaller{
public:
    PreCallerSingle();
    PreCallerSingle(const PreCallerSingle& orig);
    virtual ~PreCallerSingle();
    
    void callVar();
private:

};

#endif /* PRECALLERSINGLE_H */

