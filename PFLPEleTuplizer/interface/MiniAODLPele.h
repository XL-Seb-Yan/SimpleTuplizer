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
  class MiniAODLPele
  {
  public:
    enum {TEST=0};
    MiniAODLPele();
    ~MiniAODLPele();
    void SetEvt(const edm::Event& iEvent);
		void SetLPEle(const edm::Handle<std::vector<pat::Electron> > electrons);
	
		unsigned int evtEvent;
    unsigned int evtRun;
    unsigned int evtLumiBlock;
		
		// Low pt electron
		unsigned short int nLPEle;
    std::vector<float> ptLPEle;
    std::vector<float> etaLPEle;
    std::vector<float> phiLPEle;
    std::vector<float> energyLPEle;
    std::vector<int> chargeLPEle;
    std::vector<float> lpMvaIdIDLPEle;
    std::vector<float> lpMvaIdptbiasedLPEle;
	  std::vector<float> lpMvaIdunbiasedLPEle;
		
		
		void Reset()
		{
		nLPEle = 0;
		ptLPEle.clear();
		etaLPEle.clear();
		phiLPEle.clear();
		energyLPEle.clear();
		chargeLPEle.clear();
		lpMvaIdIDLPEle.clear();
		lpMvaIdptbiasedLPEle.clear();
		lpMvaIdunbiasedLPEle.clear();
		}
		
  };
}