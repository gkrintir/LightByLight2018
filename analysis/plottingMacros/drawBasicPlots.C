#include "../include/Helpers.hpp"

//string inputPath  = "../results/basicPlots_default.root";
//string inputPath  = "../results/basicPlots_tracks+nhits11.root";
//string inputPath  = "../results/basicPlots_tracks+nhits7.root";
//string inputPath  = "../results/basicPlots_tracks+chi2_2p5.root";
//string inputPath  = "../results/basicPlots_tracks+pt500.root";
//string inputPath  = "../results/basicPlots_test.root";
string inputPath  = "../results/basicPlots_test_new.root";
string outputPath = "../plots/distributions";

map<EDataset, double> initialNevents = {
//  { kMCqedSC, 67820000  }, // total
  { kMCqedSC, 960000    }, // currently available
  { kMClbl  , 362000    }, // currently available
  { kMCcep  , 144900    }, // currently available
};

map<EDataset, double> crossSection = { // μb
  { kMCqedSC, 8830    },
  { kMClbl  , 2.59    },
//  { kMCcep  , 5.8  },
  { kMCcep  , 0.0058  },
};

//double luminosity = 1847.99; // from CMS pages, 1/μb
double luminosity = 1609.910015010; // from brilcalc, 1/μb

const double markerSize = 0.5;

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
  kData,
  kMCcep,
  kMCqedSC,
//  kMCqedSL,
  kMClbl,
};

const double goldenRatio = 1.61803398875;
const int baseHistWidth  = 600;
const int baseHistHeight = baseHistWidth/goldenRatio;

vector<tuple<string, int, int>> canvasParams = {
  // title       col row
  {"Photon"       , 2 , 2 },
  {"Diphoton"     , 2 , 3 },
  {"Triphoton"    , 2 , 2 },
  {"Electron"     , 2 , 2 },
  {"Dielectron"   , 2 , 3 },
  {"Same sign ee" , 2 , 2 },
  {"QED calo"     , 2 , 2 },
  {"tracks"       , 4 , 4 },
};

vector<tuple<string, string, bool, bool, int, int, int, double, double>> histParams = {
  // title                            x axis title                  log Y  norm?  iCanvas iPad rebin xMin xMax
  { "lbl_photon_et_all"               , "photon E_{t} (GeV)"      , false, false ,   0   , 1  , 1 ,   0  , 30  },
  { "lbl_photon_eta_all"              , "photon #eta"             , false, false ,   0   , 2  , 1 , -3.0 , 3.0 },
  { "lbl_photon_phi_all"              , "photon #phi"             , false, false ,   0   , 3  , 1 , -3.5 , 3.5 },
  { "lbl_nee_failing_all"             , ""                        , false, true  ,   0   , 4  , 1 ,   0  , 10  },
  
  { "lbl_acoplanarity_all"            , "A_{#phi}^{#gamma#gamma}" , false, false ,   1   , 1  , 1 ,   0  , 0.2 },
  { "lbl_diphoton_mass_all"           , "diphoton m_{inv} (GeV)"  , false, false ,   1   , 2  , 1 ,   0  , 50  },
  { "lbl_diphoton_pt_all"             , "diphoton p_{t}"          , false, false ,   1   , 3  , 1 ,   0  , 2.0 },
  { "lbl_diphoton_rapidity_all"       , "diphoton rapidity"       , false, false ,   1   , 4  , 1 , -3.0 , 3.0 },
  { "lbl_cut_flow_all"                , ""                        , false, true  ,   1   , 5  , 1 ,   0  , 10  },
  
  { "lbl_triphoton_mass_all"          , "triphoton m_{inv} (GeV)" , false, false ,   2   , 1  , 2 ,   0  , 30  },
  { "lbl_triphoton_rapidity_all"      , "triphoton rapidity"      , false, false ,   2   , 2  , 1 , -3.0 , 3.0 },
  { "lbl_triphoton_pt_all"            , "triphoton p_{t}"         , false, false ,   2   , 3  , 2 ,   0  , 30  },
  
  { "qed_electron_pt_all"             , "electron p_{t} (GeV)"    , false, false ,   3   , 1  , 1 ,   0  , 40  },
  { "qed_electron_eta_all"            , "electron #eta"           , false, false ,   3   , 2  , 1 , -2.5 , 2.5 },
  { "qed_electron_phi_all"            , "electron #phi"           , false, false ,   3   , 3  , 1 , -3.5 , 3.5 },
  { "qed_electron_cutflow_all"        , ""                        , false, false ,   3   , 4  , 1 ,   0  , 12  },
  
  { "qed_acoplanarity_all"            , "A_{#phi}^{e^{+}e^{-}}"   , true , false ,   4   , 1  , 1 ,   0  , 0.1 },
  { "qed_dielectron_mass_all"         , "dielectron m_{inv} (GeV)", false, false ,   4   , 2  , 1 ,   0  , 100 },
  { "qed_dielectron_pt_all"           , "dielectron p_{t}"        , false, false ,   4   , 3  , 1 ,   0  , 2.0 },
  { "qed_dielectron_rapidity_all"     , "dielectron rapidity"     , false, false ,   4   , 4  , 1 ,  -3.0, 3.0 },
  { "qed_cut_flow_all"                , ""                        , false, true  ,   4   , 5  , 1 ,   0  , 10  },
  
  { "samesign_dielectron_mass_all"    , "dielectron m_{inv} (GeV)", false, false ,   5   , 1  , 1 ,   0  , 100 },
  { "samesign_dielectron_pt_all"      , "dielectron p_{t}"        , false, false ,   5   , 2  , 1 ,   0  , 2.0 },
  { "samesign_dielectron_rapidity_all", "dielectron rapidity"     , false, false ,   5   , 3  , 1 ,  -3.0, 3.0 },
  
  { "qed_HFp_all"                     , "HF+ energy (GeV)"        , true , true  ,   6   , 1  , 1 ,   0  , 20  },
  { "qed_HFm_all"                     , "HF- energy (GeV)"        , true , true  ,   6   , 2  , 1 ,   0  , 20  },
  { "qed_HFp_leading_tower_all"       , "HF+ leading energy (GeV)", true , true  ,   6   , 3  , 1 ,   0  , 20  },
  { "qed_HFm_leading_tower_all"       , "HF- leading energy (GeV)", true , true  ,   6   , 4  , 1 ,   0  , 20  },
  
  
  { "track_charge_all"                , "track charge"            , false, false ,   7   , 1  , 1 ,   -1 , 2   },
  { "track_eta_all"                   , "track #eta"              , false, false ,   7   , 2  , 1 , -3.0 , 3.0 },
  { "track_phi_all"                   , "track #phi"              , false, false ,   7   , 3  , 1 , -3.5 , 3.5 },
  { "track_dxy_all"                   , "track d_{xy} (cm)"       , true , false ,   7   , 4  , 1 ,  -10 , 10  },
  { "track_dz_all"                    , "track d_{z} (cm)"        , true , false ,   7   , 5  , 1 ,  -30 , 30  },
  { "track_dxy_over_sigma_all"        , "|d_{xy}/#sigma_{xy}|"    , true , false ,   7   , 6  , 2 ,    0 , 10  },
  { "track_dz_over_sigma_all"         , "|d_{xy}/#sigma_{z}|"     , true , false ,   7   , 7  , 2 ,    0 , 10  },
  { "track_vx_all"                    , "track vertex x (cm)"     , true , false ,   7   , 8  , 1 ,  -10 , 10  },
  { "track_vy_all"                    , "track vertex y (cm)"     , true , false ,   7   , 9  , 1 ,  -10 , 10  },
  { "track_vz_all"                    , "track vertex z (cm)"     , true , false ,   7   , 10 , 1 ,  -30 , 30  },
  { "track_valid_hits_all"            , "N_{hits}^{valid}"        , false, false ,   7   , 11 , 1 ,   0  , 30  },
  { "track_missing_hits_all"          , "N_{hits}^{missing}"      , false, false ,   7   , 12 , 1 ,   0  , 20  },
  { "track_chi2_all"                  , "track #chi^{2}/NDF"      , true , true  ,   7   , 13 , 1 ,   0  , 20  },
  { "track_purity_all"                , "track purity"            , false, false ,   7   , 14 , 1 ,   0  , 20  },
  { "tracks_cut_flow_all"              , ""                       , false, true  ,   7   , 15 , 1 ,   0  , 10  },
};

void fillLabels(TH1D *hist, vector<const char*> labels)
{
  int i=1;
  for(auto label : labels){
    hist->GetXaxis()->SetBinLabel(i, label);
    hist->GetXaxis()->ChangeLabel(i, 45);
    i++;
  }
  hist->LabelsOption("u", "X");
}

void setCutflowLabels(TH1D *hist, bool lbl)
{
  vector<const char *> labelsQED = {
    "Initial", "Trigger", "NEE", "CHE", "2 good electrons", "opposite q",
    "dielectron m_{inv}", "dielectron p_{t}", "dielectron y"
  };
  vector<const char *> labelsLbL = {
    "Initial", "Trigger", "CHE", "NEE", "2 good photons",
    "diphoton m_{inv}", "diphoton p_{t}", "diphoton y", "acoplanarity"
  };
  fillLabels(hist, lbl ? labelsLbL : labelsQED);
}

void setCaloLabels(TH1D *hist)
{
  vector<const char *> labels = { "EB", "EE", "HB", "HE", "HF+", "HF-" };
  fillLabels(hist, labels);
}

void setElectronCutsLabels(TH1D *hist)
{
  vector<const char *> labels = {
    "Initial", "p_{t}", "Cracks", "#eta", "HEM", "missing hits",
    "H/E", "#Delta#eta seed", "Iso charge", "Iso photon", "Iso neutral"
  };
  fillLabels(hist, labels);
}

void setTrackCutsLabels(TH1D *hist)
{
  vector<const char *> labels = {
    "Initial", "p_{t}", "Eta", "d_{xy}", "|d_{xy}/#sigma_{xy}|",
    "d_{z}", "|d_{z}/#sigma_{z}|", "N_{hits}^{valid}", "#chi^{2}" };
  fillLabels(hist, labels);
}

map<EDataset, string> legendOptions = {
  {kData,     "elp" },
  {kMCcep,    "f"   },
  {kMCqedSL,  "f"   },
  {kMCqedSC,  "f"   },
  {kMClbl,    "f"   },
};

void prepareHist(TH1D *hist, EDataset dataset)
{
  hist->SetLineColor(datasetColor.at(dataset));
  hist->SetFillColorAlpha(datasetColor.at(dataset), 0.2);
  
  hist->SetMarkerColor(datasetColor.at(dataset));
  hist->SetMarkerStyle(20);
  hist->SetMarkerSize(markerSize);
  
//  hist->Scale(1./hist->GetEntries());
//  hist->Sumw2(false);
}



map<EDataset, TH1D*> getHistsFromFile(TFile *inFile, string histName)
{
  map<EDataset, TH1D*> hists;
  
  for(EDataset dataset : datasetsToAnalyze){
    hists[dataset] = (TH1D*)inFile->Get((histName+"_"+datasetName.at(dataset)).c_str());
    if(!hists[dataset]){
      cout<<"ERROR -- no histogram \""<<histName<<"\" found for dataset "<<datasetName.at(dataset)<<endl;
      continue;
    }
    prepareHist(hists[dataset], dataset);
  }
  return hists;
}

TLegend* getLegendForHists(map<EDataset, TH1D*> hists)
{
  TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.9 );
  for(EDataset dataset : datasetsToAnalyze){
    legend->AddEntry(hists[dataset], datasetDescription.at(dataset).c_str(), legendOptions[dataset].c_str());
  }
  return legend;
}

int getTotalBackgroundEntries(map<EDataset, TH1D*> hists)
{
  int totalBackgroundEntries = 0;
  
  for(EDataset dataset : datasetsToAnalyze){
    if(!hists[dataset]) continue;
    
    if(dataset != kData) totalBackgroundEntries += hists[dataset]->GetEntries();
  }
  return totalBackgroundEntries;
}

double getMaxHistValue(TH1D *hist)
{
  double max = -999999;
  for(int i=0; i<hist->GetNbinsX(); i++){
    double value = hist->GetBinContent(i);
    if(value > max) max = value;
  }
  return max;
}

double getMinHistValue(TH1D *hist)
{
  double min = 999999;
  for(int i=0; i<hist->GetNbinsX(); i++){
    double value = hist->GetBinContent(i);
    if(value < min) min = value;
  }
  return min;
}

double getMaxValueInHists(map<EDataset, TH1D*> hists)
{
  double maxValue = -999;
  
  for(EDataset dataset : datasetsToAnalyze){
    if(!hists[dataset]) continue;
    
    for(int i=0; i<hists[dataset]->GetNbinsX(); i++){
      double value = hists[dataset]->GetBinContent(i);
      if(value > maxValue) maxValue = value;
    }
  }
  return maxValue;
}

void normalizeHists(map<EDataset, TH1D*> hists, bool normalize, bool cutFlow, bool failingCalos)
{
  if(normalize){
    int totalBackgroundEntries = getTotalBackgroundEntries(hists);
    
    for(EDataset dataset : datasetsToAnalyze){
      if(!hists[dataset]) continue;
      
      if(hists[dataset]->GetEntries() == 0) continue;
      
      if(failingCalos){
        cout<<hists[dataset]->GetEntries();
        
        hists[dataset]->Scale(1./hists[dataset]->GetEntries());
      }
      
      if(dataset == kData) continue;
      
//      if(cutFlow) hists[dataset]->Scale(1./hists[dataset]->GetEntries());
      if(cutFlow)           hists[dataset]->Scale(1./hists[dataset]->GetBinContent(1)*hists[kData]->GetBinContent(1));
      else if(!failingCalos)hists[dataset]->Scale(1./totalBackgroundEntries);
//      hists[dataset]->Sumw2(false);
    }
  }
  else{
    for(EDataset dataset : datasetsToAnalyze){
      if(dataset == kData) continue;
      if(!hists[dataset]) continue;
      hists[dataset]->Scale(luminosity*crossSection[dataset]/initialNevents[dataset]);
//      hists[dataset]->Sumw2(false);
    }
  }
}

void drawBasicPlots()
{
  gStyle->SetOptStat(0);
  
  TFile *inFile = TFile::Open(inputPath.c_str());
  
  vector<TCanvas*> canvas;
  
  for(auto &[title, nCol, nRow] : canvasParams){
    canvas.push_back(new TCanvas(title.c_str(), title.c_str(), baseHistWidth*nCol, baseHistHeight*nRow));
    canvas.back()->Divide(nCol, nRow);
  }
  
  for(auto &[histName, xAxisTitle, logY, normalize, iCanvas, iPad, rebin, xMin, xMax] : histParams){
    
    map<EDataset, TH1D*> hists = getHistsFromFile(inFile, histName);
    
    
    THStack *backgroundsStack = new THStack();
    TH1D *dataHist;
    
    for(EDataset dataset : datasetsToAnalyze){
      if(!hists[dataset]) continue;
      
      hists[dataset]->Rebin(rebin);
      hists[dataset]->Scale(1./rebin);
      
      if(dataset != kData)  backgroundsStack->Add(hists[dataset]);
      else                  dataHist = hists[dataset];
    }
    //
    // Draw main plot
    //
    
    canvas[iCanvas]->cd(iPad);
    
    TPad *histsPad = new TPad("histsPad", "histsPad", 0.0, 0.0, 1., 1.);
    histsPad->SetTopMargin(0.1);
		histsPad->SetLeftMargin(0.15);
		histsPad->SetBottomMargin(0.4);
    histsPad->SetLogy(logY);
		histsPad->Draw();
		histsPad->cd();

    bool isCutFlow      = histName.find("cut_flow") != string::npos;
    bool isFailingcalos = histName.find("nee_failing") != string::npos;
    normalizeHists(hists, normalize, isCutFlow, isFailingcalos);
    
    if(histName == "lbl_acoplanarity_all"){
      double signal = dataHist->GetBinContent(1);
      double background = 0;
      for(int i=2; i<=dataHist->GetNbinsX(); i++){
        background += dataHist->GetBinContent(i);
      }
      background /= 25;
      cout<<"Significance: "<<(signal-background)/sqrt(signal)<<endl;
    }
    
    if(normalize){
      if(histName.find("cut_flow")    != string::npos
         || histName.find("nee_failing")  != string::npos
         ){
        //        dataHist->Scale(1./dataHist->GetBinContent(1));
        dataHist->Draw("PE");
      }
      else{
        dataHist->DrawNormalized("PE");
      }
    }
    else{
      dataHist->Draw("PE");
      dataHist->SetMaximum(1.5 * getMaxValueInHists(hists));
    }
    backgroundsStack->Draw((isCutFlow || isFailingcalos) ? "sameNostack" : "same");
    getLegendForHists(hists)->Draw();
    
    dataHist->SetTitle("");
    
    dataHist->GetXaxis()->SetTitle("");
    dataHist->GetXaxis()->SetTitleSize(0.06);
    dataHist->GetXaxis()->SetLabelSize(0);
    dataHist->GetXaxis()->SetRangeUser(xMin, xMax);
    
    dataHist->GetYaxis()->SetTitle("# events");
    dataHist->GetYaxis()->SetTitleSize(0.06);
    dataHist->GetYaxis()->SetTitleOffset(1.15);
    dataHist->GetYaxis()->SetLabelSize(0.06);
    
    //
    // Draw ratio
    //

    TPad *ratioPad = new TPad("ratioPad", "ratioPad", 0.0, 0.1, 1.0, 0.4);
    ratioPad->SetTopMargin(0);
    ratioPad->SetLeftMargin(0.15);
    ratioPad->SetBottomMargin(0.5);
    ratioPad->SetGrid();
    ratioPad->Draw();
    ratioPad->cd();

    TH1D *ratio = new TH1D(*dataHist);
    TH1D *backgroundsSum = nullptr;
    bool first = true;
    
    for(auto &[dataset, hist] : hists){
      if(dataset == kData) continue;
      if(!hists[dataset]) continue;
      
      if(first){
        backgroundsSum = new TH1D(*hist);
        first = false;
      }
      else{
        backgroundsSum->Add(hist);
      }
    }
    
    if(!backgroundsSum) continue;
    
    ratio->Divide(backgroundsSum);
    ratio->Draw();
    
    ratio->SetMaximum(1.2 * getMaxHistValue(ratio));
    ratio->SetMinimum(0.8 * getMinHistValue(ratio));
    
    ratio->SetTitle("");
    
    if(histName == "qed_cut_flow_all")          setCutflowLabels(ratio, false);
    if(histName == "lbl_cut_flow_all")          setCutflowLabels(ratio, true);
    if(histName == "qed_electron_cutflow_all")  setElectronCutsLabels(ratio);
    if(histName == "tracks_cut_flow_all")       setTrackCutsLabels(ratio);
    if(histName == "lbl_nee_failing_all")       setCaloLabels(ratio);
    
    
    ratio->GetXaxis()->SetTitle(xAxisTitle.c_str());
    ratio->GetXaxis()->SetTitleSize(0.2);
    ratio->GetXaxis()->SetTitleOffset(1.1);
    ratio->GetXaxis()->SetLabelSize(0.2);
    
    if(histName.find("cut_flow") != string::npos || histName.find("nee_failing") != string::npos){
      ratio->GetXaxis()->SetLabelSize(0.16);
      ratio->GetXaxis()->SetLabelOffset(0.055);
      ratioPad->SetBottomMargin(0.55);
    }
    
    ratio->GetYaxis()->SetTitle("Data/MC ");
    ratio->GetYaxis()->SetTitleSize(0.17);
    ratio->GetYaxis()->SetTitleOffset(0.3);
    ratio->GetYaxis()->SetLabelSize(0.15);
    ratio->GetYaxis()->SetNdivisions(5);
    
  }
    
    
  canvas[0]->SaveAs((outputPath+"_LbL.pdf").c_str());
  canvas[1]->SaveAs((outputPath+"_QED.pdf").c_str());
  canvas[2]->SaveAs((outputPath+"_Calo.pdf").c_str());
  canvas[3]->SaveAs((outputPath+"_QED_no_cuts.pdf").c_str());
}
