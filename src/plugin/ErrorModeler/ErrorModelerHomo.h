/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ErrorModelerHomo.h
 * Author: zhixingfeng
 *
 * Created on November 13, 2015, 12:31 PM
 */

#ifndef ERRORMODELERHOMO_H
#define ERRORMODELERHOMO_H

#include "ErrorModeler.h"

class ErrorModelerHomo : public ErrorModeler {
public:
    ErrorModelerHomo();
    ErrorModelerHomo(const ErrorModelerHomo& orig);
    virtual ~ErrorModelerHomo();

    void train(int left = 1, int right = 1);
    pair<string, string> getLocalContext(int refID, int locus, int left, int right); 
};

#endif /* ERRORMODELERHOMO_H */

