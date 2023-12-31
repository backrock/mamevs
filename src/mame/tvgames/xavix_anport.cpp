// license:BSD-3-Clause
// copyright-holders:David Haywood

// are these still part of the ADC? if so merge into xavix_adc.cpp

#include "emu.h"
#include "xavix_anport.h"

#define VERBOSE 0
#include "logmacro.h"

DEFINE_DEVICE_TYPE(XAVIX_ANPORT, xavix_anport_device, "xavix_anport", "XaviX Analog ports")

xavix_anport_device::xavix_anport_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, XAVIX_ANPORT, tag, owner, clock)
	, m_in0_cb(*this, 0xff)
	, m_in1_cb(*this, 0xff)
	, m_in2_cb(*this, 0xff)
	, m_in3_cb(*this, 0xff)
{
}

void xavix_anport_device::device_start()
{
}

void xavix_anport_device::device_reset()
{
}


uint8_t xavix_anport_device::mouse_7b00_r()
{
	LOG("%s: mouse_7b00_r\n", machine().describe_context());
	return m_in0_cb();

}

uint8_t xavix_anport_device::mouse_7b01_r()
{
	LOG("%s: mouse_7b01_r\n", machine().describe_context());
	return m_in1_cb();
}

uint8_t xavix_anport_device::mouse_7b10_r()
{
	LOG("%s: mouse_7b10_r\n", machine().describe_context());
	return m_in2_cb();
}

uint8_t xavix_anport_device::mouse_7b11_r()
{
	LOG("%s: mouse_7b11_r\n", machine().describe_context());
	return m_in3_cb();
}

void xavix_anport_device::mouse_7b00_w(uint8_t data)
{
	LOG("%s: mouse_7b00_w %02x\n", machine().describe_context(), data);
}

void xavix_anport_device::mouse_7b01_w(uint8_t data)
{
	LOG("%s: mouse_7b01_w %02x\n", machine().describe_context(), data);
}

void xavix_anport_device::mouse_7b10_w(uint8_t data)
{
	LOG("%s: mouse_7b10_w %02x\n", machine().describe_context(), data);
}

void xavix_anport_device::mouse_7b11_w(uint8_t data)
{
	LOG("%s: mouse_7b11_w %02x\n", machine().describe_context(), data);
}


