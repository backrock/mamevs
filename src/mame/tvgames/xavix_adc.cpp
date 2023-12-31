// license:BSD-3-Clause
// copyright-holders:David Haywood

#include "emu.h"
#include "xavix_adc.h"

#define VERBOSE 0
#include "logmacro.h"

DEFINE_DEVICE_TYPE(XAVIX_ADC, xavix_adc_device, "xavix_adc", "XaviX ADC")

xavix_adc_device::xavix_adc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, XAVIX_ADC, tag, owner, clock)
	, m_in0_cb(*this, 0xff)
	, m_in1_cb(*this, 0xff)
	, m_in2_cb(*this, 0xff)
	, m_in3_cb(*this, 0xff)
	, m_in4_cb(*this, 0xff)
	, m_in5_cb(*this, 0xff)
	, m_in6_cb(*this, 0xff)
	, m_in7_cb(*this, 0xff)
{
}

void xavix_adc_device::device_start()
{
	m_adc_timer = timer_alloc(FUNC(xavix_adc_device::adc_timer_done), this);

	save_item(NAME(m_adc_control));
	save_item(NAME(m_adc_inlatch));
}

TIMER_CALLBACK_MEMBER(xavix_adc_device::adc_timer_done)
{
	//m_irqsource |= 0x04;
	//update_irqs();
}

void xavix_adc_device::device_reset()
{
	m_adc_control = 0x00;
	m_adc_inlatch = 0xff;
}


uint8_t xavix_adc_device::adc_7b80_r()
{
	LOG("%s: adc_7b80_r\n", machine().describe_context());
	return m_adc_inlatch;
}

void xavix_adc_device::adc_7b80_w(uint8_t data)
{
	// is the latch writeable?
	LOG("%s: adc_7b80_w %02x\n", machine().describe_context(), data);
}

void xavix_adc_device::adc_7b81_w(uint8_t data)
{
//  m_irqsource &= ~0x04;
//  update_irqs();

	LOG("%s: adc_7b81_w %02x\n", machine().describe_context(), data);
	m_adc_control = data;

	// bit 0x40 = run? or IRQ? (doesn't seem to be any obvious way to clear IRQs tho, ADC handling is usually done in timer IRQ?)
	// should probably set latch after a timer has expired not instantly?
	// bits 0x0c are not port select?
	// bit 0x80 is some kind of ack? / done flag?
	switch (m_adc_control & 0x13)
	{
	case 0x00: m_adc_inlatch = m_in0_cb(); break;
	case 0x01: m_adc_inlatch = m_in1_cb(); break;
	case 0x02: m_adc_inlatch = m_in2_cb(); break;
	case 0x03: m_adc_inlatch = m_in3_cb(); break;
	case 0x10: m_adc_inlatch = m_in4_cb(); break;
	case 0x11: m_adc_inlatch = m_in5_cb(); break;
	case 0x12: m_adc_inlatch = m_in6_cb(); break;
	case 0x13: m_adc_inlatch = m_in7_cb(); break;
	}

//  m_adc_timer->adjust(attotime::from_usec(200));
}

uint8_t xavix_adc_device::adc_7b81_r()
{
//  has_wamg polls this if interrupt is enabled
	return machine().rand();
}


