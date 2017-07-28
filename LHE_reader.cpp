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

  int i = 0;
  TLorentzVector mu_neg;
  TLorentzVector mu_pos;

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

          /*  //std::cout << "clustering: " << reader.hepeup.clustering[iPart].p1 << " " << reader.hepeup.clustering[iPart].p2 << " " << reader.hepeup.clustering[iPart].p0 << " " << reader.hepeup.clustering[iPart].scale << " " << reader.hepeup.clustering[iPart].alphas <<  std::endl;
           TLorentzVector boost (
                reader.hepeup.PUP.at (iPart).at (0), // px
                reader.hepeup.PUP.at (iPart).at (1), // py
                reader.hepeup.PUP.at (iPart).at (2), // pz
                reader.hepeup.PUP.at (iPart).at (3) // E
              ) ; 

            if(reader.hepeup.IDUP.at (iPart) == 1000006 and reader.hepeup.ISTUP.at (iPart) == 1) 
            {
                reader.hepeup.ISTUP.at (iPart) = 2;

                if(reader2.readEvent())
                {
                       reader.hepeup.addHEPUP(reader2.hepeup, boost.BoostVector(), iPart);
                        std::cout << iPart << std::endl;
                }

            }

            if(reader.hepeup.IDUP.at (iPart) == -1000006)
            {
                reader.hepeup.ISTUP.at (iPart) = 2;
                if(reader2.readEvent())
                {
                       reader.hepeup.addHEPUP(reader2.hepeup, boost.BoostVector(), iPart);
                        std::cout << iPart << std::endl;
                }
            }*/
          

            std::cout << reader.hepeup.IDUP.at (iPart) << std::endl;            
        }
        std::cout << mu_neg.Phi() << std::endl;

   
    }


return 0;
}
