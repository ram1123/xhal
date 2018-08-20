import xhalpy as xi
import os

def w1(str):
    print (str)
    wait = raw_input()
    return

print os.getpid()
#w1('starting main..press a key')
eagle64=xi.XHALInterface("eagle64","/opt/cmsgemos/etc/maps/amc_address_table_top.xml")
eagle64.init()
eagle64.loadModule("memory","memory v1.0.1")
#print "read reg by name: eagle64.readReg(GEM_AMC.GEM_SYSTEM.BOARD_ID)=%s"%(eagle64.readReg("GEM_AMC.GEM_SYSTEM.BOARD_ID"))
print "read reg by address: eagle64.readReg(0x66400008)=%s"%(eagle64.readReg(0x66400008))
