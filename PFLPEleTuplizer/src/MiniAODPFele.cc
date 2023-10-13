#include "SimpleTuplizer/PFLPEleTuplizer/interface/MiniAODPFele.h"

MINIAODANA::MiniAODPFele::MiniAODPFele()
{
}

MINIAODANA::MiniAODPFele::~MiniAODPFele()
{
}

void MINIAODANA::MiniAODPFele::SetEvt(const edm::Event& iEvent)
{
    evtEvent = iEvent.id().event();
    evtRun = iEvent.id().run();
    evtLumiBlock = iEvent.id().luminosityBlock();
    
}

void MINIAODANA::MiniAODPFele::SetPFEle(const edm::Handle<std::vector<pat::Electron> > electrons)
{
  int nPFEles = 0;
  for (const pat::Electron &el : *electrons) {
    nPFEles++;
    if (el.pt() < 0.5) continue;
    ptPFEle.push_back(el.pt());
    etaPFEle.push_back(el.eta());
    phiPFEle.push_back(el.phi());
    energyPFEle.push_back(el.energy());
    chargePFEle.push_back(el.charge());
    isMvaIDwp80PFEle.push_back(el.electronID("mvaEleID-Fall17-iso-V2-wp80"));
    isMvaIDwp90PFEle.push_back(el.electronID("mvaEleID-Fall17-iso-V2-wp90"));
		isMvaIDwpLoosePFEle.push_back(el.electronID("mvaEleID-Fall17-iso-V2-wpLoose"));
    }
  nPFEle = nPFEles;
}