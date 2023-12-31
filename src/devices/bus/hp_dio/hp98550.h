// license:BSD-3-Clause
// copyright-holders:Sven Schnelle

#ifndef MAME_BUS_HPDIO_98550_H
#define MAME_BUS_HPDIO_98550_H

#pragma once

#include "hp_dio.h"
#include "video/catseye.h"
#include "video/nereid.h"
#include "machine/ram.h"

namespace bus::hp_dio {

class dio32_98550_device :
	public device_t,
	public device_dio16_card_interface,
	public device_memory_interface
{
public:
	dio32_98550_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	uint16_t rom_r(offs_t offset, uint16_t mem_mask = ~0);
	void rom_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);

	uint16_t catseye_r(address_space &space, offs_t offset, uint16_t mem_mask = ~0);
	void catseye_w(address_space &space, offs_t offset, uint16_t data, uint16_t mem_mask = ~0);

	uint16_t vram_r(offs_t offset, uint16_t mem_mask = ~0);
	void vram_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);

	static constexpr int CATSEYE_COUNT = 8;


	uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
protected:
	required_device<nereid_device> m_nereid;
	required_device_array<catseye_device, CATSEYE_COUNT> m_catseye;

	dio32_98550_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	virtual space_config_vector memory_space_config() const override;

	void vblank_w(int state);
	void int_w(offs_t offset, uint8_t data);

	const address_space_config m_space_config;
	void map(address_map &map);
	void update_int();

	static constexpr int m_fb_width = 2048;
	static constexpr int m_h_pix = 1280;
	static constexpr int m_v_pix = 1024;

	required_region_ptr<uint8_t> m_rom;
	required_shared_ptr_array<uint8_t, 2> m_vram;

	uint16_t m_plane_mask;
	uint8_t m_intreg;
	uint8_t m_ints;
};

} // namespace bus::hp_dio

// device type definition
DECLARE_DEVICE_TYPE_NS(HPDIO_98550, bus::hp_dio, dio32_98550_device)

#endif // MAME_BUS_HPDIO_98550_H
