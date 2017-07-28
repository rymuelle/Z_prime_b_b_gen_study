// c++ -o LHE_reader `root-config --glibs --cflags` -lm LHE_reader.cpp
#include "LHEF.h"
#include <iomanip>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"

using namespace std ;


int main(int argc, char ** argv) 
{


  int maxEvents = 10;
  std::ifstream ifs (argv[1]) ;
  

  LHEF::Reader reader (ifs) ;

  int verbosity = atoi(argv[2]);
  int i = 0;
  TLorentzVector mu_neg;
  TLorentzVector mu_pos;

  TH1F * TH1F_eta_bjet = new TH1F("TH1F_eta_bjet", "TH1F_eta_bjet; #eta", 100, -4, 4);

  TCanvas * c1 = new TCanvas();


  while (reader.readEvent ()) 
    {
        i = i +1;
      if ( reader.outsideBlock.length ()) std::cout << reader.outsideBlock;
      // loop over particles in the event


      for (int iPart = 0 ; iPart < reader.hepeup.IDUP.size (); ++iPart) 
        {

          if(reader.hepeup.IDUP.at (iPart) == -13){
            mu_neg.SetPxPyPzE(
                reader.hepeup.PUP.at (iPart).at (0), // px
                reader.hepeup.PUP.at (iPart).at (1), // py
                reader.hepeup.PUP.at (iPart).at (2), // pz
                reader.hepeup.PUP.at (iPart).at (3) // E
              );
           }

          if(reader.hepeup.IDUP.at (iPart) == 13){
            mu_pos.SetPxPyPzE(
                reader.hepeup.PUP.at (iPart).at (0), // px
                reader.hepeup.PUP.at (iPart).at (1), // py
                reader.hepeup.PUP.at (iPart).at (2), // pz
                reader.hepeup.PUP.at (iPart).at (3) // E
              );
           }
          

            if(verbosity > 10) {std::cout << reader.hepeup.IDUP.at (iPart) << std::endl;}            
        }
        if(verbosity > 10) {std::cout << "mass of di muon " << (mu_pos+mu_neg ).M() << std::endl;}
        TH1F_eta_bjet->Fill(mu_pos.Eta());
        TH1F_eta_bjet->Fill(mu_neg.Eta());



   
    }
    TH1F_eta_bjet->Draw();
    c1->SaveAs("output/TH1F_eta_bjet.png");



return 0;
}
