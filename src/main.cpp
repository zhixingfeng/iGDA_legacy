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

#ifndef _UNITTEST

int main(int argc, char* argv[]) {
    
    return 0;
}

#else

int main(int argc, char* argv[]) {
    int result = Catch::Session().run( argc, argv );
    return result;
}

#endif

