/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: zhixingfeng
 *
 * Created on November 11, 2015, 1:50 PM
 */


#define CATCH_CONFIG_RUNNER
#include "../include/catch.hpp"
#include "../src/tool/tool.h"
#include "iGDA.h"
#include "util/BamFilter.h"

#ifndef _UNITTEST

using namespace TCLAP;

void print_usage() {
    cout << "Usage: igda [mode]" << endl;
    cout << "[mode] is one of the following:" << endl << endl;
    cout << "train: train background model using known homogeneous data." << endl;
    cout << "precall: detect low frequency variants" << endl;
    cout << "filter: filter bam files." << endl;
    cout << endl << "type igda [mode] to print usage of each mode." << endl;
}

void print_usage_train() {
    cout << "igda train pileupfile outfile" << endl;
}


int main(int argc, char* argv[]) {
try{
    if (argc == 1) { print_usage(); return 0; }
    
    string cmdname = "igda "; cmdname += argv[1];
    vector<string> argv2;
    argv2.push_back(cmdname);
    for (int i=2; i<argc; i++){
        argv2.push_back(argv[i]);
    }
    
    
    iGDA gda;
    PileupParserGDA obj_PileupParserGDA;
    ErrorModelerHomo obj_ErrorModelerHomo; 
    PreCallerSingle obj_PreCallerSingle;
    PreCallerMultiple obj_PreCallerMultiple;
    
    if (argc >= 2) {
        if (strcmp(argv[1],"train")==0) {
            if ( argc == 2 ) { print_usage_train(); return 0; }
            if ( argc != 4 ) {
                cerr << "incorrect usage of igda train." << endl;
                print_usage_train();
                return 1;
            }
            string infile = argv[2];
            string outfile = argv[3];
                    
            gda.setPileupFile(infile);
            gda.setPileupParser(& obj_PileupParserGDA);
            gda.setErrorModeler(& obj_ErrorModelerHomo);
            
            gda.trainErrorModel(outfile);
            return 0;
        }
        if (strcmp(argv[1],"precall")==0) {
            try {
                CmdLine cmd("iGDA", ' ', "0.1");
                ValueArg<int> mArg("m","method","method of pre-calling. 0: single locus, 1: multiple loci", false , 1, "method", cmd);
                ValueArg<int> vArg("v","cvg","minimum coverage, default is 1", false , 1, "cvg", cmd);
                ValueArg<int> cArg("c","cvg_ctrl","minimum coverage in control data, default is 1", false , 1, "cvg_ctrl", cmd);
                ValueArg<int> lArg("l","left_len","length of left side context, default is 1", false , 1, "left_len", cmd);
                ValueArg<int> rArg("r","right_len","length of right side context, default is 1", false , 1, "right_len", cmd);
                
                
                UnlabeledValueArg<string> pileupfileArg("pileupfile", "path of pileup file", true, "", "pileupfile", cmd);
                UnlabeledValueArg<string> errfileArg("errfile", "path of error model file", true, "", "errfile", cmd);
                UnlabeledValueArg<string> outprefixArg("outprefix", "prefix of output files", true, "", "outprefix", cmd);
                
                cmd.parse(argv2);
                
                gda.setPileupFile(pileupfileArg.getValue());
                        
                gda.setPileupParser(& obj_PileupParserGDA);
                gda.setErrorModeler(& obj_ErrorModelerHomo);
                        
                switch (mArg.getValue()) {
                    case 0:
                        cout << "precall using single locus method." << endl;
                        gda.setPreCaller(& obj_PreCallerSingle);
                        gda.loadErrorModel(errfileArg.getValue());
                        gda.preCall(outprefixArg.getValue(), vArg.getValue(), cArg.getValue(), lArg.getValue(), rArg.getValue());
                        break;
                    case 1:
                        cout << "precall using multiple loci method." << endl;
                        gda.setPreCaller(& obj_PreCallerMultiple);
                        gda.loadErrorModel(errfileArg.getValue());
                        gda.preCall(outprefixArg.getValue(), vArg.getValue(), cArg.getValue(), lArg.getValue(), rArg.getValue());
                        break;
                    default:
                        cerr << "Error: Invalid argument. -m should be 0 or 1" << endl;
                        return 1;
                }
            }catch(ArgException &e) {
                cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
            }
            return 0;
        }
        if (strcmp(argv[1],"filter")==0) {
            try {
                CmdLine cmd("iGDA", ' ', "0.1");
                SwitchArg bam2faArg("t", "bam2fa", "convert bam to fasta", cmd, false);
                
                UnlabeledValueArg<string> infileArg("infile", "path of input file", true, "", "infile", cmd);
                UnlabeledValueArg<string> outfileArg("outfile", "path of output file", true, "", "outfile", cmd);
                
                cmd.parse(argv2);
                
                if (bam2faArg.getValue()) {
                    BamFilter::bam2Fa( infileArg.getValue(), outfileArg.getValue() );
                    return 0;
                }
                
                if (infileArg.getValue()!="" && outfileArg.getValue()!="")
                    cerr << "Error: Invalid argument. type \"igda filter -h\"" << endl;
               
            }catch(ArgException &e) {
                cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
            }
            return 0;
            
        }
    }
     
    return 0;
}
catch(const std::overflow_error& e) {
    cerr << "overflow_error: " << e.what() << endl;
} catch(const std::runtime_error& e) {
    cerr << "runtime_error: " << e.what() << endl;
} catch(const std::exception& e) {
    cerr << "expection: " << e.what() << endl;
} catch(...) {
    
}

}

#else

using namespace boost::filesystem;

int main(int argc, char* argv[]) {
    if (!exists("./results"))
        create_directory("./results");
    int result = Catch::Session().run( argc, argv );
    return result;
}

#endif

