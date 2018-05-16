import os
from ctypes import *

lib = CDLL(os.getenv("XHAL_ROOT")+"/lib/x86_64/librpcman.so")
rBlock = lib.getBlock
rBlock.restype = c_uint
rBlock.argtypes=[c_uint,POINTER(c_uint32)]
getRPCTTCmain = lib.getmonTTCmain
getRPCTTCmain.argtypes = [POINTER(c_uint32)]
getRPCTTCmain.restype = c_uint

getRPCTRIGGERmain = lib.getmonTRIGGERmain
getRPCTRIGGERmain.argtypes = [POINTER(c_uint32), c_uint32]
getRPCTRIGGERmain.restype = c_uint

getRPCTRIGGEROHmain = lib.getmonTRIGGEROHmain
getRPCTRIGGEROHmain.argtypes = [POINTER(c_uint32), c_uint32]
getRPCTRIGGEROHmain.restype = c_uint

getRPCDAQmain = lib.getmonDAQmain
getRPCDAQmain.argtypes = [POINTER(c_uint32)]
getRPCDAQmain.restype = c_uint

getRPCDAQOHmain = lib.getmonDAQOHmain
getRPCDAQOHmain.argtypes = [POINTER(c_uint32), c_uint32]
getRPCDAQOHmain.restype = c_uint

getRPCOHmain = lib.getmonOHmain
getRPCOHmain.argtypes = [POINTER(c_uint32), c_uint32]
getRPCOHmain.restype = c_uint

rList = lib.getList
rList.restype = c_uint
rList.argtypes=[POINTER(c_uint32),POINTER(c_uint32)]

update_atdb = lib.update_atdb
update_atdb.argtypes = [c_char_p]
update_atdb.restype = c_uint
