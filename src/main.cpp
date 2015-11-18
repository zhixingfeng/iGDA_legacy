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
#include "../include/stl.h"
#include "../src/tool/tool.h"

#ifndef _UNITTEST

void print_usage() {

}

int main(int argc, char* argv[]) {
    int name;
    string salute;

    GetOpt_pp ops(argc, argv);

    ops >> Option('n', "name", name, 1);      /* the default name is 'world' */
    ops >> Option("salute", salute, "Hello");         /* the default salute is 'Hello' */

    std::cout << salute << " " << name << "!" << std::endl;

    return 0;
}

#else

int main(int argc, char* argv[]) {
    int result = Catch::Session().run( argc, argv );
    return result;
}

#endif

