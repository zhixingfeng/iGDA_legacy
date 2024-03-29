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

int PileupParserGDA::getMaxMolID(string pileupfile) {
    int max_mol_id = -1;
    ifstream fs_pileupfile; open_infile(fs_pileupfile, pileupfile);
    this->setPileupFileStream(&fs_pileupfile);
    while(true) {
        this->readLine();
        if (fs_pileupfile.eof()) break;
        
        Pileup pu = this->getPileup();
        
        if (pu.readID.size() > 0)
            if (pu.readID.back() > max_mol_id) max_mol_id = pu.readID.back();
        if (pu.readID_ins.size() > 0)
            if (pu.readID_ins.back() > max_mol_id) max_mol_id = pu.readID_ins.back();
    }
    fs_pileupfile.close();
    if (max_mol_id < 0)
        throw runtime_error("Error in PileupParserGDA::getMaxMolID(): fail to get max mol ID.");
    
    return max_mol_id ;
}

bool PileupParserGDA::checkFormat(string pileupfile) {
    ifstream fs_pileupfile; open_infile(fs_pileupfile, pileupfile);
    int prev_refID = -1;
    int prev_locus = 0;
    bool is_start;
    while(true) {
        string line_ins;
        string line;
        getline(fs_pileupfile, line_ins);
        getline(fs_pileupfile, line);
        if (fs_pileupfile.eof()) break;
        vector<string> line_ins_list = split(line_ins, '\t');
        vector<string> line_list = split(line, '\t');
        
        // check number of columns
        if ((line_ins_list.size()!=4 && line_ins_list.size()!=6) || (line_list.size()!=4 && line_list.size()!=6)){
            cerr << "number of columns is not 4 or 6" << endl;
            return false;
        }
        
        // check if two lines match 
        int refID_ins = atoi(line_ins_list[0].c_str());
        int refID = atoi(line_list[0].c_str());
        int locus_ins = atoi(line_ins_list[1].substr(1,line_ins_list[1].size()-1).c_str());
        int locus = atoi(line_list[1].c_str());
        if (refID_ins != refID || locus_ins != locus) {
            cerr << "two lines not match" << endl;
            return false;
        }
        
        // check if the current locus is the start locus
        if (refID != prev_refID)
            is_start = true;
        else
            is_start = false;
        
        // check if locus start from 1
        if (is_start && locus!=1) {
            cerr << "chr " << refID << ": locus is not start from 1" << endl;
            return false;
        }
        
        // check if locus is continous 
        if (!is_start && locus != prev_locus + 1) {
            cerr << "chr " << refID <<  ", " << locus << ": locus is not continous" << endl;
            return false;
        }
        
        // check if molecule number is increasing
        if (line_ins_list.size() == 6) {
            vector<string> id_list = split(line_ins_list[5],',');
            for (int i=0; i<(int)(id_list.size()-1); i++) {
                if (atoi(id_list[i].c_str()) >= atoi(id_list[i+1].c_str())){
                    cerr << "chr " << refID <<  ", " << locus << "(ins): molecule ID is not increasing." << endl;
                    return false;
                }
            }
        }
        
        if (line_list.size() == 6) {
            vector<string> id_list = split(line_list[5],',');
            for (int i=0; i<(int)(id_list.size()-1); i++) {
                if (atoi(id_list[i].c_str()) >= atoi(id_list[i+1].c_str())){
                    cerr << "chr " << refID <<  ", " << locus << ": molecule ID is not increasing." << endl;
                    return false;
                }
            }
        }
        
        prev_refID = refID;
        prev_locus = locus;
    }
    fs_pileupfile.close();
    
    return true;
}
