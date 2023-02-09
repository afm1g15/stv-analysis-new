#include "TFile.h"
#include "TMatrixD.h"

void rootFileMerger() {

  // Retrieve the pre-calculated unfolding inputs for this example

  //NUE ENERGY
  //TFile* in_tfile_ds = new TFile( "data_signal_nue_energy.root", "read" );
  //TFile* in_tfile_dc = new TFile( "data_covmat_nue_energy.root", "read" );
  //TFile* in_tfile_s = new TFile( "smearcept_nue_energy.root", "read" );
  //TFile* in_tfile_pts = new TFile( "prior_true_signal_nue_energy.root", "read" );
  //NUMU ENERGY
  TFile* in_tfile_ds = new TFile( "data_signal_numu_energy.root", "read" );
  TFile* in_tfile_dc = new TFile( "data_covmat_numu_energy.root", "read" );
  TFile* in_tfile_s = new TFile( "smearcept_numu_energy.root", "read" );
  TFile* in_tfile_pts = new TFile( "prior_true_signal_numu_energy.root", "read" );

  TMatrixD* data_signal = nullptr;
  TMatrixD* data_covmat = nullptr;
  TMatrixD* smearcept = nullptr;
  TMatrixD* prior_true_signal = nullptr;

  in_tfile_ds->GetObject( "data_signal", data_signal );
  in_tfile_dc->GetObject( "data_covmat", data_covmat );
  in_tfile_s->GetObject( "smearcept", smearcept );
  in_tfile_pts->GetObject( "prior_true_signal", prior_true_signal );

  //NUE ENERGY
  //std::unique_ptr<TFile> f(TFile::Open("nue_energy_inputs.root", "recreate"));
  //NUMU ENERGY
  std::unique_ptr<TFile> f(TFile::Open("numu_energy_inputs.root", "recreate"));
  
  f->WriteObject(data_signal, "data_signal");
  f->WriteObject(data_covmat, "data_covmat");
  f->WriteObject(smearcept, "smearcept");
  f->WriteObject(prior_true_signal, "prior_true_signal");
   
  f->Close();
 
}
