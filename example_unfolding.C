#include "TFile.h"
#include "TMatrixD.h"

#include "WienerSVDUnfolder.hh"
#include "DAgostiniUnfolder.hh"

using DCC = DAgostiniUnfolder::ConvergenceCriterion;
using RMT = WienerSVDUnfolder::RegularizationMatrixType;

const RMT MY_REGULARIZATION = RMT::kIdentity;
//const RMT MY_REGULARIZATION = RMT::kFirstDeriv;
//const RMT MY_REGULARIZATION = RMT::kSecondDeriv;

void example_unfolding() {

  // Retrieve the pre-calculated unfolding inputs for this example
  //TFile* in_tfile = new TFile( "energy_inputs_MCONLY_weighted_blockwise_recoCut_incErr_Sept19.root", "read" );
  //TFile* in_tfile = new TFile( "angle_inputs_MCONLY_weighted_blockwise_recoCut_incErr_Sept19.root", "read" );
  //TFile* in_tfile = new TFile( "leptonMom_inputs_MCONLY_weighted_blockwise_recoCut_incErr_Sept19.root", "read" );
  TFile* in_tfile = new TFile( "angle_inputs_MCONLY_weighted_blockwise_recoCut_incErr_nuWro_Sept19.root", "read" );
  //TFile* in_tfile = new TFile( "angle_inputs_MCONLY_weighted_blockwise_recoCut_incErr_run1_Sept19.root", "read" );
  //TFile* in_tfile = new TFile( "angle_inputs_MCONLY_weighted_blockwise_recoCut_incErr_noTune_Sept19.root", "read" );
  //TFile* in_tfile = new TFile( "angle_inputs_MCONLY_weighted_blockwise_recoCut_incErr_MECTune_Sept19.root", "read" );

  TMatrixD* data_signal = nullptr;
  TMatrixD* data_covmat = nullptr;
  TMatrixD* smearcept = nullptr;
  TMatrixD* prior_true_signal = nullptr;

  in_tfile->GetObject( "data_signal", data_signal );
  in_tfile->GetObject( "data_covmat", data_covmat );
  in_tfile->GetObject( "smearcept", smearcept );
  in_tfile->GetObject( "prior_true_signal", prior_true_signal );

  // Instantiate an object derived from the Unfolder base class
  WienerSVDUnfolder unfolder( true, MY_REGULARIZATION );

  //DAgostiniUnfolder unfolder( NUM_ITERATIONS );

  //DAgostiniUnfolder unfolder( DCC:FigureOfMerit, 0.025 );

  // Perform the unfolding
  UnfoldedMeasurement result = unfolder.unfold( *data_signal, *data_covmat,
    *smearcept, *prior_true_signal, "blocks.txt" );

  result.unfolded_signal_->Print();

  //OUTPUT
  //std::ofstream outfile ("blockwise_unsmeared_events_energy_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile2 ("blockwise_unsmeared_errors_energy_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile3 ("blockwise_unsmeared_AC_energy_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile4 ("blockwise_unsmeared_unfolding_matrix_energy_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile5 ("blockwise_unsmeared_cov_matrix_energy_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //OUTPUT ANGLE
  //std::ofstream outfile ("blockwise_unsmeared_events_angle_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile2 ("blockwise_unsmeared_errors_angle_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile3 ("blockwise_unsmeared_AC_angle_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile4 ("blockwise_unsmeared_unfolding_matrix_angle_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile5 ("blockwise_unsmeared_cov_matrix_angle_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //OUTPUT MOM
  //std::ofstream outfile ("blockwise_unsmeared_events_leptonMom_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile2 ("blockwise_unsmeared_errors_leptonMom_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile3 ("blockwise_unsmeared_AC_leptonMom_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile4 ("blockwise_unsmeared_unfolding_matrix_leptonMom_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile5 ("blockwise_unsmeared_cov_matrix_leptonMom_MC_ONLY_weighted_recoCut_incErr_Sept19.csv",std::ofstream::binary);

  //OUT ANGLE RUN1
  //std::ofstream outfile ("blockwise_unsmeared_events_angle_MC_ONLY_weighted_recoCut_incErr_run1_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile2 ("blockwise_unsmeared_errors_angle_MC_ONLY_weighted_recoCut_incErr_run1_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile3 ("blockwise_unsmeared_AC_angle_MC_ONLY_weighted_recoCut_incErr_run1_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile4 ("blockwise_unsmeared_unfolding_matrix_angle_MC_ONLY_weighted_recoCut_incErr_run1_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile5 ("blockwise_unsmeared_cov_matrix_angle_MC_ONLY_weighted_recoCut_incErr_run1_Sept19.csv",std::ofstream::binary);
  
  //OUT ANGLE NUWRO
  std::ofstream outfile ("blockwise_unsmeared_events_angle_MC_ONLY_weighted_recoCut_incErr_nuWro_Sept19.csv",std::ofstream::binary);
  std::ofstream outfile2 ("blockwise_unsmeared_errors_angle_MC_ONLY_weighted_recoCut_incErr_nuWro_Sept19.csv",std::ofstream::binary);
  std::ofstream outfile3 ("blockwise_unsmeared_AC_angle_MC_ONLY_weighted_recoCut_incErr_nuWro_Sept19.csv",std::ofstream::binary);
  std::ofstream outfile4 ("blockwise_unsmeared_unfolding_matrix_angle_MC_ONLY_weighted_recoCut_incErr_nuWro_Sept19.csv",std::ofstream::binary);
  std::ofstream outfile5 ("blockwise_unsmeared_cov_matrix_angle_MC_ONLY_weighted_recoCut_incErr_nuWro_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile6 ("blockwise_unsmeared_err_prop_angle_MC_ONLY_weighted_recoCut_incErr_nuWro_Sept19.csv",std::ofstream::binary);

  //OUT ANGLE NOTUNE
  //std::ofstream outfile ("blockwise_unsmeared_events_angle_MC_ONLY_weighted_recoCut_incErr_noTune_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile2 ("blockwise_unsmeared_errors_angle_MC_ONLY_weighted_recoCut_incErr_noTune_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile3 ("blockwise_unsmeared_AC_angle_MC_ONLY_weighted_recoCut_incErr_noTune_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile4 ("blockwise_unsmeared_unfolding_matrix_angle_MC_ONLY_weighted_recoCut_incErr_noTune_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile5 ("blockwise_unsmeared_cov_matrix_angle_MC_ONLY_weighted_recoCut_incErr_noTune_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile6 ("blockwise_unsmeared_err_prop_angle_MC_ONLY_weighted_recoCut_incErr_noTune_Sept19.csv",std::ofstream::binary);
  //std::unique_ptr<TFile> f(TFile::Open("blockwise_unsmeared_cov_matrix_angle_MC_ONLY_weighted_recoCut_incErr_noTune_Sept19.root", "recreate"));
  // f->WriteObject(&result.cov_matrix_, "data_covmat");

  //OUT ANGLE MECTUNE
  //std::ofstream outfile ("blockwise_unsmeared_events_angle_MC_ONLY_weighted_recoCut_incErr_MECTune_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile2 ("blockwise_unsmeared_errors_angle_MC_ONLY_weighted_recoCut_incErr_MECTune_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile3 ("blockwise_unsmeared_AC_angle_MC_ONLY_weighted_recoCut_incErr_MECTune_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile4 ("blockwise_unsmeared_unfolding_matrix_angle_MC_ONLY_weighted_recoCut_incErr_MECTune_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile5 ("blockwise_unsmeared_cov_matrix_angle_MC_ONLY_weighted_recoCut_incErr_MECTune_Sept19.csv",std::ofstream::binary);
  //std::ofstream outfile6 ("blockwise_unsmeared_err_prop_angle_MC_ONLY_weighted_recoCut_incErr_MECTune_Sept19.csv",std::ofstream::binary);

  for ( int t = 0; t < 20; ++t ) {
    double evts = 0.;
    double error = 0.;
    char* hold;
    if ( t < 20 ) {
      evts = result.unfolded_signal_->operator()( t, 0 );
      error = std::sqrt( std::max(0., result.cov_matrix_->operator()( t, t )) );
    }
    //std::cout << "evts " << evts << "  " << "err " << error << std::endl;
    outfile << evts << "\n";
    outfile2 << error << "\n";
  }

  for ( int t = 0; t < 20; ++t ) {
    for ( int s = 0; s < 20; ++s ) {
      double ac = 0.;
      char* hold;
      if ( t < 20 and s < 20) {
	ac = result.add_smear_matrix_->operator()( t, s ) ;
      }
      //std::cout << "ac " << ac << std::endl;
      outfile3 << ac << "\n";
    }
  }

  for ( int t = 0; t < 20; ++t ) {
    for ( int s = 0; s < 20; ++s ) {
      double uf = 0.;
      char* hold;
      if ( t < 20 and s < 20) {
	uf = result.unfolding_matrix_->operator()( t, s ) ;
      }
      //std::cout << "unfolding " << uf << std::endl;
      outfile4 << uf << "\n";
    }
  }

  for ( int t = 0; t < 20; ++t ) {
    for ( int s = 0; s < 20; ++s ) {
      double cv = 0.;
      char* hold;
      if ( t < 20 and s < 20) {
	cv = result.cov_matrix_->operator()( t, s ) ;
      }
      //std::cout << "unfolding " << uf << std::endl;
      outfile5 << cv << "\n";
    }
  }
  /*
  for ( int t = 0; t < 20; ++t ) {
    for ( int s = 0; s < 20; ++s ) {
      double ep = 0.;
      char* hold;
      if ( t < 20 and s < 20) {
	ep = result.err_prop_matrix_->operator()( t, s ) ;
      }
      //std::cout << "unfolding " << uf << std::endl;
      outfile6 << ep<< "\n";
    }
  }
  */
  // Output is struct with these data members
  //std::unique_ptr< TMatrixD > unfolded_signal_;
  //std::unique_ptr< TMatrixD > cov_matrix_;
  //std::unique_ptr< TMatrixD > unfolding_matrix_;
  //std::unique_ptr< TMatrixD > err_prop_matrix_;
  //std::unique_ptr< TMatrixD > add_smear_matrix_;

  outfile.close();
  outfile2.close();
  outfile3.close();
  outfile4.close();
  outfile5.close();
  //outfile6.close();
  //f->Close();

}
