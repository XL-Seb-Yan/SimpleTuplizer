// system include files
#include <memory>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"

#include "SimpleTuplizer/PFLPEleTuplizer/interface/MiniAODLPele.h"

class MiniAODLPeleTuplizer : public edm::EDAnalyzer {
  public:
    explicit MiniAODLPeleTuplizer (const edm::ParameterSet&);
    ~MiniAODLPeleTuplizer() {}

  private:
    void beginJob(void) override ;
    void analyze(const edm::Event&, const edm::EventSetup&) override;
    void endJob() override;
      
  public:
    MINIAODANA::MiniAODLPele* lpEle;
    
  private:
    // output file
    edm::Service<TFileService> fs_;
    
    // tree
    TTree * tree_;
	
	edm::EDGetTokenT<std::vector<pat::Electron> > electronToken_;
};

MiniAODLPeleTuplizer::MiniAODLPeleTuplizer(const edm::ParameterSet& iConfig):
   electronToken_(consumes<std::vector<pat::Electron>>(iConfig.getParameter<edm::InputTag>("electrons")))
    
{
  lpEle = new MINIAODANA::MiniAODLPele();
  
	// set up output
	tree_=fs_->make<TTree>("LpEleTree", "LpEleTree");
	tree_->Branch("nLPEle", &(lpEle->nLPEle));
	tree_->Branch("ptLPEle", &(lpEle->ptLPEle));
	tree_->Branch("etaLPEle", &(lpEle->etaLPEle));
	tree_->Branch("phiLPEle", &(lpEle->phiLPEle));
	tree_->Branch("energyLPEle", &(lpEle->energyLPEle));
	tree_->Branch("chargeLPEle", &(lpEle->chargeLPEle));
	tree_->Branch("lpMvaIdIDLPEle", &(lpEle->lpMvaIdIDLPEle));
	tree_->Branch("lpMvaIdptbiasedLPEle", &(lpEle->lpMvaIdptbiasedLPEle));
	tree_->Branch("lpMvaIdunbiasedLPEle", &(lpEle->lpMvaIdunbiasedLPEle));
}


void MiniAODLPeleTuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  lpEle->Reset();

  edm::Handle<std::vector<pat::Electron> > electrons;
  iEvent.getByToken(electronToken_, electrons);
  
  lpEle->SetEvt(iEvent);

  if (electrons.isValid()){ 
    lpEle->SetLPEle(electrons);
  } else {
    edm::LogWarning("MissingProduct") << "Electrons not found. Branch will not be filled" << std::endl;
  }
  
  tree_->Fill();

}

// ------------ method called once each job just before starting event loop  ------------
void 
MiniAODLPeleTuplizer::beginJob(void)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MiniAODLPeleTuplizer::endJob() {
}


//define this as a plug-in
DEFINE_FWK_MODULE(MiniAODLPeleTuplizer);