/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iGDA.cpp
 * Author: zhixingfeng
 * 
 * Created on November 11, 2015, 4:08 PM
 */

#include "iGDA.h"

iGDA::iGDA() {
    // initialize pileupfile
    pileupfile = "";
    err_model_file = "";
    
    // initialize plugins
    ptr_PileupParser = NULL;
    ptr_ErrorModeler = NULL;
    ptr_PreCaller = NULL;
}

iGDA::iGDA(const iGDA& orig) {
    
}

iGDA::~iGDA() {
}

void iGDA::setErrorModeler(ErrorModeler* a_ErrorModeler) {
    if (ptr_PileupParser == NULL)
        throw runtime_error("PileupParser has not been setup yet.");
    ptr_ErrorModeler = a_ErrorModeler;
    ptr_ErrorModeler->setPileupParser(ptr_PileupParser);
}
void iGDA::setPreCaller(PreCaller* a_PreCaller) {
    if (ptr_PileupParser == NULL)
        throw runtime_error("ptr_PileupParser has not been setup yet.");
    if (ptr_ErrorModeler == NULL)
        throw runtime_error("ptr_ErrorModeler has not been setup yet.");
    
    ptr_PreCaller = a_PreCaller;
    ptr_PreCaller->setPileupParser(ptr_PileupParser);
    ptr_PreCaller->setErrorModeler(ptr_ErrorModeler);
}

void iGDA::trainErrorModel(string err_model_file) {
    // check pileupfile and plugins
    if (pileupfile == "")  throw runtime_error("error in iGDA::run: pileupfile has not been setup yet.");
    if (this->ptr_PileupParser == NULL) throw runtime_error("PileupParser has not been setup yet.");
    if (this->ptr_ErrorModeler == NULL) throw runtime_error("ErrorModeler has not been setup yet.");
        
    // train background model error rate 
    ptr_ErrorModeler->setPileupFile(pileupfile);
    ptr_ErrorModeler->train(1,1);
    ptr_ErrorModeler->save(err_model_file);
    ptr_ErrorModeler->calErrorRateStat();
    ptr_ErrorModeler->save_mean_err(err_model_file + ".mean");
}

void iGDA::loadErrorModel(string a_err_model_file) {
    if (ptr_PreCaller == NULL) 
        throw runtime_error("Error in iGDA::loadErrorModel: ptr_PreCaller is NULL");
    
    ptr_PreCaller->loadErrorModel(a_err_model_file);
    err_model_file = a_err_model_file;
}

void iGDA::preCall(string out_prefix, int min_cvg, int min_cvg_ctrl, int len_l, int len_r) {
    if (pileupfile == "")  
        throw runtime_error("error in iGDA::preCall: pileupfile has not been setup yet.");
    if (err_model_file == "")
        throw runtime_error("error in iGDA::preCall: err_model_file has not been setup yet.");
    verifyPlugin();
    
    ptr_PreCaller->setPileupfile(pileupfile);
    ptr_PreCaller->callVar(min_cvg, min_cvg_ctrl, len_l, len_r);
    ptr_PreCaller->writeVar(out_prefix);
    
}

void iGDA::run(){
    // check if pileupfile is set
    if (pileupfile == "") 
        throw runtime_error("error in iGDA::run: pileupfile has not been setup yet.");
    
    // check plugins
    verifyPlugin();
}


SeqFreq iGDA::getSeqFreq(){
    throw "run not implemented yet"; 
}

void iGDA::verifyPlugin() {
    if (this->ptr_PileupParser == NULL)
        throw runtime_error("PileupParser has not been setup yet.");
    if (this->ptr_ErrorModeler == NULL)
        throw runtime_error("ErrorModeler has not been setup yet.");
    if (this->ptr_PreCaller == NULL)
        throw runtime_error("PreCaller has not been setup yet.");
    
}