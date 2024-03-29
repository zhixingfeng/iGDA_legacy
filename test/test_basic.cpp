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


TEST_CASE("Test incomplete beta function") {
    //cout << "beta_cdf: " << 1 - beta_cdf(0.01, 2, 1) << endl;
    
}

TEST_CASE("Test binomial_pdf") {
    cout << "binomial_pdf: " << binomial_pdf(15,117,0.0828139) << endl;
    cout << "binomial_pdf: " << binomial_pdf(55,117,0.5) << endl;
    cout << "binomial_pdf: " << binomial_pdf(55,117,0.5) << endl;
}

