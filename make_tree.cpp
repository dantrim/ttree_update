//std/stl
#include <iostream>
#include <string>
using namespace std;

//ROOT
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

int main()
{
    string ofilename = "tree.root";
    TFile* rfile = TFile::Open(ofilename.c_str(), "RECREATE");

    TTree* tree = new TTree("mytree", "mytree");
    float var0 = 0.0;
    float var1 = 0.0;
    float var2 = 0.0;
    tree->Branch("var0", &var0);
    tree->Branch("var1", &var1);
    tree->Branch("var2", &var2);

    unsigned int n_events = 1000;
    for(size_t ievent = 0; ievent <  n_events; ievent++)
    {
        var0 = 2;
        var1 = 2;
        var2 = 49;
        tree->Fill();
    } // ievent

    tree->Write();
    rfile->Close();

    delete tree;
    return 0;
}
