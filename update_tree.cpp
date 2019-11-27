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
    string ifilename = "tree.root";
    TFile* rfile = TFile::Open(ifilename.c_str(), "UPDATE");
    TTree* tree = static_cast<TTree*>(rfile->Get("mytree"));
    float var0 = 0.0;
    float var1 = 0.0;
    float varN = 0.0;

    TBranch* new_branch = tree->Branch("varN", &varN, "varN/F");
    tree->SetBranchStatus("*",0);
    tree->SetBranchStatus("var0", 1);
    tree->SetBranchStatus("var1", 1);
    tree->SetBranchStatus("varN", 1);
    tree->SetBranchAddress("var0", &var0);
    tree->SetBranchAddress("var1", &var1);

    unsigned int n_events = tree->GetEntries();
    for(size_t ievent = 0; ievent < n_events; ievent++)
    {
        tree->GetEvent(ievent);
        varN = var0 + var1;
        new_branch->Fill();
    } // ievent

    tree->SetBranchStatus("*",1);

    // calling tree->AutoSave() seems to have the same behavior as
    // tree->Write("", TObject::kOverwrite), i.e. that there are no
    // new cycles (mytree;2, mytree;1, etc...) appearing in the output file
    // c.f. https://root.cern.ch/doc/master/classTTree.html#addcoltoexistingtree

    //tree->AutoSave();
    tree->Write("", TObject::kOverwrite);
    rfile->Close();

    return 0;
}
