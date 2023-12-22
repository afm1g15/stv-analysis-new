void csvToTMatrixD_blockwise() {

   ifstream in;
   std::string dummy;
   TMatrixT<double> matrix(20,1);
   //TMatrixT<double> matrix(16,1);
   int x;
   char c;
   int sum = 0;
   
   //INPUT
   //in.open("../../PELEE/nue_full_500_catsel_nopions_recoE_usingSelection_data_signal_MCONLY_blockwise_recoCut_comb_nonzero_Sept19.csv", std::ios::binary);
   //in.open("../../PELEE/nue_full_500_catsel_nopions_recoE_usingSelection_prior_true_signal_blockwise_recoCut_comb_nonzero_Sept19.csv", std::ios::binary);
   //INPUTS ANGLE
   //in.open("../../PELEE/nue_full_500_catsel_nopions_angleDiff_usingSelection_data_signal_MCONLY_blockwise_recoCut_comb_Sept19.csv", std::ios::binary); 
   //in.open("../../PELEE/nue_full_500_catsel_nopions_angleDiff_usingSelection_prior_true_signal_blockwise_recoCut_comb_Sept19.csv", std::ios::binary);  //in noTune
   //INPUTS MOM
   //in.open("../../PELEE/nue_full_500_catsel_nopions_leptonMom_usingSelection_data_signal_MCONLY_blockwise_recoCut_comb_Sept19.csv", std::ios::binary);
   //in.open("../../PELEE/nue_full_500_catsel_nopions_leptonMom_usingSelection_prior_true_signal_blockwise_recoCut_comb_Sept19.csv", std::ios::binary);

   //ANGLE NUWRO
   //in.open("../../PELEE/data_signal_MC_nuWro_input_angleDiff_comb_Sept19.csv", std::ios::binary);
   in.open("../../PELEE/nue_full_500_catsel_nopions_angleDiff_usingSelection_prior_true_signal_blockwise_recoCut_Sept19.csv", std::ios::binary);
   //in.open("../../PELEE/nue_full_500_catsel_nopions_angleDiff_usingSelection_data_signal_MCONLY_blockwise_recoCut_Sept19.csv", std::ios::binary);

   //ANGLE NO TUNE
   //in.open("../../PELEE/data_signal_MC_noTune_input_angleDiff_comb_Sept19.csv", std::ios::binary);

   //ANGLE MEC TUNE
   //in.open("../../PELEE/data_signal_MC_MECTune_input_angleDiff_comb_Sept19.csv", std::ios::binary);
   
   
   if (!in.is_open()) {
      std::cout << "failed to open csv!" << '\n';
      return;
   }

   int i = 0;
   for (std::string line; std::getline(in, line);){
	matrix(i,0)=std::stod(line);
	i++;
   }
   
   matrix.Print();
   std::cout << std::setprecision(17) << matrix(1,0) << std::endl;

   //OUTPUTS
   //std::unique_ptr<TFile> f(TFile::Open("data_signal_energy_MCONLY_blockwise_recoCut_nonzero_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");
   //std::unique_ptr<TFile> f(TFile::Open("prior_true_signal_energy_blockwise_recoCut_nonzero_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "prior_true_signal");
   //OUTPUTS ANGLE
   //std::unique_ptr<TFile> f(TFile::Open("data_signal_angle_MCONLY_blockwise_recoCut_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");
   //std::unique_ptr<TFile> f(TFile::Open("prior_true_signal_angle_blockwise_recoCut_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "prior_true_signal");
   //OUTPUTS MOM
   //std::unique_ptr<TFile> f(TFile::Open("data_signal_leptonMom_MCONLY_blockwise_recoCut_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");
   //std::unique_ptr<TFile> f(TFile::Open("prior_true_signal_leptonMom_blockwise_recoCut_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "prior_true_signal");

   //OUTPUTS ANGLE NUWRO
   // std::unique_ptr<TFile> f(TFile::Open("data_signal_angle_MCONLY_blockwise_recoCut_NuWro_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");
   std::unique_ptr<TFile> f(TFile::Open("prior_true_signal_angle_blockwise_recoCut_run1_Sept19.root", "recreate"));
   f->WriteObject(&matrix, "prior_true_signal");
   //std::unique_ptr<TFile> f(TFile::Open("data_signal_angle_MCONLY_blockwise_recoCut_run1_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");

   //OUTPUTS ANGLE NOTUNE
   //std::unique_ptr<TFile> f(TFile::Open("data_signal_angle_MCONLY_blockwise_recoCut_noTune_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");

   //OUTPUTS ANGLE MECTUNE
   //std::unique_ptr<TFile> f(TFile::Open("data_signal_angle_MCONLY_blockwise_recoCut_MECTune_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");
   
   
   f->Close();

}
