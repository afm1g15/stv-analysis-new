void csvToTMatrixD_blockwise() {

   ifstream in;
   std::string dummy;
   //TH1D matrix(20);
   TVectorT<double> matrix(20);
   int x;
   char c;
   int sum = 0;
   
   //ANGLE NOTUNE
   //in.open("../../../PELEE/data_signal_MC_noTune_chi2_angleDiff_comb_Sept19_noTune.csv", std::ios::binary);
   //in.open("../../../PELEE/prior_true_MC_noTune_chi2_angleDiff_comb_Sept19_noTune.csv", std::ios::binary);

   //in.open("../../../PELEE/data_signal_MC_MECTune_chi2_angleDiff_comb_Sept19_MECTune.csv", std::ios::binary);
   in.open("../../../PELEE/prior_true_MC_MECTune_chi2_angleDiff_comb_Sept19_MECTune.csv", std::ios::binary);

   //in.open("../../../PELEE/data_signal_MC_nuWro_chi2_angleDiff_comb_Sept19.csv", std::ios::binary);
   //in.open("../../../PELEE/prior_true_MC_nuWro_chi2_angleDiff_comb_Sept19.csv", std::ios::binary);

   
   
   if (!in.is_open()) {
      std::cout << "failed to open csv!" << '\n';
      return;
   }

   int i = 0;
   for (std::string line; std::getline(in, line);){
        matrix(i)=std::stod(line);
	i++;
   }
   
   matrix.Print();
   std::cout << std::setprecision(17) << matrix(1) << std::endl;

 

   //OUTPUTS ANGLE NUWRO
   //std::unique_ptr<TFile> f(TFile::Open("data_signal_TH1D_angle_MCONLY_blockwise_recoCut_noTune_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");
   //std::unique_ptr<TFile> f(TFile::Open("prior_true_signal_TH1D_angle_blockwise_recoCut_noTune_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "prior_true_signal");

   //std::unique_ptr<TFile> f(TFile::Open("data_signal_TH1D_angle_MCONLY_blockwise_recoCut_MECTune_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");
   std::unique_ptr<TFile> f(TFile::Open("prior_true_signal_TH1D_angle_blockwise_recoCut_MECTune_Sept19.root", "recreate"));
   f->WriteObject(&matrix, "prior_true_signal");

   //std::unique_ptr<TFile> f(TFile::Open("data_signal_TH1D_angle_MCONLY_blockwise_recoCut_nuWro_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");
   //std::unique_ptr<TFile> f(TFile::Open("prior_true_signal_TH1D_angle_blockwise_recoCut_nuWro_Sept19.root", "recreate"));
   //f->WriteObject(&matrix, "prior_true_signal");
   
   f->Close();

}
