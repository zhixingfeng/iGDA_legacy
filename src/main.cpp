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

void print_usage_precall() {
    cout << "igda precall -m <method> pileupfile error_model_file out_prefix" << endl;
    cout << "-m 0 : single locus method" << endl;
    cout << "-m 1 : multiple loci method" << endl;
}


int main(int argc, char* argv[]) {
    if (argc == 1) { print_usage(); return 0; }
       
    GetOpt_pp ops(argc, argv);

    PileupParserGDA obj_PileupParserGDA;
    ErrorModelerHomo obj_ErrorModelerHomo; 
    PreCallerSingle obj_PreCallerSingle;
    
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
            
            iGDA gda;
            gda.setPileupFile(infile);
            gda.setPileupParser(& obj_PileupParserGDA);
            gda.setErrorModeler(& obj_ErrorModelerHomo);
            gda.setPreCaller(& obj_PreCallerSingle);
            
            gda.trainErrorModel(outfile);
        }
        if (strcmp(argv[1],"precall")==0) {
            if ( argc == 2 ) { print_usage_precall(); return 0; }
            /*if ( argc != 5 ) {
                cerr << "incorrect usage of igda precall." << endl;
                print_usage_precall();
                return 1;
            }*/
            int m;
            ops >> Option('m', "method", m, 1);
            cout << m << endl;
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

