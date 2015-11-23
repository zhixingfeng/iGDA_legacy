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
    
    //data_BaseFreq(data_Pileup);
    data_BaseFreq.refID = data_Pileup.refID;
    data_BaseFreq.locus = data_Pileup.locus;
    data_BaseFreq.refSeq = data_Pileup.refSeq;
    data_BaseFreq.cvg = data_Pileup.cvg;
    data_BaseFreq.cvg_ins = data_Pileup.cvg_ins;
    
    
    map<string, int>::iterator it;
    
    // get freq of insertion
    for (int i=0; i<(int) data_Pileup.readSeq_ins.size(); i++) {
        string cur_seq = NtSeq2Str(data_Pileup.readSeq_ins[i]);
        it = data_BaseFreq.freq_ins.find( cur_seq );
        if ( it == data_BaseFreq.freq_ins.end() )
            data_BaseFreq.freq_ins[cur_seq] = 1;
        else 
            data_BaseFreq.freq_ins[cur_seq] ++;
            
    }
    
    // get freq of match
    for (int i=0; i<(int) data_Pileup.readSeq.size(); i++) {
        string cur_seq = NtSeq2Str(data_Pileup.readSeq[i]);
        it = data_BaseFreq.freq.find( cur_seq );
        if ( it == data_BaseFreq.freq.end() )
            data_BaseFreq.freq[cur_seq] = 1;
        else 
            data_BaseFreq.freq[cur_seq] ++;
            
    }
    
    // get prob of insertion
    for (it=data_BaseFreq.freq_ins.begin(); it!= data_BaseFreq.freq_ins.end(); it++)
        data_BaseFreq.prob_ins[it->first] = double(it->second) / data_BaseFreq.cvg;
    
    // get prob of match
    for (it=data_BaseFreq.freq.begin(); it!= data_BaseFreq.freq.end(); it++)
        data_BaseFreq.prob[it->first] = double(it->second) / data_BaseFreq.cvg;
}


RefGenome PileupParserGDA::getRefGenome(string pileupfile) {
    RefGenome refgenome;
    ifstream cur_fs_pileupfile;
    open_infile(cur_fs_pileupfile, pileupfile);
    while(true) {
        string cur_line_ins;
        string cur_line;
        
        getline(cur_fs_pileupfile, cur_line_ins);
        getline(cur_fs_pileupfile, cur_line);
    
        if (cur_fs_pileupfile.eof()) break;
        
        vector<string> buf_ins = split(cur_line_ins, '\t');
        vector<string> buf = split(cur_line, '\t');
        
        if ((buf.size()!=4 && buf.size()!=6) || (buf_ins.size()!=4 && buf_ins.size()!=6)) 
            throw runtime_error ("Error in PileupParserGDA::getRefGenome : incorrect buf size.");
        if (buf_ins[1][0] != '_' || buf[1][0] == '_')
            throw runtime_error ("Error in PileupParserGDA::getRefGenome : incorrect pileupfile format.");
        
        refgenome[ atoi(buf[0].c_str()) ].push_back(buf[2][0]);
        
    }
    cur_fs_pileupfile.close();
    return refgenome;
}