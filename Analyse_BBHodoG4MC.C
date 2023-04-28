#include <TLorentzVector.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TSystem.h>

#include <iostream>
#include <fstream>

using namespace std;

const Bool_t ApplyThresh     = true;
const Bool_t ApplyWindow     = true;

const Double_t Hodo_threshold = 1.0;
const Double_t Hodo_window    = 50;

void Analyse_BBHodoG4MC(  ) {
  
  //-----------------------------------------------------------------------------------------------------------------------------

  TChain* TOut = new TChain("TOut");
  
  TOut->Add("batch_beam.root");

  const Int_t     Maxprim = 50;
  const Int_t     Maxhits = 10000;

  Double_t         Event_weight;
  Int_t           Event_flag;
  Int_t           Event_num;
  Int_t           Primary_Nhits;
  Int_t           Primary_pdg[Maxprim];
  Double_t         Primary_E[Maxprim];
  Double_t         Primary_x[Maxprim];
  Double_t         Primary_y[Maxprim];
  Double_t         Primary_z[Maxprim];
  Double_t         Primary_px[Maxprim];
  Double_t         Primary_py[Maxprim];
  Double_t         Primary_pz[Maxprim];
  Int_t           Virtual_Nhits;
  Int_t           Virtual_pdg[Maxhits];
  Int_t           Virtual_det[Maxhits];
  Int_t           Virtual_mod[Maxhits];
  Int_t           Virtual_row[Maxhits];
  Int_t           Virtual_col[Maxhits];
  Int_t           Virtual_tid[Maxhits];
  Int_t           Virtual_pid[Maxhits];
  Double_t         Virtual_E[Maxhits];
  Double_t         Virtual_t[Maxhits];
  Double_t         Virtual_x[Maxhits];
  Double_t         Virtual_y[Maxhits];
  Double_t         Virtual_z[Maxhits];
  Double_t         Virtual_px[Maxhits];
  Double_t         Virtual_py[Maxhits];
  Double_t         Virtual_pz[Maxhits];
  Double_t         Virtual_vx[Maxhits];
  Double_t         Virtual_vy[Maxhits];
  Double_t         Virtual_vz[Maxhits];
  Int_t           Real_Nhits;
  Int_t           Real_det[Maxhits];
  Int_t           Real_mod[Maxhits];
  Int_t           Real_row[Maxhits];
  Int_t           Real_col[Maxhits];
  Double_t         Real_edep[Maxhits];
  Double_t         Real_t[Maxhits];
  Double_t         Real_x[Maxhits];
  Double_t         Real_y[Maxhits];
  Double_t         Real_z[Maxhits];
  
  TOut->SetBranchAddress("Event_weight",&Event_weight);
  TOut->SetBranchAddress("Event_flag",&Event_flag);
  TOut->SetBranchAddress("Event_num",&Event_num);
  TOut->SetBranchAddress("Primary_Nhits",&Primary_Nhits);
  TOut->SetBranchAddress("Primary_pdg",Primary_pdg);
  TOut->SetBranchAddress("Primary_E",Primary_E);
  TOut->SetBranchAddress("Primary_x",Primary_x);
  TOut->SetBranchAddress("Primary_y",Primary_y);
  TOut->SetBranchAddress("Primary_z",Primary_z);
  TOut->SetBranchAddress("Primary_px",Primary_px);
  TOut->SetBranchAddress("Primary_py",Primary_py);
  TOut->SetBranchAddress("Primary_pz",Primary_pz);
  TOut->SetBranchAddress("Virtual_Nhits",&Virtual_Nhits);
  TOut->SetBranchAddress("Virtual_pdg",Virtual_pdg);
  TOut->SetBranchAddress("Virtual_det",Virtual_det);
  TOut->SetBranchAddress("Virtual_mod",Virtual_mod);
  TOut->SetBranchAddress("Virtual_row",Virtual_row);
  TOut->SetBranchAddress("Virtual_col",Virtual_col);
  TOut->SetBranchAddress("Virtual_tid",Virtual_tid);
  TOut->SetBranchAddress("Virtual_pid",Virtual_pid);
  TOut->SetBranchAddress("Virtual_E",Virtual_E);
  TOut->SetBranchAddress("Virtual_t",Virtual_t);
  TOut->SetBranchAddress("Virtual_x",Virtual_x);
  TOut->SetBranchAddress("Virtual_y",Virtual_y);
  TOut->SetBranchAddress("Virtual_z",Virtual_z);
  TOut->SetBranchAddress("Virtual_px",Virtual_px);
  TOut->SetBranchAddress("Virtual_py",Virtual_py);
  TOut->SetBranchAddress("Virtual_pz",Virtual_pz);
  TOut->SetBranchAddress("Virtual_vx",Virtual_vx);
  TOut->SetBranchAddress("Virtual_vy",Virtual_vy);
  TOut->SetBranchAddress("Virtual_vz",Virtual_vz);
  TOut->SetBranchAddress("Real_Nhits",&Real_Nhits);
  TOut->SetBranchAddress("Real_det",Real_det);
  TOut->SetBranchAddress("Real_mod",Real_mod);
  TOut->SetBranchAddress("Real_row",Real_row);
  TOut->SetBranchAddress("Real_col",Real_col);
  TOut->SetBranchAddress("Real_edep",Real_edep);
  TOut->SetBranchAddress("Real_t",Real_t);
  TOut->SetBranchAddress("Real_x",Real_x);
  TOut->SetBranchAddress("Real_y",Real_y);
  TOut->SetBranchAddress("Real_z",Real_z);

  gStyle->SetOptFit(0);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);

  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);

  gStyle->SetPadTopMargin(.05);
  gStyle->SetPadLeftMargin(.18);
  gStyle->SetPadRightMargin(.18);
  gStyle->SetPadBottomMargin(.15);

  gStyle->SetTitleOffset(1.1, "X");
  gStyle->SetTitleOffset(1.5, "Y");
  gStyle->SetTitleFont(42,"X");
  gStyle->SetTitleFont(42,"Y");
  gStyle->SetTitleSize(0.055,"X");
  gStyle->SetTitleSize(0.055,"Y");

  gStyle->SetLabelOffset(0.01, "X");
  gStyle->SetLabelOffset(0.01, "Y");
  gStyle->SetLabelFont(42,"X");
  gStyle->SetLabelFont(42,"Y");
  gStyle->SetLabelSize(0.045,"X");
  gStyle->SetLabelSize(0.045,"Y");

  gStyle->SetNdivisions(105,"X");
  gStyle->SetNdivisions(105,"Y");

  gStyle->SetStripDecimals(kFALSE);

  Long64_t nentries = TOut->GetEntries();
  Int_t ntrees      = TOut->GetNtrees();
  
  cout << "Processing TOut chain with " << ntrees << " trees and " << nentries << " total events" << endl;

  //-----------------------------------------------------------------------------------------------------------------------------
  
  TH1F* hPrim_N   = new TH1F("hPrim_N",  "", 100,0.,2.);
  TH1F* hPrim_E   = new TH1F("hPrim_E",  "", 100,0.,3000.);
  TH1F* hPrim_z   = new TH1F("hPrim_z",  "", 100,-400.,0.);
  TH1F* hPrim_pdg = new TH1F("hPrim_pdg",  "", 100,-300.,3000.);
  TH2F* hPrim_xy  = new TH2F("hPrim_xy", "", 100,-1.0,1.0, 100,-1.,1. );

  TH1F* hHodo_N   = new TH1F("hHodo_N",  "", 90,0.,90.);
  TH1F* hHodo_E   = new TH1F("hHodo_E",  "", 100,0.,3000.);
  TH1F* hHodo_z   = new TH1F("hHodo_z",  "", 100,0.,500.);
  TH1F* hHodo_pdg = new TH1F("hHodo_pdg",  "", 100,-300.,3000.);
  TH2F* hHodo_xy  = new TH2F("hHodo_xy", "", 100,-50.,50., 100,-100.,100. );

  TH1F* hRealHodo_N   = new TH1F("hRealHodo_N",  "", 90,0.,90.);
  TH1F* hRealHodo_E   = new TH1F("hRealHodo_E",  "", 100,0.,50.);
  TH1F* hRealHodo_z   = new TH1F("hRealHodo_z",  "", 100,0.,500.);
  TH1F* hRealHodo_t   = new TH1F("hRealHodo_t",  "", 100, 0.,50.);
  TH2F* hRealHodo_xy  = new TH2F("hRealHodo_xy", "", 100,-50.,50., 100,-100.,100. );

  //-----------------------------------------------------------------------------------------------------------------------------

  for(Long64_t ev=0; ev<nentries;ev++) {
    
    TOut->GetEntry(ev);
    
    if( ev%10000 == 0 )
      cout << ev << endl;
    
    // Primary variables
    hPrim_N->Fill( (Double_t)Primary_Nhits );
    for( int i =0; i < Primary_Nhits; i++ ) {
      
      hPrim_E->Fill( Primary_E[i] , Event_weight );
      hPrim_xy->Fill( Primary_x[i], Primary_y[i] , Event_weight );
      hPrim_z->Fill( Primary_z[i] , Event_weight );
      hPrim_pdg->Fill( (Double_t)Primary_pdg[i] , Event_weight );
    }
    
    // Virutal variables
    for( int i =0; i < Virtual_Nhits; i++ ) {

      if( Virtual_pdg[i] == 22 ) continue;

      Int_t id = Virtual_row[i];
      hHodo_N->Fill( (Double_t)id , Event_weight );
      hHodo_E->Fill( Virtual_E[i] , Event_weight );
      hHodo_xy->Fill( Virtual_x[i], Virtual_y[i] , Event_weight );
      hHodo_z->Fill( Virtual_z[i] , Event_weight );
      hHodo_pdg->Fill( (Double_t)Virtual_pdg[i] , Event_weight );
    }
    
    // Real variables
    for( int i =0; i < Real_Nhits; i++ ) {

      if( ApplyThresh && Real_edep[i] > Hodo_threshold ) { 
	if( ApplyWindow && Real_t[i] < Hodo_window ) {
	  
	  Int_t id = Real_row[i];
	  hRealHodo_N->Fill( (Double_t)id, Event_weight );
	  hRealHodo_E->Fill( Real_edep[i], Event_weight );
	  hRealHodo_xy->Fill( Real_x[i], Real_y[i], Event_weight );
	  hRealHodo_z->Fill( Real_z[i], Event_weight );
	  hRealHodo_t->Fill( (Double_t)Real_t[i], Event_weight );
	}
      }
    }
    
  }

  //-----------------------------------------------------------------------------------------------------------------------------

  TLatex* tex;

  TCanvas* cPrim = new TCanvas("cPrim","",1200,800);
  cPrim->Divide(3,2);
  
  cPrim->cd(1);
  
  tex = new TLatex( 0.24, 0.7, "BBHodoG4MC");
  tex->SetNDC(1);
  tex->SetTextFont(42);
  tex->SetTextColor(1);
  tex->SetTextSize(0.095);
  tex->Draw();
  
  tex = new TLatex( 0.24, 0.3, "Primaries");
  tex->SetNDC(1);
  tex->SetTextFont(42);
  tex->SetTextColor(1);
  tex->SetTextSize(0.095);
  tex->Draw();
    
  cPrim->cd(2);
  hPrim_N->SetLineColor(4);
  hPrim_N->Draw("hist e4");
  hPrim_N->GetXaxis()->SetTitle("Num Primary Particles");

  cPrim->cd(3)->SetLogy(1);
  hPrim_pdg->SetLineColor(4);
  hPrim_pdg->Draw("hist e4");
  hPrim_pdg->GetXaxis()->SetTitle("PDG code");

  cPrim->cd(4);
  hPrim_E->SetLineColor(4);
  hPrim_E->Draw("hist e4");
  hPrim_E->GetXaxis()->SetTitle("Kinetic Energy [MeV]");

  cPrim->cd(5);
  hPrim_xy->Draw("colz");
  hPrim_xy->GetXaxis()->SetTitle("x [cm]");
  hPrim_xy->GetYaxis()->SetTitle("y [cm]");

  cPrim->cd(6);
  hPrim_z->SetLineColor(4);
  hPrim_z->Draw("hist e4");
  hPrim_z->GetXaxis()->SetTitle("z [cm]");

  cPrim->Print("tempa.pdf");  

  //-----------------------------------------------------------------------------------------------------------------------------

  TCanvas* cVirt1 = new TCanvas("cVirt1","",1200,800);
  cVirt1->Divide(3,2);
  
  cVirt1->cd(1);
  
  tex = new TLatex( 0.24, 0.7, "BBHodoG4MC");
  tex->SetNDC(1);
  tex->SetTextFont(42);
  tex->SetTextColor(1);
  tex->SetTextSize(0.095);
  tex->Draw();

  tex = new TLatex( 0.24, 0.3, "Virtual");
  tex->SetNDC(1);
  tex->SetTextFont(42);
  tex->SetTextColor(1);
  tex->SetTextSize(0.095);
  tex->Draw();
    
  cVirt1->cd(2);
  hHodo_N->SetLineColor(4);
  hHodo_N->Draw("hist e4");
  hHodo_N->GetXaxis()->SetTitle("Bar ID");

  cVirt1->cd(3)->SetLogy(1);
  hHodo_pdg->SetLineColor(4);
  hHodo_pdg->Draw("hist e4");
  hHodo_pdg->GetXaxis()->SetTitle("PDG code");

  cVirt1->cd(4)->SetLogy(1);
  hHodo_E->SetLineColor(4);
  hHodo_E->Draw("hist e4");
  hHodo_E->GetXaxis()->SetTitle("Kinetic Energy [MeV]");

  cVirt1->cd(5);
  hHodo_xy->Draw("colz");
  hHodo_xy->GetXaxis()->SetTitle("x [cm]");
  hHodo_xy->GetYaxis()->SetTitle("y [cm]");

  cVirt1->cd(6);
  hHodo_z->SetLineColor(4);
  hHodo_z->Draw("hist e4");
  hHodo_z->GetXaxis()->SetTitle("z [cm]");

  cVirt1->Print("tempb.pdf");  

  //-----------------------------------------------------------------------------------------------------------------------------

  TCanvas* cReal1 = new TCanvas("cReal1","",1200,800);
  cReal1->Divide(3,2);
  
  cReal1->cd(1);
  
  tex = new TLatex( 0.24, 0.7, "BBHodoG4MC");
  tex->SetNDC(1);
  tex->SetTextFont(42);
  tex->SetTextColor(1);
  tex->SetTextSize(0.095);
  tex->Draw();

  tex = new TLatex( 0.24, 0.3, "Real");
  tex->SetNDC(1);
  tex->SetTextFont(42);
  tex->SetTextColor(1);
  tex->SetTextSize(0.095);
  tex->Draw();
    
  cReal1->cd(2);
  hRealHodo_N->SetLineColor(4);
  hRealHodo_N->Draw("hist e4");
  hRealHodo_N->GetXaxis()->SetTitle("Bar ID");

  cReal1->cd(3);
  hRealHodo_t->SetLineColor(4);
  hRealHodo_t->Draw("hist e4");
  hRealHodo_t->GetXaxis()->SetTitle("Time [ns]");

  cReal1->cd(4)->SetLogy(1);
  hRealHodo_E->SetLineColor(4);
  hRealHodo_E->Draw("hist e4");
  hRealHodo_E->GetXaxis()->SetTitle("Energy Deposit [MeV]");

  cReal1->cd(5);
  hRealHodo_xy->Draw("colz");
  hRealHodo_xy->GetXaxis()->SetTitle("x [cm]");
  hRealHodo_xy->GetYaxis()->SetTitle("y [cm]");

  cReal1->cd(6);
  hRealHodo_z->SetLineColor(4);
  hRealHodo_z->Draw("hist e4");
  hRealHodo_z->GetXaxis()->SetTitle("z [cm]");

  cReal1->Print("tempe.pdf");  

  
  //-----------------------------------------------------------------------------------------------------------------------------
  
  gSystem->Exec("pdfunite  temp*.pdf BBHodoG4MC.pdf");  
  gSystem->Exec("rm temp*.pdf");  
  
}

//-----------------------------------------------------------------------------------------------------------------------------
