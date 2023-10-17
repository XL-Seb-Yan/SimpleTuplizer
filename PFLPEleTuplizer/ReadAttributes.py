## Need to run with python3

import ROOT
from DataFormats.FWLite import Handle, Events

# Set up electron handle and label
electrons = Handle("std::vector<pat::Electron>")
# electronLabel = ("slimmedLowPtElectrons", "", "RECO")
electronLabel = ("slimmedElectrons", "", "RECO")

# Event loop
events = Events('/eos/home-x/xuyan/RKProj/lowpt/RunF.root') # Replace 'file.root' with your file

for iev, event in enumerate(events):
    if iev > 0: break
    event.getByLabel(electronLabel, electrons)
    
    # Loop over electrons in the event
    for i, electron in enumerate(electrons.product()):
        if i > 0: break;
        print(electron.userIntNames())
        # print(dir(electron))