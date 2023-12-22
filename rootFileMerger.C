#include "TFile.h"
#include "TMatrixD.h"

void rootFileMerger() {

  // Retrieve the pre-calculated unfolding inputs for this example


  //BLOCKWISE
  //TFile* in_tfile_ds = new TFile( "data_signal_energy_MCONLY_blockwise_recoCut_Sept19.root", "read" );
  //TFile* in_tfile_dc = new TFile( "data_covmat_energy_blockwise_recoCut_Sept19.root", "read" );
  //TFile* in_tfile_s = new TFile( "smearcept_energy_weighted_blockwise_recoCut_Sept19.root", "read" );
  //TFile* in_tfile_pts = new TFile( "prior_true_signal_energy_blockwise_recoCut_Sept19.root", "read" );
  //BLOCKWISE ANGLE
  //TFile* in_tfile_ds = new TFile( "data_signal_angle_MCONLY_blockwise_recoCut_Sept19.root", "read" );
  //TFile* in_tfile_dc = new TFile( "data_covmat_angle_blockwise_recoCut_Sept19.root", "read" );
  //TFile* in_tfile_s = new TFile( "smearcept_angle_weighted_blockwise_recoCut_Sept19.root", "read" );  //noTune, MEC
  //TFile* in_tfile_pts = new TFile( "prior_true_signal_angle_blockwise_recoCut_Sept19.root", "read" );  //noTune, MEC
  //BLOCKWISE MOM
  //TFile* in_tfile_ds = new TFile( "data_signal_leptonMom_MCONLY_blockwise_recoCut_Sept19.root", "read" );
  //TFile* in_tfile_dc = new TFile( "data_covmat_leptonMom_blockwise_recoCut_Sept19.root", "read" );
  //TFile* in_tfile_s = new TFile( "smearcept_leptonMom_weighted_blockwise_recoCut_Sept19.root", "read" );
  //TFile* in_tfile_pts = new TFile( "prior_true_signal_leptonMom_blockwise_recoCut_Sept19.root", "read" );


  //BLOCKWISE ANGLE RUN1
  //TFile* in_tfile_ds = new TFile( "data_signal_angle_MCONLY_blockwise_recoCut_run1_Sept19.root", "read" );
  //TFile* in_tfile_dc = new TFile( "data_covmat_angle_blockwise_recoCut_run1_Sept19.root", "read" );
  TFile* in_tfile_s = new TFile( "smearcept_angle_weighted_blockwise_recoCut_run1_Sept19.root", "read" ); //yes for nuWro
  TFile* in_tfile_pts = new TFile( "prior_true_signal_angle_blockwise_recoCut_run1_Sept19.root", "read" ); //yes for nuWro

  //BLOCKWISE ANGLE NUWRO
  TFile* in_tfile_ds = new TFile( "data_signal_angle_MCONLY_blockwise_recoCut_NuWro_Sept19.root", "read" );
  TFile* in_tfile_dc = new TFile( "data_covmat_angle_blockwise_recoCut_nuWro_Sept19.root", "read" );

  //BLOCKWISE ANGLE NOTUNE
  //TFile* in_tfile_ds = new TFile( "data_signal_angle_MCONLY_blockwise_recoCut_noTune_Sept19.root", "read" );
  //TFile* in_tfile_dc = new TFile( "data_covmat_angle_blockwise_recoCut_noTune_Sept19.root", "read" );

  //BLOCKWISE ANGLE MECTUNE
  //TFile* in_tfile_ds = new TFile( "data_signal_angle_MCONLY_blockwise_recoCut_MECTune_Sept19.root", "read" );
  //TFile* in_tfile_dc = new TFile( "data_covmat_angle_blockwise_recoCut_MECTune_Sept19.root", "read" );
  

  TMatrixD* data_signal = nullptr;
  TMatrixD* data_covmat = nullptr;
  TMatrixD* smearcept = nullptr;
  TMatrixD* prior_true_signal = nullptr;

  in_tfile_ds->GetObject( "data_signal", data_signal );
  in_tfile_dc->GetObject( "data_covmat", data_covmat );
  in_tfile_s->GetObject( "smearcept", smearcept );
  in_tfile_pts->GetObject( "prior_true_signal", prior_true_signal );

  //BLOCKWISE
  //std::unique_ptr<TFile> f(TFile::Open("energy_inputs_MCONLY_weighted_blockwise_recoCut_incErr_Sept19.root", "recreate"));
  //BLOCKWISE ANGLE
  //std::unique_ptr<TFile> f(TFile::Open("angle_inputs_MCONLY_weighted_blockwise_recoCut_incErr_Sept19.root", "recreate"));
  //BLOCKWISE MOM
  //std::unique_ptr<TFile> f(TFile::Open("leptonMom_inputs_MCONLY_weighted_blockwise_recoCut_incErr_Sept19.root", "recreate"));

  //BLOCKWISE ANGLE RUN1
  //std::unique_ptr<TFile> f(TFile::Open("angle_inputs_MCONLY_weighted_blockwise_recoCut_incErr_run1_Sept19.root", "recreate"));
  //BLOCKWISE ANGLE NUWRO
  std::unique_ptr<TFile> f(TFile::Open("angle_inputs_MCONLY_weighted_blockwise_recoCut_incErr_nuWro_Sept19.root", "recreate"));
  //BLOCKWISE ANGLE NOTUNE
  //std::unique_ptr<TFile> f(TFile::Open("angle_inputs_MCONLY_weighted_blockwise_recoCut_incErr_noTune_Sept19.root", "recreate"));
  //BLOCKWISE ANGLE MECTUNE
  //std::unique_ptr<TFile> f(TFile::Open("angle_inputs_MCONLY_weighted_blockwise_recoCut_incErr_MECTune_Sept19.root", "recreate"));
  
  f->WriteObject(data_signal, "data_signal");
  f->WriteObject(data_covmat, "data_covmat");
  f->WriteObject(smearcept, "smearcept");
  f->WriteObject(prior_true_signal, "prior_true_signal");
   
  f->Close();
 
}
