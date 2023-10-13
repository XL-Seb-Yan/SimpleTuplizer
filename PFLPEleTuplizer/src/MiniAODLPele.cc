#include "SimpleTuplizer/PFLPEleTuplizer/interface/MiniAODLPele.h"

MINIAODANA::MiniAODLPele::MiniAODLPele()
{
}

MINIAODANA::MiniAODLPele::~MiniAODLPele()
{
}

void MINIAODANA::MiniAODLPele::SetEvt(const edm::Event& iEvent)
{
    evtEvent = iEvent.id().event();
    evtRun = iEvent.id().run();
    evtLumiBlock = iEvent.id().luminosityBlock();
    
}

void MINIAODANA::MiniAODLPele::SetLPEle(const edm::Handle<std::vector<pat::Electron> > electrons)
{
  int nLPEles = 0;
  for (const pat::Electron &el : *electrons) {
    nLPEles++;
    if (el.pt() < 0.5) continue;
    ptLPEle.push_back(el.pt());
    etaLPEle.push_back(el.eta());
    phiLPEle.push_back(el.phi());
    energyLPEle.push_back(el.energy());
    chargeLPEle.push_back(el.charge());
    lpMvaIdIDLPEle.push_back(el.electronID("ID"));
    lpMvaIdptbiasedLPEle.push_back(el.electronID("ptbiased"));
		lpMvaIdunbiasedLPEle.push_back(el.electronID("unbiased"));
    }
  nLPEle = nLPEles;
}