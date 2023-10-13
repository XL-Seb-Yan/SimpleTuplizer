//MC spfElection
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                  // access to gROOT, entry point to ROOT system
#include <TSystem.h>                // interface to OS
#include <TFile.h>                  // file handle class
#include <TDirectoryFile.h>
#include <TTree.h>                  // class to access ntuples
#include <TClonesArray.h>           // ROOT array class
#include <TBenchmark.h>             // class to track macro running statistics
#include <TVector2.h>               // 2D vector class
#include <TVector3.h>               // 2D vector class
#include <TMath.h>                  // ROOT math library
#include <vector>                   // STL vector class
#include <utility>
#include <iostream>                 // standard I/O
#include <iomanip>                  // functions to format standard I/O
#include <fstream>                  // functions for file I/O
#include <bitset>
#include "TLorentzVector.h"         // 4-vector class
#include <THStack.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TF1.h>
#include <TStopwatch.h>
#include <TMatrixD.h>
#include <TArrayD.h>
#include <TMatrixDEigen.h>
#include <TVectorD.h>
#include "TH1D.h"
#include "TRandom3.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
// C++ tool
#include <algorithm>
#include <map>
#endif

using namespace std;
using namespace ROOT;

void Skimmer() { 
	
	gROOT->SetBatch(1);
	
	// Data Structure for output skimmed files
	float pfEle_pt_0, pfEle_pt_1;
	float pfEle_eta_0, pfEle_eta_1;
	float pfEle_phi_0, pfEle_phi_1;
	float pfEle_energy_0, pfEle_energy_1;
	float pfDiEle_invmass;
	
	float lpEle_pt_0, lpEle_pt_1;
	float lpEle_eta_0, lpEle_eta_1;
	float lpEle_phi_0, lpEle_phi_1;
	float lpEle_energy_0, lpEle_energy_1;
	float lpDiEle_invmass;
	
	UInt_t run_num;
	ULong64_t evt_num;
	Int_t lumi_block;
	
	TString inFileName = "SimpleNtuple.root";
	TString outFileName = "SimpleNtuple_2Eleskim.root";
	TFile *infile = TFile::Open(inFileName);
	TDirectoryFile *df = (TDirectoryFile*)infile->Get("PFTree");
	TTree *eventTree = (TTree*)df->Get("PfEleTree");
	cout<<eventTree<<endl;
	
	TFile *outfile = TFile::Open(outFileName, "RECREATE");
	TTree *pfoutTree = new TTree("PfEleTree","PfEleTree");
	pfoutTree->Branch("pfEle_pt_0", &pfEle_pt_0);
	pfoutTree->Branch("pfEle_pt_1", &pfEle_pt_1);
	pfoutTree->Branch("pfEle_eta_0", &pfEle_eta_0);
	pfoutTree->Branch("pfEle_eta_1", &pfEle_eta_1);
	pfoutTree->Branch("pfEle_phi_0", &pfEle_phi_0);
	pfoutTree->Branch("pfEle_phi_1", &pfEle_phi_1);
	pfoutTree->Branch("pfEle_energy_0", &pfEle_energy_0);
	pfoutTree->Branch("pfEle_energy_1", &pfEle_energy_1);
	pfoutTree->Branch("pfDiEle_invmass", &pfDiEle_invmass);
		
	TTreeReader fReader_PF; 		//!the tree reader
	TTreeReaderValue<unsigned short int> nPFEleReader = {fReader_PF, "nPFEle"};
	TTreeReaderValue<std::vector<float>> ptPFEleReader = {fReader_PF, "ptPFEle"};
	TTreeReaderValue<std::vector<float>> etaPFEleReader = {fReader_PF, "etaPFEle"};
	TTreeReaderValue<std::vector<float>> phiPFEleReader = {fReader_PF, "phiPFEle"};
	TTreeReaderValue<std::vector<float>> energyPFEleReader = {fReader_PF, "energyPFEle"};
	TTreeReaderValue<std::vector<int>> chargePFEleReader = {fReader_PF, "chargePFEle"};
	TTreeReaderValue<std::vector<bool>> isMvaIDwp80PFEleReader = {fReader_PF, "isMvaIDwp80PFEle"};
	TTreeReaderValue<std::vector<bool>> isMvaIDwp90PFEleReader = {fReader_PF, "isMvaIDwp90PFEle"};
	TTreeReaderValue<std::vector<bool>> isMvaIDwpLoosePFEleReader = {fReader_PF, "isMvaIDwpLoosePFEle"};
	fReader_PF.SetTree(eventTree);
	
	for(UInt_t ientry=0; ientry<eventTree->GetEntries(); ientry++){
		fReader_PF.SetLocalEntry(ientry);
		if(ientry%20000 == 0) cout<<"Processing: "<<ientry<<" out of: "<<eventTree->GetEntries()<<endl;
		
		if(*nPFEleReader < 2) continue;
		std::vector<TLorentzVector> goodPFEles;
		for(int ipfPFEle=0; ipfPFEle < ptPFEleReader->size(); ipfPFEle++){
			if(isMvaIDwp90PFEleReader->at(ipfPFEle)){
				TLorentzVector el;
				el.SetPtEtaPhiE(ptPFEleReader->at(ipfPFEle),etaPFEleReader->at(ipfPFEle),phiPFEleReader->at(ipfPFEle),energyPFEleReader->at(ipfPFEle));
				goodPFEles.push_back(el);
			}
		}
		if(goodPFEles.size() < 2) continue;

		pfEle_pt_0 = goodPFEles.at(0).Pt();
		pfEle_pt_1 = goodPFEles.at(1).Pt();
		pfEle_eta_0 = goodPFEles.at(0).Eta();
		pfEle_eta_1 = goodPFEles.at(1).Eta();
		pfEle_phi_0 = goodPFEles.at(0).Phi();
		pfEle_phi_1 = goodPFEles.at(1).Phi();
		pfEle_energy_0 = goodPFEles.at(0).E();
		pfEle_energy_1 = goodPFEles.at(1).E();
		pfDiEle_invmass = (goodPFEles.at(0)+goodPFEles.at(1)).M();
		
		pfoutTree->Fill();
	}// End of event loop
	
	df = (TDirectoryFile*)infile->Get("LPTree");
	eventTree = (TTree*)df->Get("LpEleTree");
	TTree *lpoutTree = new TTree("LpEleTree","LpEleTree");
	lpoutTree->Branch("lpEle_pt_0", &lpEle_pt_0);
	lpoutTree->Branch("lpEle_pt_1", &lpEle_pt_1);
	lpoutTree->Branch("lpEle_eta_0", &lpEle_eta_0);
	lpoutTree->Branch("lpEle_eta_1", &lpEle_eta_1);
	lpoutTree->Branch("lpEle_phi_0", &lpEle_phi_0);
	lpoutTree->Branch("lpEle_phi_1", &lpEle_phi_1);
	lpoutTree->Branch("lpEle_energy_0", &lpEle_energy_0);
	lpoutTree->Branch("lpEle_energy_1", &lpEle_energy_1);
	lpoutTree->Branch("lpDiEle_invmass", &lpDiEle_invmass);
		
	TTreeReader fReader_LP; 		//!the tree reader
	TTreeReaderValue<unsigned short int> nLPEleReader = {fReader_LP, "nLPEle"};
	TTreeReaderValue<std::vector<float>> ptLPEleReader = {fReader_LP, "ptLPEle"};
	TTreeReaderValue<std::vector<float>> etaLPEleReader = {fReader_LP, "etaLPEle"};
	TTreeReaderValue<std::vector<float>> phiLPEleReader = {fReader_LP, "phiLPEle"};
	TTreeReaderValue<std::vector<float>> energyLPEleReader = {fReader_LP, "energyLPEle"};
	TTreeReaderValue<std::vector<int>> chargeLPEleReader = {fReader_LP, "chargeLPEle"};
	TTreeReaderValue<std::vector<float>> lpMvaIdIDLPEleReader = {fReader_LP, "lpMvaIdIDLPEle"};
	TTreeReaderValue<std::vector<float>> lpMvaIdptbiasedLPEleReader = {fReader_LP, "lpMvaIdptbiasedLPEle"};
	TTreeReaderValue<std::vector<float>> lpMvaIdunbiasedLPEleReader = {fReader_LP, "lpMvaIdunbiasedLPEle"};
	fReader_LP.SetTree(eventTree);
	
	for(UInt_t ientry=0; ientry<eventTree->GetEntries(); ientry++){
		fReader_LP.SetLocalEntry(ientry);
		if(ientry%20000 == 0) cout<<"Processing: "<<ientry<<" out of: "<<eventTree->GetEntries()<<endl;
		
		if(*nLPEleReader < 2) continue;
		std::vector<TLorentzVector> goodLPEles;
		for(int ipfLPEle=0; ipfLPEle < ptLPEleReader->size(); ipfLPEle++){
			if(lpMvaIdIDLPEleReader->at(ipfLPEle) > 0.5){
				TLorentzVector el;
				el.SetPtEtaPhiE(ptLPEleReader->at(ipfLPEle),etaLPEleReader->at(ipfLPEle),phiLPEleReader->at(ipfLPEle),energyLPEleReader->at(ipfLPEle));
				goodLPEles.push_back(el);
			}
		}
		if(goodLPEles.size() < 2) continue;

		lpEle_pt_0 = goodLPEles.at(0).Pt();
		lpEle_pt_1 = goodLPEles.at(1).Pt();
		lpEle_eta_0 = goodLPEles.at(0).Eta();
		lpEle_eta_1 = goodLPEles.at(1).Eta();
		lpEle_phi_0 = goodLPEles.at(0).Phi();
		lpEle_phi_1 = goodLPEles.at(1).Phi();
		lpEle_energy_0 = goodLPEles.at(0).E();
		lpEle_energy_1 = goodLPEles.at(1).E();
		lpDiEle_invmass = (goodLPEles.at(0)+goodLPEles.at(1)).M();
		
		lpoutTree->Fill();
	}// End of event loop
	
	outfile->cd();
	outfile->Write();
	outfile->Close();
	infile->Close();
}