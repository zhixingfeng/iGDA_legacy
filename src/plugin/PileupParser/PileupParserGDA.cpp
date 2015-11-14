/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PileupParserGDA.cpp
 * Author: zhixingfeng
 * 
 * Created on November 11, 2015, 6:56 PM
 */

#include "PileupParserGDA.h"

PileupParserGDA::PileupParserGDA() {
    signature = "PileupParserGDA";
}

PileupParserGDA::PileupParserGDA(const PileupParserGDA& orig) {
}

PileupParserGDA::~PileupParserGDA() {
}



bool PileupParserGDA::readLine() {
    if (ptr_fs_pileupfile == NULL)
        throw runtime_error("Error in PileupParserGDA::readLine: ptr_fs_pileupfile has not been setup yet.");
    data_Pileup.clear();            
          
            
    string cur_line_ins;
    string cur_line;
    vector<string> buf;
    
    getline(*ptr_fs_pileupfile, cur_line_ins);
    getline(*ptr_fs_pileupfile, cur_line);
    
    if (ptr_fs_pileupfile->eof()) return true;
    
    
    // parse insertion
    this->parseLine(cur_line_ins, data_Pileup, true);
    
    // parse match
    this->parseLine(cur_line, data_Pileup, false);
    
    return false;
}

void PileupParserGDA::parseLine(string & line, Pileup &obj_Pileup, bool is_ins) {
    // split the line
    vector<string> buf = split(line,'\t');
    if (buf.size()!=4 && buf.size()!=6) 
        throw runtime_error ("Error in PileupParserGDA::parseLine : incorrect buf size.");
    
    // test if is_ins set correctly
    if ((buf[1][0]=='_') != is_ins) 
        throw runtime_error ("Error in PileupParserGDA::parseLine : is_ins is not correct.");
    
    // parse
    obj_Pileup.refID = atoi(buf[0].c_str());
    obj_Pileup.locus = is_ins ? atoi(buf[1].substr(1,buf[1].size()-1).c_str()) : atoi(buf[1].c_str());    
    obj_Pileup.refSeq = buf[2][0];    
    
    if (is_ins)
        obj_Pileup.cvg_ins = atoi(buf[3].c_str());
    else
        obj_Pileup.cvg = atoi(buf[3].c_str());
    
    if (buf.size() == 4) return;
    
    if (is_ins) {
        obj_Pileup.readSeq_ins = split_NtSeq(buf[4], ',', true);
        obj_Pileup.readID_ins = split_int(buf[5], ',');
    }else {
        obj_Pileup.readSeq = split_NtSeq(buf[4], ',', true);
        obj_Pileup.readID = split_int(buf[5], ',');
    }
     
}

void PileupParserGDA::calBaseFreq() {
    data_BaseFreq.clear();
}
