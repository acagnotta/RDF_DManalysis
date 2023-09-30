chmod 600 .globus/usercert.pem
chmod 600 .globus/userkey.pem

voms-proxy-init --voms cms --key .globus/userkey.pem --cert .globus/usercert.pem

scp acagnott@lxplus.cern.ch:/afs/cern.ch/work/a/acagnott/CMSSW_12_4_7/src/PhysicsTools/NanoAODTools/python/postprocessing/variables.py acagnott@lxplus.cern.ch:/afs/cern.ch/work/a/acagnott/CMSSW_12_4_7/src/PhysicsTools/NanoAODTools/python/postprocessing/samples/dict_samples.pkl acagnott@lxplus.cern.ch:/afs/cern.ch/work/a/acagnott/CMSSW_12_4_7/src/PhysicsTools/NanoAODTools/python/postprocessing/samples/samples.py acagnott@lxplus.cern.ch:/afs/cern.ch/work/a/acagnott/CMSSW_12_4_7/src/PhysicsTools/NanoAODTools/python/postprocessing/postselection.h ./utils/.