/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BamFilter.h
 * Author: zhixingfeng
 *
 * Created on December 29, 2015, 11:06 PM
 */

#ifndef BAMFILTER_H
#define BAMFILTER_H

#include <api/BamReader.h>
#include <api/BamWriter.h>

using namespace BamTools;
class BamFilter {
public:
    BamFilter();
    BamFilter(const BamFilter& orig);
    
    void test(){BamReader reader;}
    
    virtual ~BamFilter();
private:

};

#endif /* BAMFILTER_H */

