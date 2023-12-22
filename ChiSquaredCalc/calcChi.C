// Standard library includes
#include <algorithm>

// ROOT includes
#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "THStack.h"
#include "TLegend.h"
#include "TH2D.h"
#include "TH1D.h"

//#include "SliceBinning.hh"
//#include "SliceHistogram.hh"
#include "MatrixUtils.hh"

void calcChi() {

  //TFile* in_tfile = new TFile( "data_covmat_TH2D_angle_MCONLY_blockwise_recoCut_noTune_Sept19.root", "read" );
  //TFile* in_tfile2 = new TFile( "data_signal_TH1D_angle_MCONLY_blockwise_recoCut_noTune_Sept19.root", "read" );
  //TFile* in_tfile3 = new TFile( "prior_true_signal_TH1D_angle_blockwise_recoCut_noTune_Sept19.root", "read" );

  //TFile* in_tfile = new TFile( "data_covmat_TH2D_angle_MCONLY_blockwise_recoCut_MECTune_Sept19.root", "read" );
  //TFile* in_tfile2 = new TFile( "data_signal_TH1D_angle_MCONLY_blockwise_recoCut_MECTune_Sept19.root", "read" );
  //TFile* in_tfile3 = new TFile( "prior_true_signal_TH1D_angle_blockwise_recoCut_MECTune_Sept19.root", "read" );

  TFile* in_tfile = new TFile( "data_covmat_TH2D_angle_MCONLY_blockwise_recoCut_nuWro_Sept19.root", "read" );
  TFile* in_tfile2 = new TFile( "data_signal_TH1D_angle_MCONLY_blockwise_recoCut_nuWro_Sept19.root", "read" );
  TFile* in_tfile3 = new TFile( "prior_true_signal_TH1D_angle_blockwise_recoCut_nuWro_Sept19.root", "read" );

  TVectorD* data_signal = nullptr;
  TVectorD* prior_true_signal = nullptr;
  
  TMatrixD* data_covmat = nullptr;
  TH2D* prior_true_covmat = nullptr;

  in_tfile2->GetObject( "data_signal", data_signal );
  in_tfile3->GetObject( "prior_true_signal", prior_true_signal );
  
  in_tfile->GetObject( "data_covmat", data_covmat );

  std::cout << "data_signal =  " << data_signal << std::endl;
  std::cout << "prior_true_signal =  " << prior_true_signal << std::endl;
  std::cout << "data_covmat =  " << data_covmat << std::endl;
  std::cout << " " << std::endl;

  //data_signal->Draw();
  //TAxis *yaxis =  data_signal_TH->GetYaxis();
  //std::cout << yaxis->GetNbins() << std::endl;
  
  TH1D *data_signal_TH = new TH1D(*data_signal);
  TH1D *prior_true_signal_TH = new TH1D(*prior_true_signal);

  TH2D *data_covmat_TH = new TH2D(*data_covmat);

  
  //TH2D *prior_true_covmat_TH = new TH2D(*prior_true_covmat);
  

  //Instead of slice histograms, use the TH1Ds

  // We now have all of the reco bin space histograms that we need as input.
  // Use them to make new histograms in slice space.
  //SliceHistogram::Chi2Result* slice_bnb = SliceHistogram::get_chi2(data_signal, prior_true_signal, data_covmat, prior_true_covmat );

    //auto chi2_result = slice_bnb->get_chi2( *slice_mc_plus_ext );
    //std::cout << "Slice " << sl_idx << ": \u03C7\u00b2 = "
    //  << chi2_result.chi2_ << '/' << chi2_result.num_bins_ << " bins,"
    //  << " p-value = " << chi2_result.p_value_ << '\n';

  int num_bins = data_signal_TH->GetNbinsX();
  if ( prior_true_signal_TH->GetNbinsX() != num_bins ) {
    throw std::runtime_error( "Incompatible vector sizes in chi^2"
      " calculation" );
   }


  // If both SliceHistogram objects have a covariance matrix, then
  // check that their dimensions match. If one is missing, it will be assumed
  // to be a null matrix
  if ( data_covmat_TH && prior_true_covmat ) {
    int my_cov_mat_x_bins = data_covmat_TH->GetNbinsX();
    int my_cov_mat_y_bins = data_covmat_TH->GetNbinsY();
    int other_cov_mat_x_bins = prior_true_covmat->GetNbinsY();
    int other_cov_mat_y_bins = prior_true_covmat->GetNbinsY();
    if ( my_cov_mat_x_bins != num_bins
      || my_cov_mat_y_bins != num_bins
      || other_cov_mat_x_bins != num_bins
      || other_cov_mat_y_bins != num_bins )
    {
      throw std::runtime_error( "Invalid covariance matrix dimensions"
        " encountered in chi^2 calculation" );
    }
  }
  else if (!data_covmat_TH && !prior_true_covmat ) {
    throw std::runtime_error( "Both SliceHistogram objects involved in"
      " a chi^2 calculation have null covariance matrices" );
  }

  // The total covariance matrix on the difference between the
  // two histograms is just the sum of each individual SliceHistogram's
  // owned covariance matrix.
  TH2D* cov_mat;
  cov_mat =  data_covmat_TH;
  //cov_mat += prior_true_covmat;  //This should always be null for what I'm doing


  // Get access to a TMatrixD object representing the covariance matrix.
  auto cov_matrix = data_covmat;

  // Invert the covariance matrix
  auto inverse_cov_matrix = invert_matrix( *cov_matrix, 1e-4 );

  // Create a 1D vector containing the difference between the two slice
  // histograms in each bin
  TMatrixD diff_vec( 1, num_bins );
  for ( int a = 0; a < num_bins; ++a ) {
    // Note the one-based bin indices used for ROOT histograms
    double counts = data_signal_TH->GetBinContent( a + 1 );
    double other_counts = prior_true_signal_TH->GetBinContent( a + 1 );
    diff_vec( 0, a ) = counts - other_counts;
  }

  // Multiply diff * covMat^{-1} * diff^{T} to get chi-squared
  TMatrixD temp1( diff_vec, TMatrixD::kMult, *inverse_cov_matrix );
  TMatrixD temp2( temp1, TMatrixD::kMult, diff_vec.T() );

  // We'll now have a 1x1 matrix containing the chi-squared value
  double chi2 = temp2( 0, 0 );

  // Assume that parameter fitting is not done, so that the relevant degrees
  // of freedom for the chi^2 test is just the number of bins minus one
  int dof = num_bins - 1;

  // Calculate a p-value for observing a chi^2 value at least as large as the
  // one actually obtained
  double p_value = ROOT::Math::inc_gamma_c( dof / 2., chi2 / 2. );

  std::cout << "chi2 =  " << chi2 << std::endl;
  std::cout << "num_bins =  " << num_bins << std::endl;
  std::cout << "dof =  " << dof << std::endl;
  std::cout << "p_value =  " << p_value << std::endl;

}

int main() {
  calcChi();
  return 0;
}
