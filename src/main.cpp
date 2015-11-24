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

#ifndef _UNITTEST

void print_usage() {
    cout << "Usage: igda [mode]" << endl;
    cout << "[mode] is one of the following:" << endl << endl;
    cout << "train: train background model using known homogeneous data." << endl;
    cout << "detect: detect low frequency variants" << endl;
    cout << endl << "type igda [mode] to print usage of each mode.";
}

void print_usage_train() {
    cout << "igda train pileupfile outfile" << endl;
}

int main(int argc, char* argv[]) {
    if (argc == 1) { print_usage(); return 0; }
       
    GetOpt_pp ops(argc, argv);

    PileupParserGDA obj_PileupParser;
    ErrorModelerHomo obj_ErrorModeler; 
    PreCallerSingle obj_PreCaller;
    
    if (argc >= 2) {
        if (strcmp(argv[1],"train")==0) {
            if ( argc == 2 ) { print_usage_train(); return 0; }
            if ( argc != 4 ) 
                throw runtime_error("incorrect usage of igda train.");
            string infile = argv[2];
            string outfile = argv[3];
            
            iGDA gda;
            gda.setPileupFile(infile);
            gda.setPileupParser(& obj_PileupParser);
            gda.setErrorModeler(& obj_ErrorModeler);
            gda.setPreCaller(& obj_PreCaller);
            
            gda.trainErrorModel(outfile);
            
        }
    }
    //ops >> Option('n', "name", name, 1);      /* the default name is 'world' */
    //ops >> Option("salute", salute, "Hello");         /* the default salute is 'Hello' */

    //std::cout << salute << " " << name << "!" << std::endl;

    return 0;
}

#else

int main(int argc, char* argv[]) {
    int result = Catch::Session().run( argc, argv );
    return result;
}

#endif

