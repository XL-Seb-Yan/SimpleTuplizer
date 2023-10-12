#include "SimpleTuplizer/PFLPEleTuplizer/interface/MiniAODPFele.h"

MINIAODANA::MiniAODPFele::MiniAODPFele()
{
}

MINIAODANA::MiniAODPFele::~MiniAODPFele()
{
}

void MINIAODANA::MiniAODPFele::SetEvt(const edm::Event& iEvent)
{
    pfEle_.evtEvent = iEvent.id().event();
    pfEle_.evtRun = iEvent.id().run();
    pfEle_.evtLumiBlock = iEvent.id().luminosityBlock();
    
}

void MINIAODANA::MiniAODPFele::SetEle(const edm::Handle<std::vector<pat::Electron> > electrons)
{
  int nEles = 0;
  for (const pat::Electron &el : *electrons) {
    nEles++;
    if (el.pt() < 2) continue;
    pfEle_.ptEle.push_back(el.pt());
    pfEle_.etaEle.push_back(el.eta());
    pfEle_.phiEle.push_back(el.phi());
    pfEle_.energyEle.push_back(el.energy());
    pfEle_.chargeEle.push_back(el.charge());
    pfEle_.isMvaIDwp80Ele.push_back(el.electronID("mvaEleID-Fall17-iso-V2-wp80"));
    pfEle_.isMvaIDwp90Ele.push_back(el.electronID("mvaEleID-Fall17-iso-V2-wp90"));
    }
	int j=0;
	
  pfEle_.nEle = nEles;
}