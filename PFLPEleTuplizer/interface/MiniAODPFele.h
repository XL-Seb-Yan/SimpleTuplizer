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
#include "MiniAODPFeleDataFormat.h"

namespace MINIAODANA
{
  class MiniAODPFele
  {
  public:
    enum {TEST=0};
    MiniAODPFele();
    ~MiniAODPFele();
    void Reset() {pfEle_.Reset();}
    void SetEvt(const edm::Event& iEvent);
    void SetEle(const edm::Handle<std::vector<pat::Electron> > electrons);
    MiniAODPFeleDataFormat * getData() {return &pfEle_;}

  private:
    MiniAODPFeleDataFormat pfEle_;
  };
}