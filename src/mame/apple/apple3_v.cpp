// license:BSD-3-Clause
// copyright-holders:Nathan Woods,R. Belmont
/***************************************************************************

    video/apple3.c

    Apple ///

***************************************************************************/


#include "emu.h"
#include "apple3.h"
#include "machine/ram.h"

#define BLACK   0
#define DKRED   1
#define DKBLUE  2
#define PURPLE  3
#define DKGREEN 4
#define DKGRAY  5
#define BLUE    6
#define LTBLUE  7
#define BROWN   8
#define ORANGE  9
#define GRAY    10
#define PINK    11
#define GREEN   12
#define YELLOW  13
#define AQUA    14
#define WHITE   15

// derived from the IIgs palette then adjusted to match Sara
static const unsigned char apple3_palette[] =
{
	// text colors, which don't match the Apple II palette
	0x0, 0x0, 0x0,  /* Black         $0 */
	0x5, 0x0, 0x5,  /* Magenta       $1 */
	0x0, 0x0, 0x9,  /* Dark Blue     $2 */
	0xD, 0x2, 0xD,  /* Purple        $3 */
	0x0, 0x7, 0x2,  /* Dark Green    $4 */
	0xa, 0xa, 0xa,  /* Light Gray    $5 */
	0x2, 0x2, 0xF,  /* Medium Blue   $6 */
	0x6, 0xA, 0xF,  /* Light Blue    $7 */
	0x8, 0x5, 0x0,  /* Brown         $8 */
	0xF, 0x6, 0x0,  /* Orange        $9 */
	0x5, 0x5, 0x5,  /* Dark Gray     $A */
	0xF, 0x9, 0xF,  /* Pink          $B */
	0x1, 0xD, 0x0,  /* Light Green   $C */
	0xe, 0xe, 0x0,  /* Yellow        $D */
	0x4, 0xe, 0xd,  /* Cyan          $E */
	0xF, 0xF, 0xF,  /* White         $F */
	// graphics colors, which *are* Apple II order
	0x0, 0x0, 0x0,  /* Black         $0 */
	0xD, 0x0, 0x3,  /* Deep Red      $1 */
	0x0, 0x0, 0x9,  /* Dark Blue     $2 */
	0xD, 0x2, 0xD,  /* Purple        $3 */
	0x0, 0x7, 0x2,  /* Dark Green    $4 */
	0x5, 0x5, 0x5,  /* Dark Gray     $5 */
	0x2, 0x2, 0xF,  /* Medium Blue   $6 */
	0x6, 0xA, 0xF,  /* Light Blue    $7 */
	0x8, 0x5, 0x0,  /* Brown         $8 */
	0xF, 0x6, 0x0,  /* Orange        $9 */
	0xA, 0xA, 0xA,  /* Light Gray    $A */
	0xF, 0x9, 0x8,  /* Pink          $B */
	0x1, 0xD, 0x0,  /* Light Green   $C */
	0xF, 0xF, 0x0,  /* Yellow        $D */
	0x4, 0xF, 0x9,  /* Aquamarine    $E */
	0xF, 0xF, 0xF   /* White         $F */

};

static const uint32_t text_map[] =
{
	0x400, 0x480, 0x500, 0x580, 0x600, 0x680, 0x700, 0x780,
	0x428, 0x4a8, 0x528, 0x5a8, 0x628, 0x6a8, 0x728, 0x7a8,
	0x450, 0x4d0, 0x550, 0x5d0, 0x650, 0x6d0, 0x750, 0x7d0
};


void apple3_state::palette_init(palette_device &palette) const
{
	for (int i = 0; i < 32; i++)
	{
		palette.set_pen_color(i,
				apple3_palette[(3*i)]*17,
				apple3_palette[(3*i)+1]*17,
				apple3_palette[(3*i)+2]*17);
	}
}

void apple3_state::apple3_write_charmem()
{
	address_space& space = m_maincpu->space(AS_PROGRAM);
	static const uint32_t screen_hole_map[] =
	{
		0x478, 0x4f8, 0x578, 0x5f8, 0x678, 0x6f8, 0x778, 0x7f8
	};
	int i, j, addr;
	uint8_t val;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 4; j++)
		{
			addr = 0x7f & space.read_byte(screen_hole_map[i] + 0x400 + j + 0);
			val = space.read_byte(screen_hole_map[i] + j + 0);
			m_char_mem[((addr * 8) + ((i & 3) * 2) + 0) & 0x7ff] = val;

			addr = 0x7f & space.read_byte(screen_hole_map[i] + 0x400 + j + 4);
			val = space.read_byte(screen_hole_map[i] + j + 4);
			m_char_mem[((addr * 8) + ((i & 3) * 2) + 1) & 0x7ff] = val;
		}
	}
}



void apple3_state::video_start()
{
	int i, j;
	uint32_t v;

	memset(m_char_mem, 0, 0x800);

	m_hgr_map = std::make_unique<uint32_t[]>(192);
	for (i = 0; i < 24; i++)
	{
		v = text_map[i] - 0x0400;
		for (j = 0; j < 8; j++)
		{
			m_hgr_map[(i * 8) + j] = 0x2000 + v + (j * 0x400);
		}
	}
}



void apple3_state::text40(bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	uint8_t const *const ram = m_ram->pointer();
	uint32_t const ram_size = m_ram->size();
	int const beginrow = (cliprect.top() - (cliprect.top() % 8)) / 8;
	int const endrow = (cliprect.bottom() - (cliprect.bottom() % 8) + 7) / 8;

	for (int y = beginrow; y <= endrow; y++)
	{
		for (int x = 0; x < 40; x++)
		{
			offs_t offset = ram_size - 0x8000 + text_map[y] + x + (m_flags & VAR_VM2 ? 0x0400 : 0x0000);
			uint8_t const ch = ram[offset];

			// no color text in emulation mode
			pen_t fg, bg;
			if ((m_flags & VAR_VM0) && (m_via_1_a & 0x40))
			{
				/* color text */
				offset = ram_size - 0x8000 + text_map[y] + x + (m_flags & VAR_VM2 ? 0x0000 : 0x0400);
				bg = (ram[offset] >> 0) & 0x0F;
				fg = (ram[offset] >> 4) & 0x0F;
			}
			else
			{
				/* monochrome - on a real /// with an RGB monitor, text is white */
				bg = BLACK;
				fg = WHITE;
			}

			uint8_t const *const char_data = &m_char_mem[(ch & 0x7F) * 8];

			for (int row = 0; row < 8; row++)
			{
				for (int col = 0; col < 7; col++)
				{
					uint16_t *const dest = &bitmap.pix(y * 8 + row, x * 14 + col * 2);

					// Flash or Inverse
					if (!(ch & 0x80) && (!(char_data[row] & 0x80) || m_flash))
					{
						dest[0] = (char_data[row] & (1 << col)) ? bg : fg;
						dest[1] = (char_data[row] & (1 << col)) ? bg : fg;
					}
					else
					{
						dest[0] = (char_data[row] & (1 << col)) ? fg : bg;
						dest[1] = (char_data[row] & (1 << col)) ? fg : bg;
					}
				}
			}
		}
	}
}



void apple3_state::text80(bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	uint8_t const *const ram = m_ram->pointer();
	uint32_t const ram_size = m_ram->size();
	int const beginrow = (cliprect.top() - (cliprect.top() % 8)) / 8;
	int const endrow = (cliprect.bottom() - (cliprect.bottom() % 8) + 7) / 8;

	for (int y = beginrow; y <= endrow; y++)
	{
		for (int x = 0; x < 40; x++)
		{
			offs_t const offset = ram_size - 0x8000 + text_map[y] + x;
			uint8_t ch;
			uint8_t const *char_data;
			pen_t fg, bg;

			fg = GREEN;
			bg = BLACK;

			/* first character */
			ch = ram[offset + 0x0000];
			char_data = &m_char_mem[(ch & 0x7F) * 8];

			for (int row = 0; row < 8; row++)
			{
				for (int col = 0; col < 7; col++)
				{
					uint16_t *const dest = &bitmap.pix(y * 8 + row, x * 14 + col + 0);

					// Flash or Inverse
					if (!(ch & 0x80) && (!(char_data[row] & 0x80) || m_flash))
					{
						*dest = (char_data[row] & (1 << col)) ? bg : fg;
					}
					else
					{
						*dest = (char_data[row] & (1 << col)) ? fg : bg;
					}
				}
			}

			/* second character */
			ch = ram[offset + 0x0400];
			char_data = &m_char_mem[(ch & 0x7F) * 8];

			for (int row = 0; row < 8; row++)
			{
				for (int col = 0; col < 7; col++)
				{
					uint16_t *const dest = &bitmap.pix(y * 8 + row, x * 14 + col + 7);

					// Flash or Inverse
					if (!(ch & 0x80) && (!(char_data[row] & 0x80) || m_flash))
					{
						*dest = (char_data[row] & (1 << col)) ? bg : fg;
					}
					else
					{
						*dest = (char_data[row] & (1 << col)) ? fg : bg;
					}
				}
			}
		}
	}
}



void apple3_state::graphics_hgr(bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	/* hi-res mode: 280x192x2 */
	uint8_t const *const ram = m_ram->pointer();
	int const smooth = m_va | (m_vb << 1) | (m_vc << 2);

	for (int y = cliprect.top(); y <= cliprect.bottom(); y++)
	{
		int ly = y;
		if (m_smoothscr)
		{
			// get our base Y position
			ly = y & ~7;
			// get the offset into the group of 8 lines
			int const lyb = ((y % 8) + smooth) & 7;
			// add to the base
			ly += lyb;
		}

		uint8_t const *pix_info;
		if (m_flags & VAR_VM2)
			pix_info = &ram[m_hgr_map[ly]];
		else
			pix_info = &ram[m_hgr_map[ly] - 0x2000];
		uint16_t *ptr = &bitmap.pix(y);

		for (int i = 0; i < 40; i++)
		{
			uint8_t b = *(pix_info++);

			for (int x = 0; x < 7; x++)
			{
				ptr[0] = ptr[1] = (b & 0x01) ? WHITE : BLACK;
				ptr += 2;
				b >>= 1;
			}
		}
	}
}

void apple3_state::graphics_chgr(bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	/* color hi-res mode: 280x192x16 */
	uint8_t const *const ram = m_ram->pointer();
	int const smooth = m_va | (m_vb << 1) | (m_vc << 2);

	for (int y = cliprect.top(); y <= cliprect.bottom(); y++)
	{
		int ly = y;
		if (m_smoothscr)
		{
			// get our base Y position
			ly = y & ~7;
			// get the offset into the group of 8 lines
			int const lyb = ((y % 8) + smooth) & 7;
			// add to the base
			ly += lyb;
		}

		uint8_t const *pix_info;
		uint8_t const *col_info;
		if (m_flags & VAR_VM2)
		{
			pix_info = &ram[m_hgr_map[ly] + 0x2000];
			col_info = &ram[m_hgr_map[ly] + 0x4000];
		}
		else
		{
			pix_info = &ram[m_hgr_map[ly] - 0x2000];
			col_info = &ram[m_hgr_map[ly]];
		}
		uint16_t *ptr = &bitmap.pix(y);

		for (int i = 0; i < 40; i++)
		{
			uint16_t const bgcolor = ((*col_info >> 0) & 0x0F) + 16;
			uint16_t const fgcolor = ((*col_info >> 4) & 0x0F) + 16;

			uint8_t b = *pix_info;

			for (int x = 0; x < 7; x++)
			{
				ptr[0] = ptr[1] = (b & 1) ? fgcolor : bgcolor;
				ptr += 2;
				b >>= 1;
			}
			pix_info++;
			col_info++;
		}
	}
}



void apple3_state::graphics_shgr(bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	/* super hi-res mode: 560x192x2 */
	uint8_t const *const ram = m_ram->pointer();
	int const smooth = m_va | (m_vb << 1) | (m_vc << 2);

	for (int y = cliprect.top(); y <= cliprect.bottom(); y++)
	{
		int ly = y;
		if (m_smoothscr)
		{
			// get our base Y position
			ly = y & ~7;
			// get the offset into the group of 8 lines
			int const lyb = ((y % 8) + smooth) & 7;
			// add to the base
			ly += lyb;
		}

		uint8_t const *pix_info1;
		uint8_t const *pix_info2;
		if (m_flags & VAR_VM2)
		{
			pix_info1 = &ram[m_hgr_map[ly] + 0x2000];
			pix_info2 = &ram[m_hgr_map[ly] + 0x4000];
		}
		else
		{
			pix_info1 = &ram[m_hgr_map[ly] - 0x2000];
			pix_info2 = &ram[m_hgr_map[ly]];
		}
		uint16_t *ptr = &bitmap.pix(y);

		for (int i = 0; i < 40; i++)
		{
			uint8_t b1 = *(pix_info1++);
			uint8_t b2 = *(pix_info2++);

			for (int x = 0; x < 7; x++)
			{
				*(ptr++) = (b1 & 0x01) ? WHITE : BLACK;
				b1 >>= 1;
			}

			for (int x = 0; x < 7; x++)
			{
				*(ptr++) = (b2 & 0x01) ? WHITE : BLACK;
				b2 >>= 1;
			}
		}
	}
}



void apple3_state::graphics_chires(bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	uint8_t const *const ram = m_ram->pointer();
	int const smooth = m_va | (m_vb << 1) | (m_vc << 2);

	for (int y = cliprect.top(); y <= cliprect.bottom(); y++)
	{
		int ly = y;
		if (m_smoothscr)
		{
			// get our base Y position
			ly = y & ~7;
			// get the offset into the group of 8 lines
			int const lyb = ((y % 8) + smooth) & 7;
			// add to the base
			ly += lyb;
		}

		uint16_t *pen = &bitmap.pix(y);
		for (int i = 0; i < 20; i++)
		{
			uint8_t p1, p2, p3, p4;
			if (m_flags & VAR_VM2)
			{
				p1 = ram[m_hgr_map[ly] + 0x2000 + (i * 2) + 0];
				p2 = ram[m_hgr_map[ly] + 0x4000 + (i * 2) + 0];
				p3 = ram[m_hgr_map[ly] + 0x2000 + (i * 2) + 1];
				p4 = ram[m_hgr_map[ly] + 0x4000 + (i * 2) + 1];
			}
			else
			{
				p1 = ram[m_hgr_map[ly] - 0x2000 + (i * 2) + 0];
				p2 = ram[m_hgr_map[ly] - 0x0000 + (i * 2) + 0];
				p3 = ram[m_hgr_map[ly] - 0x2000 + (i * 2) + 1];
				p4 = ram[m_hgr_map[ly] - 0x0000 + (i * 2) + 1];
			}

			pen[ 0] = pen[ 1] = pen[ 2] = pen[ 3] = (p1 & 0x0f);
			pen[ 4] = pen[ 5] = pen[ 6] = pen[ 7] = ((p1 >>  4) & 0x07) | ((p2 & 1) << 3);
			pen[ 8] = pen[ 9] = pen[10] = pen[11] = ((p2 >> 1) & 0x0F);
			pen[12] = pen[13] = pen[14] = pen[15] = ((p2 >> 5) & 0x03) | ((p3 & 3) << 2);
			pen[16] = pen[17] = pen[18] = pen[19] = ((p3 >> 2) & 0x0F);
			pen[20] = pen[21] = pen[22] = pen[23] = ((p3 >> 6) & 0x01) | ((p4 << 1) & 0xe);
			pen[24] = pen[25] = pen[26] = pen[27] = ((p4 >> 3) & 0x0F);
			pen += 28;
		}
	}
}



uint32_t apple3_state::screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
//  printf("gfx mode %x\n", m_flags & (VAR_VM3|VAR_VM1|VAR_VM0));

	// always update the flash timer here so it's smooth regardless of mode switches
	m_flash = ((machine().time() * 4).seconds() & 1) ? true : false;

	switch(m_flags & (VAR_VM3|VAR_VM1|VAR_VM0))
	{
		case 0:
		case VAR_VM0:
			text40(bitmap, cliprect);           // 1
			break;

		case VAR_VM1:                           // 2
		case VAR_VM1|VAR_VM0:                   // 3
			text80(bitmap, cliprect);
			break;

		case VAR_VM3:                           // 8
			graphics_hgr(bitmap, cliprect);    /* hgr mode */
			break;

		case VAR_VM3|VAR_VM0:                   // 9
			graphics_chgr(bitmap, cliprect);
			break;

		case VAR_VM3|VAR_VM1:                   // a
			graphics_shgr(bitmap, cliprect);
			break;

		case VAR_VM3|VAR_VM1|VAR_VM0:           // b
			graphics_chires(bitmap, cliprect);
			break;
	}
	return 0;
}
