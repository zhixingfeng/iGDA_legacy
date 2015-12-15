/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test_PileupParser.h
 * Author: zhixingfeng
 *
 * Created on November 12, 2015, 3:48 PM
 */


#include "../include/catch.hpp"
#include "../src/plugin/plugin.h"
#include "../src/tool/tool.h"
   
SCENARIO ("Test PileupParserGDA", "[PileupParser][PileupParserGDA]") {
    string pileupfile_gda = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup"; 
    string pileupfile_gda_out = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup.out";
    string basefreqfile_gda = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.basefreq";
    string baseprobfile_gda = "./results/mixed_MSSA_78_ratio_0.05_B_1.bam.baseprob";
    
    GIVEN ("A object of PileupParserGDA and pileupfile " + pileupfile_gda) {
 
        PileupParserGDA obj_PileupParserGDA;
        
        WHEN ("pointer ptr_fs_pileupfile is not set") {
            AND_WHEN ("readLines() is called") {
                THEN ("A expection should be thrown") {
                    REQUIRE_THROWS(obj_PileupParserGDA.readLine());
                }
            }
        }
        
        WHEN ("pointer ptr_fs_pileupfile is set") {
            THEN ("test Pileup and BaseFreq"){
                // read and write pileup data
                ifstream fs_pileup; open_infile(fs_pileup, pileupfile_gda);
                ofstream fs_pileup_out; open_outfile(fs_pileup_out, pileupfile_gda_out);
                ofstream fs_basefreq; open_outfile(fs_basefreq, basefreqfile_gda);
                ofstream fs_baseprob; open_outfile(fs_baseprob, baseprobfile_gda);
                
                obj_PileupParserGDA.setPileupFileStream(& fs_pileup);
                while (true) {
                    obj_PileupParserGDA.readLine();
                    if (fs_pileup.eof()) break;
                    
                    Pileup obj_Pileup = obj_PileupParserGDA.getPileup();
                    obj_PileupParserGDA.calBaseFreq();
                    BaseFreq obj_BaseFreq = obj_PileupParserGDA.getBaseFreq();
                    //BaseFreq obj_BaseFreq = Pileup2BaseFreq(obj_Pileup);
                    
                    fs_pileup_out << obj_Pileup;
                    fs_basefreq << obj_BaseFreq.freq_ins << endl;
                    fs_basefreq << obj_BaseFreq.freq << endl;
                    fs_baseprob << obj_BaseFreq.prob_ins << endl;
                    fs_baseprob << obj_BaseFreq.prob << endl;
                    
                }
                fs_pileup.close();
                fs_pileup_out.close();
                fs_basefreq.close();
                fs_baseprob.close();
                
                // check written file
                ifstream fs_pileup_in; open_infile(fs_pileup_in, pileupfile_gda_out);
                open_infile(fs_pileup, pileupfile_gda);
                
                hashwrapper *myWrapper = new md5wrapper();
                REQUIRE(myWrapper->getHashFromFile(pileupfile_gda) == myWrapper->getHashFromFile(pileupfile_gda_out));
                delete myWrapper;
                
                PileupParserGDA obj_PileupParserGDA_in( & fs_pileup_in);
                while (true){
                    bool is_end = obj_PileupParserGDA.readLine();
                    bool is_end_out = obj_PileupParserGDA_in.readLine();
                    REQUIRE(is_end == is_end_out);
                    if (is_end) break;
                    REQUIRE(obj_PileupParserGDA.getPileup() == obj_PileupParserGDA_in.getPileup());
                }
            }
        }
        
    }
}


TEST_CASE("Test PileupParser::getRefGenome", "[getRefGenome]") {
    string pileupfile = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.pileup"; 
    PileupParserGDA obj_PileupParserGDA;
    PileupParser * ptr_PileupParser = &obj_PileupParserGDA;
    RefGenome refgenome = ptr_PileupParser->getRefGenome(pileupfile);
    
    string refgenomefile_ref = "./data/mixed_MSSA_78_ratio_0.05_B_1.bam.refgenome.ref";
    ifstream fs_refgenomefile_ref; open_infile(fs_refgenomefile_ref, refgenomefile_ref);
    string refgenome_ref;
    getline(fs_refgenomefile_ref,refgenome_ref);
    fs_refgenomefile_ref.close();

    REQUIRE(refgenome[0] == refgenome_ref);
}

TEST_CASE("Test PileupParser::getMatchProb(), getDelProb(), getNorefProb()", "[PileupParser]") {
    PileupParserGDA obj_PileupParserGDA;
    map<string, double> prob;
    prob["A"] = 0.025;
    prob["G"] = 0.8;
    prob["T"] = 0.01;
    prob["-"] = 0.1;
    prob["a"] = 0.065;
    
    // test normal cases
    map<string, double> prob_m = obj_PileupParserGDA.getMatchProb(prob);
    REQUIRE(prob_m.size() == 3);
    REQUIRE(prob_m["A"] == Approx(0.025 / 0.835));
    REQUIRE(prob_m["G"] == Approx(0.8 / 0.835));
    REQUIRE(prob_m["T"] == Approx(0.01 / 0.835));
    
    prob_m = obj_PileupParserGDA.getMatchProb(prob, 'G');
    REQUIRE(prob_m.size() == 2);
    REQUIRE(prob_m["A"] == Approx(0.025 / 0.835));
    REQUIRE(prob_m["T"] == Approx(0.01 / 0.835));

    map<string, double> prob_d = obj_PileupParserGDA.getDelProb(prob);
    REQUIRE(prob_d.size()==1);
    REQUIRE(prob_d["-"] == 0.1);
    
    // test extreme cases
    prob.clear();
    prob["-"] = 0.935;
    prob["a"] = 0.065;
    prob_m = obj_PileupParserGDA.getMatchProb(prob, 'G');
    REQUIRE(prob_m.size()==0);
    
    prob.clear();
    prob["A"] = 0.025;
    prob["G"] = 0.9;
    prob["T"] = 0.01;
    prob["a"] = 0.065;
    prob_d = obj_PileupParserGDA.getDelProb(prob);
    REQUIRE(prob_d.size()==0);
}

TEST_CASE("Test PileupParser::groupPileup()", "PileupParser") {
    string pileupfile = "./data/test_scanBuf.pileup";
    string outfile = "./results/test_scanBuf_group.pileup";
    map<int, NtSeq>::iterator it;
    PileupParserGDA obj_PileupParserGDA;
    
    // read pileup file and group reads and write grouped read into file 
    ifstream fs_pileupfile; open_infile(fs_pileupfile, pileupfile);
    obj_PileupParserGDA.setPileupFileStream(&fs_pileupfile);
    ofstream fs_outfile; open_outfile(fs_outfile, outfile); 
    
    while(true) {
        obj_PileupParserGDA.readLine();
        if(fs_pileupfile.eof()) break;
        obj_PileupParserGDA.groupPileup();
        Pileup pu = obj_PileupParserGDA.getPileup();
        
        fs_outfile << pu.refID <<"\t_" << pu.locus <<'\t' << pu.refSeq << '\t' << pu.cvg_ins << '\t';
        for (it = pu.readSeq_group_ins.begin();it!=pu.readSeq_group_ins.end(); it++)
            fs_outfile << NtSeq2Str(it->second) << ',';
        fs_outfile << '\t';
        for (it = pu.readSeq_group_ins.begin();it!=pu.readSeq_group_ins.end(); it++)
            fs_outfile << it->first << ',';
        fs_outfile << endl;
        
        fs_outfile << pu.refID <<"\t" << pu.locus <<'\t' << pu.refSeq << '\t' << pu.cvg << '\t';
        for (it = pu.readSeq_group.begin();it!=pu.readSeq_group.end(); it++)
            fs_outfile << NtSeq2Str(it->second) << ',';
        fs_outfile << '\t';
        for (it = pu.readSeq_group.begin();it!=pu.readSeq_group.end(); it++)
            fs_outfile << it->first << ',';
        fs_outfile << endl;
    }
    fs_pileupfile.close();
    fs_outfile.close();
    
    // read group pileup and validate
}

TEST_CASE("test PileupParserGDA::checkFormat()") {
    REQUIRE(PileupParserGDA::checkFormat("./data/test_scanBuf.pileup") == true);
    REQUIRE(PileupParserGDA::checkFormat("./data/wrong_format_1.pileup") == false);
    REQUIRE(PileupParserGDA::checkFormat("./data/wrong_format_2.pileup") == false);
    REQUIRE(PileupParserGDA::checkFormat("./data/wrong_format_3.pileup") == false);
    REQUIRE(PileupParserGDA::checkFormat("./data/wrong_format_4.pileup") == false);
    REQUIRE(PileupParserGDA::checkFormat("./data/wrong_format_5.pileup") == false);
    REQUIRE(PileupParserGDA::checkFormat("./data/wrong_format_6.pileup") == false);
}



