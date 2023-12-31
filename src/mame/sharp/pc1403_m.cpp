// license:GPL-2.0+
// copyright-holders:Peter Trauner
#include "emu.h"
#include "cpu/sc61860/sc61860.h"

#include "pocketc.h"
#include "pc1403.h"
#include "machine/ram.h"

#define LOG_ASIC (1U << 1)

#define VERBSOE  (0)
#include "logmacro.h"

/* C-CE while reset, program will not be destroyed! */

/*
   port 2:
     bits 0,1: external rom a14,a15 lines
   port 3:
     bits 0..6 keyboard output select matrix line
*/

void pc1403_state::asic_write(offs_t offset, uint8_t data)
{
	m_asic[offset >> 9] = data;
	switch (offset >> 9)
	{
	case 0: // 0x3800
		// output
		LOGMASKED(LOG_ASIC, "asic write %.4x %.2x\n", offset, data);
		break;
	case 1: // 0x3a00
		LOGMASKED(LOG_ASIC, "asic write %.4x %.2x\n", offset, data);
		break;
	case 2: // 0x3c00
		membank("bank1")->set_base(memregion("user1")->base() + ((data & 7) << 14));
		LOGMASKED(LOG_ASIC, "asic write %.4x %.2x\n", offset, data);
		break;
	case 3: // 0x3e00
		break;
	}
}

uint8_t pc1403_state::asic_read(offs_t offset)
{
	uint8_t data = m_asic[offset >> 9];
	switch (offset >> 9)
	{
	case 0:
	case 1:
	case 2:
		LOGMASKED(LOG_ASIC, "asic read %.4x %.2x\n", offset, data);
		break;
	}
	return data;
}

uint8_t pc1403_state::in_a_r()
{
	uint8_t data = m_outa;

	for (int bit = 0; bit < 7; bit++)
		if (BIT(m_asic[3], bit))
			data |= m_keys[bit]->read();

	if (BIT(m_outa, 0))
	{
		data |= m_keys[7]->read();

		/* At Power Up we fake a 'C-CE' pressure */
		if (m_power)
			data |= 0x02;
	}

	for (int bit = 1, key = 8; bit < 7; bit++, key++)
		if (BIT(m_outa, bit))
			data |= m_keys[key]->read();

	return data;
}

void pc1403_state::out_c_w(uint8_t data)
{
	m_portc = data;
}

int pc1403_state::reset_r()
{
	return BIT(m_extra->read(), 1);
}

void pc1403_state::machine_start()
{
	pocketc_state::machine_start();

	membank("bank1")->set_base(memregion("user1")->base());

	m_ram_nvram->set_base(memregion("maincpu")->base() + 0x8000, 0x8000);

	uint8_t *gfx = memregion("gfx1")->base();
	for (int i = 0; i < 128; i++)
		gfx[i] = i;
}
