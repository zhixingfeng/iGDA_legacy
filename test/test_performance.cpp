/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../include/catch.hpp"
#include "../include/headers.h"


TEST_CASE ("compare iteration of map vs vector","[hide]") {
    cout << "compare iteration of map vs vector:" << endl;
    
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

TEST_CASE("compare map and vector to store joint prob","[hide]") {
    
    cout << "compare map and vector to store joint prob:" << endl;
    
    
    vector<int> mol_id(10000, 0);
    for (int i=0; i<1000; i++) mol_id[i] = i;
    for (int i=1001; i<10000; i++) mol_id[i] = i + 10000;
    
    vector<int> mol_id_s(10000, 0);
    for (int i=0; i<1000; i++) mol_id_s[i] = i;
    for (int i=1001; i<10000; i++) mol_id_s[i] = i + 20000;
    
    int t_s, t_e;
    
    // create vector 
    t_s = clock();
    vector<string> jprob_vec(mol_id.back(), "X");
    for (int i=0; i<mol_id.size(); i++)
        jprob_vec[mol_id[i] - mol_id[0]] = "N";
    t_e = clock();
    cout << "vector create time: " << (t_e - t_s)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl;
    
    // access vector 
    t_s = clock();
    for (int i=0; i<mol_id_s.size(); i++) {
        if (mol_id_s[i] > jprob_vec.size() || mol_id_s[i] < mol_id[0]) continue;
        string rl = jprob_vec[mol_id_s[i] - mol_id[0]];
    }
    t_e = clock();
    cout << "vector access time: " << (t_e - t_s)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl;
    
    map<int, string> jprob_map;
    // create map
    t_s = clock();
    for (int i=0; i<mol_id.size(); i++)
        jprob_map[mol_id[i]] = "N";
    t_e = clock();
    cout << "map create time: " << (t_e - t_s)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl;
    
    // access map
    t_s = clock();
    for (int i=0; i<mol_id_s.size(); i++) {
        string rl = jprob_map[mol_id_s[i]];
    }
    t_e = clock();
    cout << "map access time: " << (t_e - t_s)/double(CLOCKS_PER_SEC)*1000 << " ms" << endl;
}