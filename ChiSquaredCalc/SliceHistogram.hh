#pragma once

// Standard library includes
#include <cmath>
#include <limits>
#include <memory>
#include <stdexcept>

// ROOT includes
#include "TH1.h"
#include "Math/SpecFuncMathCore.h" // Needed for ROOT::Math::inc_gamma_c()

// STV analysis includes
#include "MatrixUtils.hh"
//#include "NormShapeCovMatrix.hh"
//#include "SliceBinning.hh"
//#include "SystematicsCalculator.hh"

class SliceHistogram {

  public:

    struct Chi2Result {

      Chi2Result() {}

      Chi2Result( double chi2, int nbins, int dof, double pval )
        : chi2_( chi2 ), num_bins_( nbins ), dof_( dof ), p_value_( pval ) {}

      double chi2_;
      int num_bins_;
      int dof_;
      double p_value_;
    };

    static Chi2Result* get_chi2( const TH1D& , const TH1D& , const TMatrixD& , const TMatrixD& ) const;

};


SliceHistogram::Chi2Result SliceHistogram::get_chi2(
						    const TH1D& other, const TH1D& other2, const TMatrixD& othercov, const TMatrixD& other2cov ) const
{

  std::cout << "Test print 2" << std::endl;
  /*
  int num_bins = hist_->GetNbinsX();
  if ( other.hist_->GetNbinsX() != num_bins ) {
    throw std::runtime_error( "Incompatible vector sizes in chi^2"
      " calculation" );
  }

  // If both SliceHistogram objects have a covariance matrix, then
  // check that their dimensions match. If one is missing, it will be assumed
  // to be a null matrix
  if ( cmat_.cov_matrix_ && other.cmat_.cov_matrix_ ) {
    int my_cov_mat_x_bins = cmat_.cov_matrix_->GetNbinsX();
    int my_cov_mat_y_bins = cmat_.cov_matrix_->GetNbinsY();
    int other_cov_mat_x_bins = other.cmat_.cov_matrix_->GetNbinsY();
    int other_cov_mat_y_bins = other.cmat_.cov_matrix_->GetNbinsY();
    if ( my_cov_mat_x_bins != num_bins
      || my_cov_mat_y_bins != num_bins
      || other_cov_mat_x_bins != num_bins
      || other_cov_mat_y_bins != num_bins )
    {
      throw std::runtime_error( "Invalid covariance matrix dimensions"
        " encountered in chi^2 calculation" );
    }
  }
  else if ( !cmat_.cov_matrix_ && !other.cmat_.cov_matrix_ ) {
    throw std::runtime_error( "Both SliceHistogram objects involved in"
      " a chi^2 calculation have null covariance matrices" );
  }

  // The total covariance matrix on the difference between the
  // two histograms is just the sum of each individual SliceHistogram's
  // owned covariance matrix.
  CovMatrix cov_mat;
  cov_mat += cmat_;
  cov_mat += other.cmat_;

  // Get access to a TMatrixD object representing the covariance matrix.
  auto cov_matrix = cov_mat.get_matrix();

  // Invert the covariance matrix
  auto inverse_cov_matrix = invert_matrix( *cov_matrix, inversion_tol );

  // Create a 1D vector containing the difference between the two slice
  // histograms in each bin
  TMatrixD diff_vec( 1, num_bins );
  for ( int a = 0; a < num_bins; ++a ) {
    // Note the one-based bin indices used for ROOT histograms
    double counts = hist_->GetBinContent( a + 1 );
    double other_counts = other.hist_->GetBinContent( a + 1 );
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

  Chi2Result result( chi2, num_bins, dof, p_value );
  */
  Chi2Result result( 0, 0, 0, 0 );
  return result;
  

}
/*
void SliceHistogram::transform( const TMatrixD& mat ) {

  int dim = hist_->GetDimension();
  if ( dim != 1 ) throw std::runtime_error( "SliceHistogram::transform() is"
    " currently implemented only for 1D histograms." );

  int num_cols = mat.GetNcols();
  int num_bins = hist_->GetNbinsX();
  if ( num_cols != num_bins ) throw std::runtime_error( "Incompatible"
    " transformation matrix passed to SliceHistogram::transform()" );

  int num_rows = mat.GetNrows();
  if ( num_rows != num_cols ) throw std::runtime_error( "Transformations which"
    " change the number of bins are currently unimplemented in"
    " SliceHistogram::transform()" );

  // Create a column vector with the current histogram bin contents
  TMatrixD hist_vec = this->get_col_vect();

  // Apply the transformation matrix to the histogram and store the result in a
  // new column vector
  TMatrixD transformed_hist_vec( mat,
    TMatrixD::EMatrixCreatorsOp2::kMult, hist_vec );

  // Replace the old histogram contents with the new ones
  for ( int b = 0; b < num_bins; ++b ) {
    double val = transformed_hist_vec( b, 0 );
    hist_->SetBinContent( b + 1, val );
  }

  // If the covariance matrix isn't defined, then we're done and can return
  // early. Otherwise, we'll apply a corresponding transformation to the
  // covariance matrix.
  if ( !cmat_.cov_matrix_ ) return;

  // Get the original covariance matrix as a std::unique_ptr< TMatrixD >
  auto orig_cov = cmat_.get_matrix();

  // Take the transpose of the transformation matrix
  TMatrixD tr_mat( TMatrixD::kTransposed, mat );

  // See https://stats.stackexchange.com/q/113700
  TMatrixD transformed_cov = mat * ( *orig_cov ) * tr_mat;

  // Create a new CovMatrix object using the transformed covariance matrix
  CovMatrix transformed_cmat( transformed_cov );

  // Replace the owned CovMatrix object with the new one
  cmat_ = std::move( transformed_cmat );

  // To wrap things up, set the updated histogram bin errors based on the
  // diagonal elements of the covariance matrix
  for ( int b = 0; b < num_bins; ++b ) {
    double variance = cmat_.cov_matrix_->GetBinContent( b + 1, b + 1 );
    double err = std::sqrt( std::max(0., variance) );
    //double err = shape_errors_.at( b );
    hist_->SetBinError( b + 1, err );
  }
  

}

*/
