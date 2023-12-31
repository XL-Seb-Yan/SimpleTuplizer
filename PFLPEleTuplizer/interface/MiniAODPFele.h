#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "FWCore/Framework/interface/Event.h"

namespace MINIAODANA
{
  class MiniAODPFele
  {
  public:
    enum {TEST=0};
    MiniAODPFele();
    ~MiniAODPFele();
    void SetEvt(const edm::Event& iEvent);
    void SetPFEle(const edm::Handle<std::vector<pat::Electron> > electrons);
		
		unsigned int evtEvent;
    unsigned int evtRun;
    unsigned int evtLumiBlock;
    
		// PF electron
    unsigned short int nPFEle;
    std::vector<float> ptPFEle;
    std::vector<float> etaPFEle;
    std::vector<float> phiPFEle;
    std::vector<float> energyPFEle;
    std::vector<int> chargePFEle;
    std::vector<bool> isMvaIDwp80PFEle;
    std::vector<bool> isMvaIDwp90PFEle;
	  std::vector<bool> isMvaIDwpLoosePFEle;
		
		void Reset()
		{
		nPFEle = 0;
		ptPFEle.clear();
		etaPFEle.clear();
		phiPFEle.clear();
		energyPFEle.clear();
		chargePFEle.clear();
		isMvaIDwp80PFEle.clear();
		isMvaIDwp90PFEle.clear();
		isMvaIDwpLoosePFEle.clear();
		}
		
  };
}