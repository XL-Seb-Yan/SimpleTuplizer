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

#include "SimpleTuplizer/PFLPEleTuplizer/interface/MiniAODPFele.h"

class MiniAODPFeleTuplizer : public edm::EDAnalyzer {
  public:
    explicit MiniAODPFeleTuplizer (const edm::ParameterSet&);
    ~MiniAODPFeleTuplizer() {}

  private:
    void beginJob(void) override ;
    void analyze(const edm::Event&, const edm::EventSetup&) override;
    void endJob() override;
      
  public:
    MINIAODANA::MiniAODPFele* pfEle;
    
  private:
    // output file
    edm::Service<TFileService> fs_;
    
    // tree
    TTree * tree_;
	
	edm::EDGetTokenT<std::vector<pat::Electron> > electronToken_;
};

MiniAODPFeleTuplizer::MiniAODPFeleTuplizer(const edm::ParameterSet& iConfig):
   electronToken_(consumes<std::vector<pat::Electron>>(iConfig.getParameter<edm::InputTag>("electrons")))
    
{
  pfEle = new MINIAODANA::MiniAODPFele();
  
	// set up output
	tree_=fs_->make<TTree>("PfEleTree", "PfEleTree");
	tree_->Branch("nPFEle", &(pfEle->nPFEle));
	tree_->Branch("ptPFEle", &(pfEle->ptPFEle));
	tree_->Branch("etaPFEle", &(pfEle->etaPFEle));
	tree_->Branch("phiPFEle", &(pfEle->phiPFEle));
	tree_->Branch("energyPFEle", &(pfEle->energyPFEle));
	tree_->Branch("chargePFEle", &(pfEle->chargePFEle));
	tree_->Branch("isMvaIDwp80PFEle", &(pfEle->isMvaIDwp80PFEle));
	tree_->Branch("isMvaIDwp90PFEle", &(pfEle->isMvaIDwp90PFEle));
	tree_->Branch("isMvaIDwpLoosePFEle", &(pfEle->isMvaIDwpLoosePFEle));
}


void MiniAODPFeleTuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  pfEle->Reset();

  edm::Handle<std::vector<pat::Electron> > electrons;
  iEvent.getByToken(electronToken_, electrons);
  
  pfEle->SetEvt(iEvent);

  if (electrons.isValid()){ 
    pfEle->SetPFEle(electrons);
  } else {
    edm::LogWarning("MissingProduct") << "Electrons not found. Branch will not be filled" << std::endl;
  }
  
  tree_->Fill();
	int i=0;

}

// ------------ method called once each job just before starting event loop  ------------
void 
MiniAODPFeleTuplizer::beginJob(void)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MiniAODPFeleTuplizer::endJob() {
}


//define this as a plug-in
DEFINE_FWK_MODULE(MiniAODPFeleTuplizer);