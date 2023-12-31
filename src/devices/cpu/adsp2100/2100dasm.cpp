// license:BSD-3-Clause
// copyright-holders:Aaron Giles
#include "emu.h"
#include "2100dasm.h"

const char *const adsp21xx_disassembler::flag_change[] = { "", "TOGGLE %s ", "RESET %s ", "SET %s " };
const char *const adsp21xx_disassembler::mode_change[] = { "", "", "DIS %s ", "ENA %s " };

const char *const adsp21xx_disassembler::alu_xop[] = { "AX0", "AX1", "AR", "MR0", "MR1", "MR2", "SR0", "SR1" };
const char *const adsp21xx_disassembler::alu_yop[] = { "AY0", "AY1", "AF", "0" };
const char *const adsp21xx_disassembler::alu_dst[] = { "AR", "AF", "NONE" };

const char *const adsp21xx_disassembler::mac_xop[] = { "MX0", "MX1", "AR", "MR0", "MR1", "MR2", "SR0", "SR1" };
const char *const adsp21xx_disassembler::mac_yop[] = { "MY0", "MY1", "MF", "0" };
const char *const adsp21xx_disassembler::mac_dst[] = { "MR", "MF", "NONE" };

const char *const adsp21xx_disassembler::shift_xop[] = { "SI", "??", "AR", "MR0", "MR1", "MR2", "SR0", "SR1" };

const char *const adsp21xx_disassembler::reg_grp[][16] =
{
	{ "AX0", "AX1", "MX0", "MX1", "AY0", "AY1", "MY0", "MY1", "SI", "SE", "AR", "MR0", "MR1", "MR2", "SR0", "SR1" },
	{ "I0", "I1", "I2", "I3", "M0", "M1", "M2", "M3", "L0", "L1", "L2", "L3", "??", "??", "PMOVLAY", "DMOVLAY" },
	{ "I4", "I5", "I6", "I7", "M4", "M5", "M6", "M7", "L4", "L5", "L6", "L7", "??", "??", "??", "??" },
	{ "ASTAT", "MSTAT", "SSTAT", "IMASK", "ICNTL", "CNTR", "SB", "PX", "RX0", "TX0", "RX1", "TX1", "IFC", "OWRCNTR", "??", "??" }
};
const char *const adsp21xx_disassembler::dual_xreg[] = { "AX0", "AX1", "MX0", "MX1" };
const char *const adsp21xx_disassembler::dual_yreg[] = { "AY0", "AY1", "MY0", "MY1" };

const char *const adsp21xx_disassembler::condition[] =
{
	"IF EQ ",
	"IF NE ",
	"IF GT ",
	"IF LE ",
	"IF LT ",
	"IF GE ",
	"IF AV ",
	"IF NOT AV ",
	"IF AC ",
	"IF NOT AC ",
	"IF NEG ",
	"IF POS ",
	"IF MV ",
	"IF NOT MV ",
	"IF NOT CE ",
	""
};

const char *const adsp21xx_disassembler::do_condition[] =
{
	"NE",
	"EQ",
	"LE",
	"GT",
	"GE",
	"LT",
	"NOT AV",
	"AV",
	"NOT AC",
	"AC",
	"POS",
	"NEG",
	"NOT MV",
	"MV",
	"CE",
	"FOREVER"
};

const char *const adsp21xx_disassembler::alumac_op[][2] =
{
	{ "",                            "" },
	{ "%s = %s * %s (RND)",          "%s = %s * %s (RND)" },
	{ "%s = MR + %s * %s (RND)",     "%s = MR + %s * %s (RND)" },
	{ "%s = MR - %s * %s (RND)",     "%s = MR - %s * %s (RND)" },
	{ "%s = %s * %s (SS)",           "%s = 0" },
	{ "%s = %s * %s (SU)",           "%s = %s * %s (SU)" },
	{ "%s = %s * %s (US)",           "%s = %s * %s (US)" },
	{ "%s = %s * %s (UU)",           "%s = %s * %s (UU)" },
	{ "%s = MR + %s * %s (SS)",      "%s = MR + %s * %s (SS)" },
	{ "%s = MR + %s * %s (SU)",      "%s = MR + %s * %s (SU)" },
	{ "%s = MR + %s * %s (US)",      "%s = MR + %s * %s (US)" },
	{ "%s = MR + %s * %s (UU)",      "%s = MR + %s * %s (UU)" },
	{ "%s = MR - %s * %s (SS)",      "%s = MR - %s * %s (SS)" },
	{ "%s = MR - %s * %s (SS)",      "%s = MR - %s * %s (SS)" },
	{ "%s = MR - %s * %s (US)",      "%s = MR - %s * %s (US)" },
	{ "%s = MR - %s * %s (UU)",      "%s = MR - %s * %s (UU)" },

	{ "!%s = %s",                    "%s = 0" },
	{ "!%s = %s + 1",                "%s = 1" },
	{ "%s = %s + %s + C",            "%s = %s + %s + C" },
	{ "%s = %s + %s",                "%s = %s" },
	{ "!%s = NOT %s",                "!%s = NOT %s" },
	{ "!%s = -%s",                   "!%s = -%s" },
	{ "%s = %s - %s + C - 1",        "%s = %s + C - 1" },
	{ "%s = %s - %s",                "%s = %s - %s" },
	{ "!%s = %s - 1",                "%s = -1" },
	{ "!%s = %s - %s",               "%s = -%s" },
	{ "!%s = %s - %s + C - 1",       "%s = -%s + C - 1" },
	{ "%s = NOT %s",                 "%s = NOT %s" },
	{ "%s = %s AND %s",              "%s = %s AND %s" },
	{ "%s = %s OR %s",               "%s = %s OR %s" },
	{ "%s = %s XOR %s",              "%s = %s XOR %s" },
	{ "%s = ABS %s",                 "%s = ABS %s" }
};

const char *const adsp21xx_disassembler::shift_op[] =
{
	"SR = LSHIFT %s (HI)",
	"SR = SR OR LSHIFT %s (HI)",
	"SR = LSHIFT %s (LO)",
	"SR = SR OR LSHIFT %s (LO)",
	"SR = ASHIFT %s (HI)",
	"SR = SR OR ASHIFT %s (HI)",
	"SR = ASHIFT %s (LO)",
	"SR = SR OR ASHIFT %s (LO)",
	"SR = NORM %s (HI)",
	"SR = SR OR NORM %s (HI)",
	"SR = NORM %s (LO)",
	"SR = SR OR NORM %s (LO)",
	"SE = EXP %s (HI)",
	"SE = EXP %s (HIX)",
	"SE = EXP %s (LO)",
	"SB = EXPADJ %s",
};

const char *const adsp21xx_disassembler::shift_by_op[] =
{
	"SR = LSHIFT %s BY %d (HI)",
	"SR = SR OR LSHIFT %s BY %d (HI)",
	"SR = LSHIFT %s BY %d (LO)",
	"SR = SR OR LSHIFT %s BY %d (LO)",
	"SR = ASHIFT %s BY %d (HI)",
	"SR = SR OR ASHIFT %s BY %d (HI)",
	"SR = ASHIFT %s BY %d (LO)",
	"SR = SR OR ASHIFT %s BY %d (LO)",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???"
};

const char *const adsp21xx_disassembler::constants[] =
{
	"$0001",
	"$FFFE",
	"$0002",
	"$FFFD",
	"$0004",
	"$FFFB",
	"$0008",
	"$FFF7",
	"$0010",
	"$FFEF",
	"$0020",
	"$FFDF",
	"$0040",
	"$FFBF",
	"$0080",
	"$FF7F",
	"$0100",
	"$FEFF",
	"$0200",
	"$FDFF",
	"$0400",
	"$FBFF",
	"$0800",
	"$F7FF",
	"$1000",
	"$EFFF",
	"$2000",
	"$DFFF",
	"$4000",
	"$BFFF",
	"$8000",
	"$7FFF"
};


void adsp21xx_disassembler::alumac(std::ostream &stream, int dest, uint32_t op)
{
	int opindex = BIT(op, 13, 5);
	const char *xop, *yop, *dst, *opstring;

	if (BIT(opindex, 4))
	{
		xop = alu_xop[BIT(op, 8, 3)];
		yop = alu_yop[BIT(op, 11, 2)];
		dst = alu_dst[dest];
	}
	else
	{
		xop = mac_xop[BIT(op, 8, 3)];
		yop = mac_yop[BIT(op, 11, 2)];
		dst = mac_dst[dest];
	}
	opstring = alumac_op[opindex][BIT(op, 11, 2) == 3];
	if (opstring[0] == '!')
		util::stream_format(stream, opstring + 1, dst, yop, xop);
	else
		util::stream_format(stream, opstring, dst, xop, yop);
}


void adsp21xx_disassembler::aluconst(std::ostream &stream, int dest, uint32_t op)
{
	int opindex = BIT(op, 13, 5);
	const char *xop, *dst, *cval, *opstring;

	if (BIT(opindex, 4))
	{
		xop = alu_xop[BIT(op, 8, 3)];
		cval = constants[BIT(op, 5, 3) | BIT(op, 11, 2) << 3];
		dst = alu_dst[dest];
	}
	else
	{
		xop = mac_xop[BIT(op, 8, 3)];
		cval = xop;
		dst = mac_dst[dest];
	}
	opstring = alumac_op[opindex][BIT(op, 11, 2) == 3];
	if (opstring[0] == '!')
		util::stream_format(stream, opstring + 1, dst, cval, xop);
	else
		util::stream_format(stream, opstring, dst, xop, cval);
}


offs_t adsp21xx_disassembler::disassemble(std::ostream &stream, offs_t pc, const data_buffer &opcodes, const data_buffer &params)
{
	uint32_t op = opcodes.r32(pc);
	unsigned dasmflags = 0;
	int temp;

	switch (BIT(op, 16, 8))
	{
		case 0x00:
			// 00000000 00000000 00000000  NOP
			stream << "NOP";
			break;
		case 0x01:
			// 00000001 0xxxxxxx xxxxxxxx  dst = IO(x)
			// 00000001 1xxxxxxx xxxxxxxx  IO(x) = dst
			// ADSP-218x only
			if (!BIT(op, 15))
				util::stream_format(stream, "%s = IO($%X)", reg_grp[0][BIT(op, 0, 4)], BIT(op, 4, 11));
			else
				util::stream_format(stream, "IO($%X) = %s", BIT(op, 4, 11), reg_grp[0][BIT(op, 0, 4)]);
			break;
		case 0x02:
			// 00000010 0000xxxx xxxxxxxx  modify flag out
			if (BIT(op, 12, 4) == 0)
			{
				util::stream_format(stream, "%s", condition[BIT(op, 0, 4)]);
				util::stream_format(stream, flag_change[BIT(op, 4, 2)], "FLAG_OUT");
				util::stream_format(stream, flag_change[BIT(op, 6, 2)], "FL0");
				util::stream_format(stream, flag_change[BIT(op, 8, 2)], "FL1");
				util::stream_format(stream, flag_change[BIT(op, 10, 2)], "FL2");
			}
			// 00000010 10000000 00000000  idle
			// 00000010 10000000 0000xxxx  idle (n)
			else if (BIT(op, 4, 12) == 0x800)
			{
			}
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x03:
			// 00000011 xxxxxxxx xxxxxxxx  call or jump on flag in
			if (BIT(op, 1))
				util::stream_format(stream, "%s", "IF FLAG_IN ");
			else
				util::stream_format(stream, "%s", "IF NOT FLAG_IN ");
			if (BIT(op, 0))
			{
				util::stream_format(stream, "%s", "CALL ");
				dasmflags = STEP_OVER | STEP_COND;
			}
			else
			{
				util::stream_format(stream, "%s", "JUMP ");
				dasmflags = STEP_COND;
			}
			temp = BIT(op, 4, 12) | BIT(op, 2, 2) << 12;
			util::stream_format(stream, "$%04X", temp);
			break;
		case 0x04:
			// 00000100 00000000 000xxxxx  stack control
			if (BIT(op, 5, 11) == 0)
			{
				if (BIT(op, 4))
				{
					util::stream_format(stream, "%s", "POP PC ");
					dasmflags = STEP_OUT;
				}
				if (BIT(op, 3)) util::stream_format(stream, "%s", "POP LOOP ");
				if (BIT(op, 2)) util::stream_format(stream, "%s", "POP CNTR ");
				if (BIT(op, 0, 2) == 2) util::stream_format(stream, "%s", "PUSH STAT ");
				else if (BIT(op, 0, 2) == 3) util::stream_format(stream, "%s", "POP STAT ");
			}
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x05:
			// 00000101 00000000 00000000  saturate MR
			if (BIT(op, 0, 16) == 0)
				util::stream_format(stream, "%s", "IF MV SAT MR");
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x06:
			// 00000110 000xxxxx 00000000  DIVS
			if ((op & 0x00e0ff) == 0x000000)
				util::stream_format(stream, "DIVS %s,%s", alu_yop[BIT(op, 11, 2)], alu_xop[BIT(op, 8, 3)]);
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x07:
			// 00000111 00010xxx 00000000  DIVQ
			if ((op & 0x00f8ff) == 0x001000)
				util::stream_format(stream, "DIVQ %s", alu_xop[BIT(op, 8, 3)]);
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x08:
			// 00001000 00000000 0000xxxx  reserved
			util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x09:
			// 00001001 00000000 000xxxxx  modify address register
			if (BIT(op, 5, 11) == 0)
			{
				temp = BIT(op, 2, 3);
				util::stream_format(stream, "MODIFY (I%d,M%d)", temp, (temp & 4) + BIT(op, 0, 2));
			}
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x0a:
			// 00001010 00000000 000xxxxx  conditional return
			if (BIT(op, 5, 11) == 0)
			{
				util::stream_format(stream, "%s", condition[BIT(op, 0, 4)]);
				if (BIT(op, 4))
					util::stream_format(stream, "%s", "RTI");
				else
					util::stream_format(stream, "%s", "RTS");
				dasmflags = STEP_OUT;
				if (BIT(op, 0, 4) != 15)
					dasmflags |= STEP_COND;
			}
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x0b:
			// 00001011 00000000 xx00xxxx  conditional jump (indirect address)
			if (BIT(op, 8, 8) == 0)
			{
				util::stream_format(stream, "%s", condition[BIT(op, 0, 4)]);
				if (BIT(op, 4))
				{
					util::stream_format(stream, "CALL (I%d)", 4 + BIT(op, 6, 2));
					dasmflags = STEP_OVER;
				}
				else
					util::stream_format(stream, "JUMP (I%d)", 4 + BIT(op, 6, 2));
				if (BIT(op, 0, 4) != 15)
					dasmflags |= STEP_COND;
			}
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x0c:
			// 00001100 xxxxxxxx xxxxxxxx  mode control
			util::stream_format(stream, mode_change[BIT(op, 4, 2)], "SEC_REG");
			util::stream_format(stream, mode_change[BIT(op, 6, 2)], "BIT_REV");
			util::stream_format(stream, mode_change[BIT(op, 8, 2)], "AV_LATCH");
			util::stream_format(stream, mode_change[BIT(op, 10, 2)], "AR_SAT");
			util::stream_format(stream, mode_change[BIT(op, 12, 2)], "M_MODE");
			util::stream_format(stream, mode_change[BIT(op, 14, 2)], "TIMER");
			util::stream_format(stream, mode_change[BIT(op, 2, 2)], "G_MODE");
			break;
		case 0x0d:
			// 00001101 0000xxxx xxxxxxxx  internal data move
			if (BIT(op, 12, 4) == 0)
				util::stream_format(stream, "%s = %s", reg_grp[BIT(op, 10, 2)][BIT(op, 4, 4)], reg_grp[BIT(op, 8, 3)][BIT(op, 0, 4)]);
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x0e:
			// 00001110 0xxxxxxx xxxxxxxx  conditional shift
			if ((op & 0x0080f0) == 0x000000)
			{
				util::stream_format(stream, "%s", condition[BIT(op, 0, 4)]);
				util::stream_format(stream, shift_op[BIT(op, 11, 4)], shift_xop[BIT(op, 8, 3)]);
			}
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x0f:
			// 00001111 0xxxxxxx xxxxxxxx  shift immediate
			if (!BIT(op, 15))
				util::stream_format(stream, shift_by_op[BIT(op, 11, 4)], shift_xop[BIT(op, 8, 3)], (signed char)op);
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x10:
			// 00010000 0xxxxxxx xxxxxxxx  shift with internal data register move
			if (!BIT(op, 15))
			{
				util::stream_format(stream, shift_op[BIT(op, 11, 4)], shift_xop[BIT(op, 8, 3)]);
				util::stream_format(stream, ", %s = %s", reg_grp[0][BIT(op, 4, 4)], reg_grp[0][BIT(op, 0, 4)]);
			}
			else
				util::stream_format(stream, "??? (%06X)", op);
			break;
		case 0x11:
			// 00010001 0xxxxxxx xxxxxxxx  shift with pgm memory read/write
			util::stream_format(stream, shift_op[BIT(op, 11, 4)], shift_xop[BIT(op, 8, 3)]);
			if (BIT(op, 15))
				util::stream_format(stream, ", PM(I%d,M%d) = %s", 4 + BIT(op, 2, 2), 4 + BIT(op, 0, 2), reg_grp[0][BIT(op, 4, 4)]);
			else
				util::stream_format(stream, ", %s = PM(I%d,M%d)", reg_grp[0][BIT(op, 4, 4)], 4 + BIT(op, 2, 2), 4 + BIT(op, 0, 2));
			break;
		case 0x12: case 0x13:
			// 0001001x 0xxxxxxx xxxxxxxx  shift with data memory read/write
			util::stream_format(stream, shift_op[BIT(op, 11, 4)], shift_xop[BIT(op, 8, 3)]);
			temp = BIT(op, 16) ? 4 : 0;
			if (BIT(op, 15))
				util::stream_format(stream, ", DM(I%d,M%d) = %s", temp + BIT(op, 2, 2), temp + BIT(op, 0, 2), reg_grp[0][BIT(op, 4, 4)]);
			else
				util::stream_format(stream, ", %s = DM(I%d,M%d)", reg_grp[0][BIT(op, 4, 4)], temp + BIT(op, 2, 2), temp + BIT(op, 0, 2));
			break;
		case 0x14: case 0x15: case 0x16: case 0x17:
			// 000101xx xxxxxxxx xxxxxxxx  do until
			util::stream_format(stream, "DO $%04X UNTIL %s", BIT(op, 4, 14), do_condition[BIT(op, 0, 4)]);
			break;
		case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f:
			// 00011xxx xxxxxxxx xxxxxxxx  conditional jump (immediate addr)
			if (BIT(op, 18))
			{
				util::stream_format(stream, "%sCALL $%04X", condition[BIT(op, 0, 4)], BIT(op, 4, 14));
				dasmflags = STEP_OVER;
			}
			else
				util::stream_format(stream, "%sJUMP $%04X", condition[BIT(op, 0, 4)], BIT(op, 4, 14));
			if (BIT(op, 0, 4) != 15)
				dasmflags |= STEP_COND;
			break;
		case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x26: case 0x27:
			// 00100xxx xxxxxxxx xxxxxxxx  conditional ALU/MAC
			util::stream_format(stream, "%s", condition[BIT(op, 0, 4)]);
			if (!BIT(op, 4))
				alumac(stream, BIT(op, 18), op);
			else
			{
				// ADSP-218x only
				aluconst(stream, BIT(op, 18), op);
			}
			break;
		case 0x28: case 0x29: case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f:
			// 00101xxx xxxxxxxx xxxxxxxx  ALU/MAC with internal data register move
			if ((op & 0x0600ff) == 0x0200aa)
			{
				// ADSP-218x only
				alumac(stream, 2, op);
			}
			else
			{
				if (BIT(op, 13, 5) != 0)
				{
					alumac(stream, BIT(op, 18), op);
					util::stream_format(stream, ", ");
				}
				util::stream_format(stream, "%s = %s", reg_grp[0][BIT(op, 4, 4)], reg_grp[0][BIT(op, 0, 4)]);
			}
			break;
		case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
		case 0x38: case 0x39: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f:
			// 0011xxxx xxxxxxxx xxxxxxxx  load non-data register immediate
			util::stream_format(stream, "%s = $%04X", reg_grp[BIT(op, 18, 2)][BIT(op, 0, 4)], BIT(op, 4, 14));
			break;
		case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47:
		case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
			// 0100xxxx xxxxxxxx xxxxxxxx  load data register immediate
			util::stream_format(stream, "%s = $%04X", reg_grp[0][BIT(op, 0, 4)], BIT(op, 4, 14));
			break;
		case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x56: case 0x57:
		case 0x58: case 0x59: case 0x5a: case 0x5b: case 0x5c: case 0x5d: case 0x5e: case 0x5f:
			// 0101xxxx xxxxxxxx xxxxxxxx  ALU/MAC with pgm memory read/write
			if (BIT(op, 13, 5) != 0)
			{
				alumac(stream, BIT(op, 18), op);
				util::stream_format(stream, ", ");
			}
			if (BIT(op, 19))
				util::stream_format(stream, "PM(I%d,M%d) = %s", 4 + BIT(op, 2, 2), 4 + BIT(op, 0, 2), reg_grp[0][BIT(op, 4, 4)]);
			else
				util::stream_format(stream, "%s = PM(I%d,M%d)", reg_grp[0][BIT(op, 4, 4)], 4 + BIT(op, 2, 2), 4 + BIT(op, 0, 2));
			break;
		case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x66: case 0x67:
		case 0x68: case 0x69: case 0x6a: case 0x6b: case 0x6c: case 0x6d: case 0x6e: case 0x6f:
		case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77:
		case 0x78: case 0x79: case 0x7a: case 0x7b: case 0x7c: case 0x7d: case 0x7e: case 0x7f:
			// 011xxxxx xxxxxxxx xxxxxxxx  ALU/MAC with data memory read/write
			if (BIT(op, 13, 5) != 0)
			{
				alumac(stream, BIT(op, 18), op);
				util::stream_format(stream, ", ");
			}
			temp = BIT(op, 20) ? 4 : 0;
			if (BIT(op, 19))
				util::stream_format(stream, "DM(I%d,M%d) = %s", temp + BIT(op, 2, 2), temp + BIT(op, 0, 2), reg_grp[0][BIT(op, 4, 4)]);
			else
				util::stream_format(stream, "%s = DM(I%d,M%d)", reg_grp[0][BIT(op, 4, 4)], temp + BIT(op, 2, 2), temp + BIT(op, 0, 2));
			break;
		case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87:
		case 0x88: case 0x89: case 0x8a: case 0x8b: case 0x8c: case 0x8d: case 0x8e: case 0x8f:
		case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95: case 0x96: case 0x97:
		case 0x98: case 0x99: case 0x9a: case 0x9b: case 0x9c: case 0x9d: case 0x9e: case 0x9f:
			// 100xxxxx xxxxxxxx xxxxxxxx  read/write data memory (immediate addr)
			if (BIT(op, 20))
				util::stream_format(stream, "DM($%04X) = %s", BIT(op, 4, 14), reg_grp[BIT(op, 18, 2)][BIT(op, 0, 4)]);
			else
				util::stream_format(stream, "%s = DM($%04X)", reg_grp[BIT(op, 18, 2)][BIT(op, 0, 4)], BIT(op, 4, 14));
			break;
		case 0xa0: case 0xa1: case 0xa2: case 0xa3: case 0xa4: case 0xa5: case 0xa6: case 0xa7:
		case 0xa8: case 0xa9: case 0xaa: case 0xab: case 0xac: case 0xad: case 0xae: case 0xaf:
		case 0xb0: case 0xb1: case 0xb2: case 0xb3: case 0xb4: case 0xb5: case 0xb6: case 0xb7:
		case 0xb8: case 0xb9: case 0xba: case 0xbb: case 0xbc: case 0xbd: case 0xbe: case 0xbf:
			// 101xxxxx xxxxxxxx xxxxxxxx  data memory write (immediate)
			temp = BIT(op, 20) ? 4 : 0;
			util::stream_format(stream, "DM(I%d,M%d) = $%04X", temp + BIT(op, 2, 2), temp + BIT(op, 0, 2), BIT(op, 4, 16));
			break;
		case 0xc0: case 0xc1: case 0xc2: case 0xc3: case 0xc4: case 0xc5: case 0xc6: case 0xc7:
		case 0xc8: case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf:
		case 0xd0: case 0xd1: case 0xd2: case 0xd3: case 0xd4: case 0xd5: case 0xd6: case 0xd7:
		case 0xd8: case 0xd9: case 0xda: case 0xdb: case 0xdc: case 0xdd: case 0xde: case 0xdf:
		case 0xe0: case 0xe1: case 0xe2: case 0xe3: case 0xe4: case 0xe5: case 0xe6: case 0xe7:
		case 0xe8: case 0xe9: case 0xea: case 0xeb: case 0xec: case 0xed: case 0xee: case 0xef:
		case 0xf0: case 0xf1: case 0xf2: case 0xf3: case 0xf4: case 0xf5: case 0xf6: case 0xf7:
		case 0xf8: case 0xf9: case 0xfa: case 0xfb: case 0xfc: case 0xfd: case 0xfe: case 0xff:
			// 11xxxxxx xxxxxxxx xxxxxxxx  ALU/MAC with data & pgm memory read
			if (BIT(op, 13, 5) != 0)
			{
				alumac(stream, 0, op);
				util::stream_format(stream, ", ");
			}
			util::stream_format(stream, "%s = DM(I%d,M%d), %s = PM(I%d,M%d)", dual_xreg[BIT(op, 18, 2)], BIT(op, 2, 2), BIT(op, 0, 2),
						dual_yreg[BIT(op, 20, 2)], 4 + BIT(op, 6, 2), 4 + BIT(op, 4, 2));
			break;
	}

	return 1 | dasmflags | SUPPORTED;
}

uint32_t adsp21xx_disassembler::opcode_alignment() const
{
	return 1;
}
