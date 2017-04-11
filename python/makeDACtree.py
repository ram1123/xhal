import ast
from array import array
from ROOT import TFile, TTree, vector

filename = "DACData.root"

myF = TFile(filename,'recreate')
myT = TTree('dacTree','Tree Holding CMS GEM DAC Data')

Nev = array( 'i', [ 0 ] )
#Nev[0] = 2
myT.Branch( 'Nev', Nev, 'Nev/I' )
dacname = vector('string')()
dacname.push_back("N/A")
myT.Branch( 'dacname', dacname )
dacinval = array( 'i', [ 0 ] )
myT.Branch( 'dacinval', dacinval, 'dacinval/I' )
dacoutval = array( 'i', [ 0 ] )
myT.Branch( 'dacoutval', dacoutval, 'dacoutval/I' )
vfatN = array( 'i', [ 0 ] )
myT.Branch( 'vfatN', vfatN, 'vfatN/I' )
link = array( 'i', [ 0 ] )
myT.Branch( 'link', link, 'link/I' )
link[0] = 0

#scans = [
#    "IPREAMPIN"   ,
#    "IPREAMPFEED" ,
#    "IPREAMPOUT"  ,
#    "ISHAPER"     ,
#    "ISHAPERFEED" ,
#    "ICOMP"       ,
#    "VTHRESHOLD1" ,
#    "VTHRESHOLD2" ,
#    "VCAL"        ,
#    "CALOUTVLOW"  ,
#    "CALOUTVHI"   ,
#]

with open("DACData.txt","r") as f:
  for line in f.readlines():
    data = ast.literal_eval(line)
    print "data type (expected dict):"
    print type(data)
    dactype = next(iter(data))
    print "Key (DAC Name) %s" %(dactype)
    dacname[0] = str(dactype)
    #print "dac_data type (expected list):"
    #print type(dac_data)
    for event in data[dactype]:
      vfatN[0] = int(event[0])
      dacinval[0] = int(event[1])
      dacoutval[0] = int(event[2])
      myT.Fill()
    myT.AutoSave("SaveSelf")

myF.cd()
myT.Write()
myF.Close()

