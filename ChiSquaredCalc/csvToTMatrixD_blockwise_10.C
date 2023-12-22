void csvToTMatrixD_blockwise_10() {

   ifstream in;
   std::string dummy;
   TMatrixD matrix(20, 20);
   //TMatrixD matrix(16, 16);

   //INPUTS

   //INPUT ANGLE1
   //in.open("../../../PELEE/data_covmat_MC_noTune_chi2_angleDiff_comb_Sept19.csv", std::ios::binary);
   //in.open("../../../PELEE/data_covmat_MC_MECTune_chi2_angleDiff_comb_Sept19.csv", std::ios::binary);
   in.open("../../../PELEE/data_covmat_MC_nuWro_chi2_angleDiff_comb_Sept19.csv", std::ios::binary);
   
   
   if (!in.is_open()) {
      std::cout << "failed to open csv!" << '\n';
      return;
   }

   int count = 0;
   while (in.is_open() && !in.eof()) {
     double a, b, k, d, e, f, g, h, i, j, l, v, n, o, p, q, r, s, t, u;
     char c;
     in >> a >> c >> b >> c >> k >> c >> d >> c >> e >> c >> f >> c >> g >> c >> h >> c >> i >> c >> j >> c >> l >> c >> v >> c >> n >> c >> o >> c >> p >> c >> q >> c >> r >> c >> s >> c >> t >> c >> u;
     double set[20] = {a, b, k, d, e, f, g, h, i, j, l, v, n, o, p, q, r, s, t, u};
     //in >> a >> c >> b >> c >> k >> c >> d >> c >> e >> c >> f >> c >> g >> c >> h >> c >> i >> c >> j >> c >> l >> c >> v >> c >> n >> c >> o >> c >> p >> c >> q;
     //double set[16] = {a, b, k, d, e, f, g, h, i, j, l, v, n, o, p, q};

     for (int m=0;m < 20; m++){
       matrix(count,m)=set[m];
     }
     count++;
     if (count == 20){
       break;
     }
   }
   
   matrix.Print();
   std::cout << std::setprecision(17) << matrix(1,0) << std::endl;

   //OUTPUTS

   //OUTPUT ANGLE
   //std::unique_ptr<TFile> f(TFile::Open("data_covmat_TH2D_angle_MCONLY_blockwise_recoCut_noTune_Sept19.root", "recreate"));
   //std::unique_ptr<TFile> f(TFile::Open("data_covmat_TH2D_angle_MCONLY_blockwise_recoCut_MECTune_Sept19.root", "recreate"));
   std::unique_ptr<TFile> f(TFile::Open("data_covmat_TH2D_angle_MCONLY_blockwise_recoCut_nuWro_Sept19.root", "recreate"));
   
   f->WriteObject(&matrix, "data_covmat");
   

   
   f->Close();

}
