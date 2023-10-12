#include <vector>
#include <string>
#include <TROOT.h>

namespace MINIAODANA
{
  struct MiniAODPFeleDataFormat
  {
    MiniAODPFeleDataFormat(){ Reset();};
    ~MiniAODPFeleDataFormat(){};
   
    unsigned int evtEvent;
    unsigned int evtRun;
    unsigned int evtLumiBlock;
    
    unsigned short int nEle;
    std::vector<float> ptEle;
    std::vector<float> etaEle;
    std::vector<float> phiEle;
    std::vector<float> energyEle;
    std::vector<int> chargeEle;
    std::vector<bool> isMvaIDwp80Ele;
    std::vector<bool> isMvaIDwp90Ele;
	
	void Reset()
    {
      nEle = 0;
      ptEle.clear();
      etaEle.clear();
      phiEle.clear();
      energyEle.clear();
      chargeEle.clear();
      isMvaIDwp80Ele.clear();
      isMvaIDwp90Ele.clear();
    }

  }; 
}