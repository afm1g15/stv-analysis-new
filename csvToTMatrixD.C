void csvToTMatrixD() {

   ifstream in;
   std::string dummy;
   //TMatrixT<double> matrix(10,1);
   TMatrixD matrix(10,1);
   int x;
   char c;
   int sum = 0;
   
   //NUE ENERGY
   //in.open("../PELEE/nue_full_500_catsel_nopions_recoE_usingSelection_data_signal.csv", std::ios::binary);
   // in.open("../PELEE/nue_full_500_catsel_nopions_recoE_usingSelection_prior_true_signal.csv", std::ios::binary);
   //NUMU ENERGY
   //in.open("../PELEE/numu_full_500_catsel_nopions_recoE_usingSelection_data_signal.csv", std::ios::binary);
   in.open("../PELEE/numu_full_500_catsel_nopions_recoE_usingSelection_prior_true_signal.csv", std::ios::binary);
   
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

   //NUE ENERGY
   //std::unique_ptr<TFile> f(TFile::Open("data_signal_nue_energy.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");
   //std::unique_ptr<TFile> f(TFile::Open("prior_true_signal_nue_energy.root", "recreate"));
   //f->WriteObject(&matrix, "prior_true_signal");
   
   //NUMU ENERGY
   //std::unique_ptr<TFile> f(TFile::Open("data_signal_numu_energy.root", "recreate"));
   //f->WriteObject(&matrix, "data_signal");
   std::unique_ptr<TFile> f(TFile::Open("prior_true_signal_numu_energy.root", "recreate"));
   f->WriteObject(&matrix, "prior_true_signal");
   
   f->Close();

}
