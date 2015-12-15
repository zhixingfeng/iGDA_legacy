/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../include/catch.hpp"
#include "../include/headers.h"

TEST_CASE("Test operation of sqrt(-1)") {
    REQUIRE(sqrt(-1) != sqrt(-1));
    REQUIRE(INFINITY + 1 == INFINITY); 
    REQUIRE(INFINITY == INFINITY);
    //REQUIRE(1.0/0 == INFINITY);
    REQUIRE(NAN != NAN);
    REQUIRE(std::isnan(NAN));
}

TEST_CASE("Test isnan()") {
    REQUIRE(std::isnan(sqrt(-1)) == true);
    REQUIRE(std::isinf(1.0/0.0) == true);
    REQUIRE(std::isnan(1) == false);
}

TEST_CASE("Test query non-existing key of map") {
    map <string, vector<double> > x;
    REQUIRE(x["nonexistings"].size() == 0);
    
   
    map<string, double> y;
    REQUIRE(y["nonexistings"] == 0);
    map<string, int> z;
    REQUIRE(z["nonexistings"] == 0);
}

TEST_CASE ("Test EPS") {
    REQUIRE(EPS == 1e-16);
}


// performance test
TEST_CASE ("compare iteration of map vs vector","[hide]") {
    int B = 1000;
    map<int, map<int, double> > x;
    vector<vector<double> > y;
    
    int t_s, t_e;
    
    // insertion to map
    t_s = clock();
    for (int i=0; i<B; i++)
        for (int j=0; j<B; j++)
            x[i][j] = i+j;
    t_e = clock();
    cout << "map insertion time: " << (t_e - t_s)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl;
    
    // insertion to vector
    t_s = clock();
    for (int i=0; i<B; i++){
        vector<double> tmp;
        for (int j=0; j<B; j++)
            tmp.push_back(i + j);
        y.push_back(tmp);
    }
    t_e = clock();
    cout << "vector insertion time: " << (t_e - t_s)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl;
    
    // insertion to vector pre-located
    t_s = clock();
    vector<vector<double> > yy(B, vector<double>(B,0));
    //cout << yy.size() << ',' << yy[0].size() << endl;
    for (int i=0; i<B; i++)
        for (int j=0; j<B; j++)
            yy[i][j] = i + j;
    
    t_e = clock();
    cout << "vector insertion time (pre-located): " << (t_e - t_s)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl;
    
    // access map
    t_s = clock();
    for (int i=0; i<B; i++)
        for (int j=0; j<B; j++)
            double z = x[i][j];
    t_e = clock();
    cout << "map access time: " << (t_e - t_s)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl;
 
    // access vector
    t_s = clock();
    for (int i=0; i<B; i++)
        for (int j=0; j<B; j++)
            double z = y[i][j];
    t_e = clock();
    cout << "vector access time: " << (t_e - t_s)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl;
    
    
}





