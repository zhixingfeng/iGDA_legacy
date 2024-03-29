/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../include/catch.hpp"
#include "../src/plugin/plugin.h"
#include "../src/tool/tool.h"



TEST_CASE("Test default constructor of VarStat", "[PreCaller]") {
    VarStat varstat;
    REQUIRE(varstat.cvg == -1);
    REQUIRE(varstat.cvg_ctrl == -1);
    REQUIRE(std::isnan(varstat.effect_size));
    REQUIRE(varstat.locus == -1);
    REQUIRE(std::isnan(varstat.p_value));
}

TEST_CASE("Test constructor of VarStat", "[PreCaller]") {
    VarStat varstat(1.98, 0.01, 10, 2847, 3625);
    REQUIRE(varstat.cvg == 10);
    REQUIRE(varstat.cvg_ctrl == 2847);
    REQUIRE(varstat.effect_size == 1.98);
    REQUIRE(varstat.locus == 3625);
    REQUIRE(varstat.p_value == 0.01);
    
    vector<VarStat> varstat_vec;
    varstat_vec.push_back(VarStat(1.98, 0.01, 10, 2847, 3625));
    REQUIRE(varstat_vec[0].cvg == 10);
    REQUIRE(varstat_vec[0].cvg_ctrl == 2847);
    REQUIRE(varstat_vec[0].effect_size == 1.98);
    REQUIRE(varstat_vec[0].locus == 3625);
    REQUIRE(varstat_vec[0].p_value == 0.01);
}



TEST_CASE("Test PreCaller setup resources", "[PreCaller]") {
    PreCallerSingle obj_PreCallerSingle;
    
    PileupParserGDA obj_PileupParserGDA;
    ErrorModelerHomo obj_ErrorModelerHomo;
    
    //REQUIRE_THROWS(obj_PreCallerSingle.setPileupParser(& obj_PileupParserGDA));
    obj_PreCallerSingle.setPileupfile("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup");
    REQUIRE_THROWS(obj_PreCallerSingle.setErrorModeler(& obj_ErrorModelerHomo));
    
    REQUIRE_NOTHROW( obj_PreCallerSingle.setPileupParser(& obj_PileupParserGDA) );
    REQUIRE_NOTHROW( obj_PreCallerSingle.setErrorModeler(& obj_ErrorModelerHomo)  );   
}

TEST_CASE("Test PreCallerSingle callVar()", "[PreCaller]") {
    PreCallerSingle obj_PreCallerSingle;
    
    PileupParserGDA obj_PileupParserGDA;
    ErrorModelerHomo obj_ErrorModelerHomo;
    
    obj_PreCallerSingle.setPileupfile("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup");
    obj_PreCallerSingle.setPileupParser(& obj_PileupParserGDA);
    obj_PreCallerSingle.setErrorModeler(& obj_ErrorModelerHomo);
    
    obj_PreCallerSingle.loadErrorModel("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.err");
    
    obj_PreCallerSingle.callVar();
    
    obj_PreCallerSingle.writeVar("./results/mixed_MSSA_78_ratio_0.05_B_1.bam");
    
}

TEST_CASE("Test PreCaller calStat()", "[PreCaller]") {
    PreCallerSingle obj_PreCallerSingle;
    map<string, double> prob;
    map<string, double> prob_ctrl;
    prob["A"] = 1e-10;
    prob["C"] = 0.15;
    prob["G"] = 0.8;
    prob["T"] = 0.05 - 1e-10;
    prob["N"] = 0.01;
            
    prob_ctrl["A"] = 0;
    prob_ctrl["C"] = 0.04;
    prob_ctrl["G"] = 0.86;
    prob_ctrl["T"] = 0.99e-16;
    prob_ctrl["-"] = 0.1;
    
    VarStat stat (NAN, NAN, 104,1300,74658);
    obj_PreCallerSingle.calStat(stat, prob, prob_ctrl);
    REQUIRE(stat.cvg == 104);
    REQUIRE(stat.cvg_ctrl == 1300);
    REQUIRE(stat.locus == 74658);
    REQUIRE(stat.effect_size == Approx(log(0.15/0.04)));
    
    REQUIRE(std::isnan(stat.log_prob_ratio["A"]));
    REQUIRE(stat.log_prob_ratio["C"] == Approx(log(0.15 / 0.04)));
    REQUIRE(stat.log_prob_ratio["G"] == Approx(log(0.8 / 0.86)));
    REQUIRE(std::isnan(stat.log_prob_ratio["T"]));
    REQUIRE(std::isnan(stat.log_prob_ratio["N"]));    
}


TEST_CASE("test PreCallerMultiple::callVar()","[hide]") {
    PreCallerMultiple obj_PreCallerMultiple;
    
    PileupParserGDA obj_PileupParserGDA;
    ErrorModelerHomo obj_ErrorModelerHomo;
    obj_PreCallerMultiple.setPileupParser(& obj_PileupParserGDA);
    obj_PreCallerMultiple.setErrorModeler(& obj_ErrorModelerHomo);
    
    obj_PreCallerMultiple.setOutprefix("./results/mixed_MSSA_78_ratio_0.05_B_1.bam");
    obj_PreCallerMultiple.setPileupfile("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup");
    obj_PreCallerMultiple.loadErrorModel("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.err");
    
    //obj_PreCallerMultiple.setOutprefix("./results/test_scanBuf");
    //obj_PreCallerMultiple.setPileupfile("./data/test_scanBuf.pileup");
    //obj_PreCallerMultiple.loadErrorModel("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.err");
    
    obj_PreCallerMultiple.callVar(1, 1, 1, 1);
}

TEST_CASE("test PreCallerMultiple::calCondProb()","[PreCallerMultiple][hide]") {
    PreCallerMultiple obj_PreCallerMultiple;
    
    PileupParserGDA obj_PileupParserGDA;
    ErrorModelerHomo obj_ErrorModelerHomo;
    
    obj_PreCallerMultiple.setPileupfile("./data/test_scanBuf.pileup");
    obj_PreCallerMultiple.setPileupParser(& obj_PileupParserGDA);
    obj_PreCallerMultiple.setErrorModeler(& obj_ErrorModelerHomo);
    
    // using default read length, which is much larger than genome size
    obj_PreCallerMultiple.calCondProb("./results/test_scanBuf.cprob");
    
    // set read length to 4
    obj_PreCallerMultiple.setReadLen(4);
    obj_PreCallerMultiple.calCondProb("./results/test_scanBuf_readlen_4.cprob");
    
    // compare the results
    hashwrapper *myWrapper = new md5wrapper();
    REQUIRE(myWrapper->getHashFromFile("./results/test_scanBuf.cprob.sorted") == myWrapper->getHashFromFile("./results/test_scanBuf_readlen_4.cprob.sorted"));
    
    
    // test larger pileupfile 
    obj_PreCallerMultiple.setPileupfile("./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup");
    obj_PreCallerMultiple.setReadLen(10000);
    obj_PreCallerMultiple.calCondProb("./results/mixed_MSSA_78_ratio_0.05_B_1.bam.cprob");
    
    obj_PreCallerMultiple.setReadLen(1000);
    obj_PreCallerMultiple.calCondProb("./results/mixed_MSSA_78_ratio_0.05_B_1.bam_readlen_1000.cprob");
    
    REQUIRE(myWrapper->getHashFromFile("./results/mixed_MSSA_78_ratio_0.05_B_1.bam.cprob.sorted")==
            myWrapper->getHashFromFile("./results/mixed_MSSA_78_ratio_0.05_B_1.bam_readlen_1000.cprob.sorted") );
    
    delete myWrapper;
}

TEST_CASE("test PreCallerMultiple::readCondProb()") {
    string cprobfile = "./data/test_scanBuf.cprob.sorted";
    string outifle = "./results/test_scanBuf.cprob.sorted.loaded";
    
    ifstream fs_cprobfile; open_infile(fs_cprobfile, cprobfile);
    ofstream fs_outfile; open_outfile(fs_outfile, outifle);
    PreCallerMultiple obj_PreCallerMultiple;
    
    while (true) {
        int refID, locus_l, locus_r, mcvg;
        string refSeq;
        JointProb cur_cprob;
        obj_PreCallerMultiple.readCondProb(fs_cprobfile, refID, locus_l, locus_r, refSeq, mcvg, cur_cprob);
        if (fs_cprobfile.eof()) break;
        fs_outfile << refID << '\t' << locus_l << '\t' << locus_r << '\t' << cur_cprob.cvg << '\t';
        fs_outfile << refSeq << '\t' << mcvg << '\t' << cur_cprob << '\t';
        if (cur_cprob.freq_m.size() >0)
            fs_outfile << cur_cprob.freq_m << '\t';
        else
            fs_outfile << "NA" << '\t';
        if (cur_cprob.freq_i.size() >0)
            fs_outfile << cur_cprob.freq_i << endl;
        else
            fs_outfile << "NA" << endl;
    }
    fs_cprobfile.close();
    fs_outfile.close();
    
    hashwrapper *myWrapper = new md5wrapper();
    REQUIRE(myWrapper->getHashFromFile("./data/test_scanBuf.cprob.sorted") == myWrapper->getHashFromFile("./results/test_scanBuf.cprob.sorted.loaded"));
    delete myWrapper;
}


