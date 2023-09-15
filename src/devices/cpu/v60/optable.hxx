// license:BSD-3-Clause
// copyright-holders:Farfetch'd, R. Belmont
const v60_device::am_func v60_device::s_OpCodeTable[256] =
{
	/* 0x00 */ &v60_device::opHALT,
	/* 0x01 */ &v60_device::opLDTASK,
	/* 0x02 */ &v60_device::opSTPR,
	/* 0x03 */ &v60_device::opUNHANDLED,
	/* 0x04 */ &v60_device::opUNHANDLED,
	/* 0x05 */ &v60_device::opUNHANDLED,
	/* 0x06 */ &v60_device::opUNHANDLED,
	/* 0x07 */ &v60_device::opUNHANDLED,
	/* 0x08 */ &v60_device::opRVBIT,
	/* 0x09 */ &v60_device::opMOVB,
	/* 0x0a */ &v60_device::opMOVSBH,
	/* 0x0b */ &v60_device::opMOVZBH,
	/* 0x0c */ &v60_device::opMOVSBW,
	/* 0x0d */ &v60_device::opMOVZBW,
	/* 0x0e */ &v60_device::opUNHANDLED,
	/* 0x0f */ &v60_device::opUNHANDLED,
	/* 0x10 */ &v60_device::opCLRTLBA,
	/* 0x11 */ &v60_device::opUNHANDLED,
	/* 0x12 */ &v60_device::opLDPR,
	/* 0x13 */ &v60_device::opUPDPSWW,
	/* 0x14 */ &v60_device::opUNHANDLED,
	/* 0x15 */ &v60_device::opUNHANDLED,
	/* 0x16 */ &v60_device::opUNHANDLED,
	/* 0x17 */ &v60_device::opUNHANDLED,
	/* 0x18 */ &v60_device::opUNHANDLED,
	/* 0x19 */ &v60_device::opMOVTHB,
	/* 0x1a */ &v60_device::opUNHANDLED,
	/* 0x1b */ &v60_device::opMOVH,
	/* 0x1c */ &v60_device::opMOVSHW,
	/* 0x1d */ &v60_device::opMOVZHW,
	/* 0x1e */ &v60_device::opUNHANDLED,
	/* 0x1f */ &v60_device::opUNHANDLED,
	/* 0x20 */ &v60_device::opINB,
	/* 0x21 */ &v60_device::opOUTB,
	/* 0x22 */ &v60_device::opINH,
	/* 0x23 */ &v60_device::opOUTH,
	/* 0x24 */ &v60_device::opINW,
	/* 0x25 */ &v60_device::opOUTW,
	/* 0x26 */ &v60_device::opUNHANDLED,
	/* 0x27 */ &v60_device::opUNHANDLED,
	/* 0x28 */ &v60_device::opUNHANDLED,
	/* 0x29 */ &v60_device::opMOVTWB,
	/* 0x2a */ &v60_device::opUNHANDLED,
	/* 0x2b */ &v60_device::opMOVTWH,
	/* 0x2c */ &v60_device::opRVBYT,
	/* 0x2d */ &v60_device::opMOVW,
	/* 0x2e */ &v60_device::opUNHANDLED,
	/* 0x2f */ &v60_device::opUNHANDLED,
	/* 0x30 */ &v60_device::opUNHANDLED,
	/* 0x31 */ &v60_device::opUNHANDLED,
	/* 0x32 */ &v60_device::opUNHANDLED,
	/* 0x33 */ &v60_device::opUNHANDLED,
	/* 0x34 */ &v60_device::opUNHANDLED,
	/* 0x35 */ &v60_device::opUNHANDLED,
	/* 0x36 */ &v60_device::opUNHANDLED,
	/* 0x37 */ &v60_device::opUNHANDLED,
	/* 0x38 */ &v60_device::opNOTB,
	/* 0x39 */ &v60_device::opNEGB,
	/* 0x3a */ &v60_device::opNOTH,
	/* 0x3b */ &v60_device::opNEGH,
	/* 0x3c */ &v60_device::opNOTW,
	/* 0x3d */ &v60_device::opNEGW,
	/* 0x3e */ &v60_device::opUNHANDLED,
	/* 0x3f */ &v60_device::opMOVD,
	/* 0x40 */ &v60_device::opMOVEAB,
	/* 0x41 */ &v60_device::opXCHB,
	/* 0x42 */ &v60_device::opMOVEAH,
	/* 0x43 */ &v60_device::opXCHH,
	/* 0x44 */ &v60_device::opMOVEAW,
	/* 0x45 */ &v60_device::opXCHW,
	/* 0x46 */ &v60_device::opUNHANDLED,
	/* 0x47 */ &v60_device::opSETF,
	/* 0x48 */ &v60_device::opBSR,
	/* 0x49 */ &v60_device::opCALL,
	/* 0x4a */ &v60_device::opUPDPSWH,
	/* 0x4b */ &v60_device::opCHLVL,
	/* 0x4c */ &v60_device::opUNHANDLED,
	/* 0x4d */ &v60_device::opCHKAR,
	/* 0x4e */ &v60_device::opCHKAW,
	/* 0x4f */ &v60_device::opCHKAE,
	/* 0x50 */ &v60_device::opREMB,
	/* 0x51 */ &v60_device::opREMUB,
	/* 0x52 */ &v60_device::opREMH,
	/* 0x53 */ &v60_device::opREMUH,
	/* 0x54 */ &v60_device::opREMW,
	/* 0x55 */ &v60_device::opREMUW,
	/* 0x56 */ &v60_device::opUNHANDLED,
	/* 0x57 */ &v60_device::opUNHANDLED,
	/* 0x58 */ &v60_device::op58,
	/* 0x59 */ &v60_device::op59,
	/* 0x5a */ &v60_device::op5A,
	/* 0x5b */ &v60_device::op5B,
	/* 0x5c */ &v60_device::op5C,
	/* 0x5d */ &v60_device::op5D,
	/* 0x5e */ &v60_device::opUNHANDLED,
	/* 0x5f */ &v60_device::op5F,
	/* 0x60 */ &v60_device::opBV8,
	/* 0x61 */ &v60_device::opBNV8,
	/* 0x62 */ &v60_device::opBL8,
	/* 0x63 */ &v60_device::opBNL8,
	/* 0x64 */ &v60_device::opBE8,
	/* 0x65 */ &v60_device::opBNE8,
	/* 0x66 */ &v60_device::opBNH8,
	/* 0x67 */ &v60_device::opBH8,
	/* 0x68 */ &v60_device::opBN8,
	/* 0x69 */ &v60_device::opBP8,
	/* 0x6a */ &v60_device::opBR8,
	/* 0x6b */ &v60_device::opUNHANDLED,
	/* 0x6C */ &v60_device::opBLT8,
	/* 0x6c */ &v60_device::opBGE8,
	/* 0x6e */ &v60_device::opBLE8,
	/* 0x6f */ &v60_device::opBGT8,
	/* 0x70 */ &v60_device::opBV16,
	/* 0x71 */ &v60_device::opBNV16,
	/* 0x72 */ &v60_device::opBL16,
	/* 0x73 */ &v60_device::opBNL16,
	/* 0x74 */ &v60_device::opBE16,
	/* 0x75 */ &v60_device::opBNE16,
	/* 0x76 */ &v60_device::opBNH16,
	/* 0x77 */ &v60_device::opBH16,
	/* 0x78 */ &v60_device::opBN16,
	/* 0x79 */ &v60_device::opBP16,
	/* 0x7a */ &v60_device::opBR16,
	/* 0x7b */ &v60_device::opUNHANDLED,
	/* 0x7c */ &v60_device::opBLT16,
	/* 0x7d */ &v60_device::opBGE16,
	/* 0x7e */ &v60_device::opBLE16,
	/* 0x7f */ &v60_device::opBGT16,
	/* 0x80 */ &v60_device::opADDB,
	/* 0x81 */ &v60_device::opMULB,
	/* 0x82 */ &v60_device::opADDH,
	/* 0x83 */ &v60_device::opMULH,
	/* 0x84 */ &v60_device::opADDW,
	/* 0x85 */ &v60_device::opMULW,
	/* 0x86 */ &v60_device::opMULX,
	/* 0x87 */ &v60_device::opTEST1,
	/* 0x88 */ &v60_device::opORB,
	/* 0x89 */ &v60_device::opROTB,
	/* 0x8a */ &v60_device::opORH,
	/* 0x8b */ &v60_device::opROTH,
	/* 0x8c */ &v60_device::opORW,
	/* 0x8d */ &v60_device::opROTW,
	/* 0x8e */ &v60_device::opUNHANDLED,
	/* 0x8f */ &v60_device::opUNHANDLED,
	/* 0x90 */ &v60_device::opADDCB,
	/* 0x91 */ &v60_device::opMULUB,
	/* 0x92 */ &v60_device::opADDCH,
	/* 0x93 */ &v60_device::opMULUH,
	/* 0x94 */ &v60_device::opADDCW,
	/* 0x95 */ &v60_device::opMULUW,
	/* 0x96 */ &v60_device::opMULUX,
	/* 0x97 */ &v60_device::opSET1,
	/* 0x98 */ &v60_device::opSUBCB,
	/* 0x99 */ &v60_device::opROTCB,
	/* 0x9a */ &v60_device::opSUBCH,
	/* 0x9b */ &v60_device::opROTCH,
	/* 0x9c */ &v60_device::opSUBCW,
	/* 0x9d */ &v60_device::opROTCW,
	/* 0x9e */ &v60_device::opUNHANDLED,
	/* 0x9f */ &v60_device::opUNHANDLED,
	/* 0xa0 */ &v60_device::opANDB,
	/* 0xa1 */ &v60_device::opDIVB,
	/* 0xa2 */ &v60_device::opANDH,
	/* 0xa3 */ &v60_device::opDIVH,
	/* 0xa4 */ &v60_device::opANDW,
	/* 0xa5 */ &v60_device::opDIVW,
	/* 0xa6 */ &v60_device::opDIVX,
	/* 0xa7 */ &v60_device::opCLR1,
	/* 0xa8 */ &v60_device::opSUBB,
	/* 0xa9 */ &v60_device::opSHLB,
	/* 0xaa */ &v60_device::opSUBH,
	/* 0xab */ &v60_device::opSHLH,
	/* 0xac */ &v60_device::opSUBW,
	/* 0xad */ &v60_device::opSHLW,
	/* 0xae */ &v60_device::opUNHANDLED,
	/* 0xaf */ &v60_device::opUNHANDLED,
	/* 0xb0 */ &v60_device::opXORB,
	/* 0xb1 */ &v60_device::opDIVUB,
	/* 0xb2 */ &v60_device::opXORH,
	/* 0xb3 */ &v60_device::opDIVUH,
	/* 0xb4 */ &v60_device::opXORW,
	/* 0xb5 */ &v60_device::opDIVUW,
	/* 0xb6 */ &v60_device::opDIVUX,
	/* 0xb7 */ &v60_device::opNOT1,
	/* 0xb8 */ &v60_device::opCMPB,
	/* 0xb9 */ &v60_device::opSHAB,
	/* 0xba */ &v60_device::opCMPH,
	/* 0xbb */ &v60_device::opSHAH,
	/* 0xbc */ &v60_device::opCMPW,
	/* 0xbd */ &v60_device::opSHAW,
	/* 0xbe */ &v60_device::opUNHANDLED,
	/* 0xbf */ &v60_device::opUNHANDLED,
	/* 0xc0 */ &v60_device::opUNHANDLED,
	/* 0xc1 */ &v60_device::opUNHANDLED,
	/* 0xc2 */ &v60_device::opUNHANDLED,
	/* 0xc3 */ &v60_device::opUNHANDLED,
	/* 0xc4 */ &v60_device::opUNHANDLED,
	/* 0xc5 */ &v60_device::opUNHANDLED,
	/* 0xc6 */ &v60_device::opC6,
	/* 0xc7 */ &v60_device::opC7,
	/* 0xc8 */ &v60_device::opBRK,
	/* 0xc9 */ &v60_device::opBRKV,
	/* 0xca */ &v60_device::opRSR,
	/* 0xcb */ &v60_device::opTRAPFL,
	/* 0xcc */ &v60_device::opDISPOSE,
	/* 0xcd */ &v60_device::opNOP,
	/* 0xce */ &v60_device::opUNHANDLED,
	/* 0xcf */ &v60_device::opUNHANDLED,
	/* 0xd0 */ &v60_device::opDECB_0,
	/* 0xd1 */ &v60_device::opDECB_1,
	/* 0xd2 */ &v60_device::opDECH_0,
	/* 0xd3 */ &v60_device::opDECH_1,
	/* 0xd4 */ &v60_device::opDECW_0,
	/* 0xd5 */ &v60_device::opDECW_1,
	/* 0xd6 */ &v60_device::opJMP_0,
	/* 0xd7 */ &v60_device::opJMP_1,
	/* 0xd8 */ &v60_device::opINCB_0,
	/* 0xd9 */ &v60_device::opINCB_1,
	/* 0xda */ &v60_device::opINCH_0,
	/* 0xdb */ &v60_device::opINCH_1,
	/* 0xdc */ &v60_device::opINCW_0,
	/* 0xdd */ &v60_device::opINCW_1,
	/* 0xde */ &v60_device::opPREPARE_0,
	/* 0xdf */ &v60_device::opPREPARE_1,
	/* 0xe0 */ &v60_device::opTASI_0,
	/* 0xe1 */ &v60_device::opTASI_1,
	/* 0xe2 */ &v60_device::opRET_0,
	/* 0xe3 */ &v60_device::opRET_1,
	/* 0xe4 */ &v60_device::opPOPM_0,
	/* 0xe5 */ &v60_device::opPOPM_1,
	/* 0xe6 */ &v60_device::opPOP_0,
	/* 0xe7 */ &v60_device::opPOP_1,
	/* 0xe8 */ &v60_device::opJSR_0,
	/* 0xe9 */ &v60_device::opJSR_1,
	/* 0xea */ &v60_device::opRETIU_0,
	/* 0xeb */ &v60_device::opRETIU_1,
	/* 0xec */ &v60_device::opPUSHM_0,
	/* 0xed */ &v60_device::opPUSHM_1,
	/* 0xee */ &v60_device::opPUSH_0,
	/* 0xef */ &v60_device::opPUSH_1,
	/* 0xf0 */ &v60_device::opTESTB_0,
	/* 0xf1 */ &v60_device::opTESTB_1,
	/* 0xf2 */ &v60_device::opTESTH_0,
	/* 0xf3 */ &v60_device::opTESTH_1,
	/* 0xf4 */ &v60_device::opTESTW_0,
	/* 0xf5 */ &v60_device::opTESTW_1,
	/* 0xf6 */ &v60_device::opGETPSW_0,
	/* 0xf7 */ &v60_device::opGETPSW_1,
	/* 0xf8 */ &v60_device::opTRAP_0,
	/* 0xf9 */ &v60_device::opTRAP_1,
	/* 0xfa */ &v60_device::opRETIS_0,
	/* 0xfb */ &v60_device::opRETIS_1,
	/* 0xfc */ &v60_device::opSTTASK_0,
	/* 0xfd */ &v60_device::opSTTASK_1,
	/* 0xfe */ &v60_device::opCLRTLB_0,
	/* 0xff */ &v60_device::opCLRTLB_1,
};
