void csvToTMatrixD_10() {

   ifstream in;
   std::string dummy;
   TMatrixD matrix(10,10);

   //NUE ENERGY
   //in.open("../PELEE/nue_full_500_catsel_nopions_recoE_usingSelection_data_covmat.csv", std::ios::binary);
   //in.open("../PELEE/nue_full_500_catsel_nopions_recoE_usingSelection_smearcept.csv", std::ios::binary);
   
   //NUMU ENERGY
   //in.open("../PELEE/numu_full_500_catsel_nopions_recoE_usingSelection_data_covmat.csv", std::ios::binary);
   in.open("../PELEE/numu_full_500_catsel_nopions_recoE_usingSelection_smearcept.csv", std::ios::binary);
   
   if (!in.is_open()) {
      std::cout << "failed to open csv!" << '\n';
      return;
   }

   int count = 0;
   while (in.is_open() && !in.eof()) {
     double a, b, k, d, e, f, g, h, i, j;
     char c;
     in >> a >> c >> b >> c >> k >> c >> d >> c >> e >> c >> f >> c >> g >> c >> h >> c >> i >> c >> j;
     std::cout << a << c << b << c << k << c << d << c << e << c << f << c << g << c << h << c << i << c << j << std::endl;
     double set[10] = {a, b, k, d, e, f, g, h, i, j};
     for (int m=0;m < 10; m++){
       matrix(count,m)=set[m];
     }
     count++;
     if (count == 10){
       break;
     }
   }
   
   matrix.Print();
   std::cout << std::setprecision(17) << matrix(1,0) << std::endl;

   //NUE ENERGY
   //std::unique_ptr<TFile> f(TFile::Open("data_covmat_nue_energy.root", "recreate"));
   //f->WriteObject(&matrix, "data_covmat");
   //std::unique_ptr<TFile> f(TFile::Open("smearcept_nue_energy.root", "recreate"));
   //f->WriteObject(&matrix, "smearcept");

   //NUMU ENERGY
   //std::unique_ptr<TFile> f(TFile::Open("data_covmat_numu_energy.root", "recreate"));
   //f->WriteObject(&matrix, "data_covmat");
   std::unique_ptr<TFile> f(TFile::Open("smearcept_numu_energy.root", "recreate"));
   f->WriteObject(&matrix, "smearcept");
   
   f->Close();

}
