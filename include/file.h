/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   file.h
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 5:50 PM
 */

#ifndef FILE_H
#define FILE_H
#include <fstream>
#include <string>
using namespace std;
inline ifstream open_infile(string filename){
    ifstream fs_infile(filename.c_str());
    if (!fs_infile.is_open()){
        string err_msg = "Error: fail to open " + filename;
        throw runtime_error(err_msg);
    }
    return fs_infile;
}

inline ofstream open_outfile(string filename){
    ofstream fs_outfile(filename.c_str());
    if (!fs_outfile.is_open()){
        string err_msg = "Error: fail to open " + filename;
        throw runtime_error(err_msg);
    }
    return fs_outfile;
}

#endif /* FILE_H */

