#include "TFile.h"
#include "TMatrixD.h"
#include <iostream>
#include <fstream>
#include <typeinfo>

#include "WienerSVDUnfolder.hh"
#include "DAgostiniUnfolder.hh"

using DCC = DAgostiniUnfolder::ConvergenceCriterion;
using RMT = WienerSVDUnfolder::RegularizationMatrixType;

const RMT MY_REGULARIZATION = RMT::kIdentity;
//const RMT MY_REGULARIZATION = RMT::kFirstDeriv;
//const RMT MY_REGULARIZATION = RMT::kSecondDeriv;

void example_unfolding() {
  //extern ostream& operator<<(ostream& sout, const std::string& string);
  
  // Retrieve the pre-calculated unfolding inputs for this example
  //NUE ENERGY
  //TFile* in_tfile = new TFile( "nue_energy_inputs.root", "read" );
  //NUMU ENERGY
  TFile* in_tfile = new TFile( "numu_energy_inputs.root", "read" );

  TMatrixD* data_signal = nullptr;
  TMatrixD* data_covmat = nullptr;
  TMatrixD* smearcept = nullptr;
  TMatrixD* prior_true_signal = nullptr;

  in_tfile->GetObject( "data_signal", data_signal );
  in_tfile->GetObject( "data_covmat", data_covmat );
  in_tfile->GetObject( "smearcept", smearcept );
  in_tfile->GetObject( "prior_true_signal", prior_true_signal );

  //data_signal->Print();
  //data_covmat->Print();
  //smearcept->Print();
  //prior_true_signal->Print();

  // Instantiate an object derived from the Unfolder base class
  WienerSVDUnfolder unfolder( true, MY_REGULARIZATION );

  //DAgostiniUnfolder unfolder( NUM_ITERATIONS );

  //DAgostiniUnfolder unfolder( DCC:FigureOfMerit, 0.025 );

  // Perform the unfolding
  UnfoldedMeasurement result = unfolder.unfold( *data_signal, *data_covmat,
    *smearcept, *prior_true_signal );

  result.unfolded_signal_->Print();
  result.cov_matrix_->Print();

  //NUE ENERGY
  //std::ofstream outfile ("nue_unsmeared_events_energy.csv",std::ofstream::binary);
  //std::ofstream outfile2 ("nue_unsmeared_errors_energy.csv",std::ofstream::binary);
  //NUMU ENERGY
  std::ofstream outfile ("numu_unsmeared_events_energy.csv",std::ofstream::binary);
  std::ofstream outfile2 ("numu_unsmeared_errors_energy.csv",std::ofstream::binary);
  
  for ( int t = 0; t < 10; ++t ) {
    double evts = 0.;
    double error = 0.;
    char* hold;
    if ( t < 10 ) {
      evts = result.unfolded_signal_->operator()( t, 0 );
      error = std::sqrt( std::max(0., result.cov_matrix_->operator()( t, t )) );
    }
    std::cout << "evts " << evts << std::endl;
    std::cout << "err " << error << std::endl;
    outfile << evts << "\n";
    outfile2 << error << "\n";
  }
  

  // Output is struct with these data members
  //std::unique_ptr< TMatrixD > unfolded_signal_;
  //std::unique_ptr< TMatrixD > cov_matrix_;
  //std::unique_ptr< TMatrixD > unfolding_matrix_;
  //std::unique_ptr< TMatrixD > err_prop_matrix_;
  //std::unique_ptr< TMatrixD > add_smear_matrix_;
  
  outfile.close();
  outfile2.close();

}
