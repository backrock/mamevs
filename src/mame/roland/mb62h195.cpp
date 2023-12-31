// license:BSD-3-Clause
// copyright-holders:AJR
/***************************************************************************

    Roland MB62H195 gate array

    This is one of Roland's several multifunction I/O gate arrays including
    built-in address latches and chip select decoders. This one's
    particular features include both an LCD data FIFO (write-only) and a
    parallel/serial converter for a µPD7001 ADC (the clock for which is
    based on an internal oscillator).

***************************************************************************/

#include "emu.h"
#include "mb62h195.h"

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// device type definition
DEFINE_DEVICE_TYPE(MB62H195, mb62h195_device, "mb62h195", "Roland MB62H195 I/O")


//**************************************************************************
//  DEVICE IMPLEMENTATION
//**************************************************************************

//-------------------------------------------------
//  mb62h195_device - constructor
//-------------------------------------------------

mb62h195_device::mb62h195_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: device_t(mconfig, MB62H195, tag, owner, clock)
	, m_lc_callback(*this)
	, m_r_callback(*this, 0xff)
	, m_t_callback(*this)
	, m_da_callback(*this)
	, m_dc_callback(*this)
	, m_sout_callback(*this)
	, m_sck_callback(*this)
	, m_sin_callback(*this, 1)
	, m_adc_callback(*this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void mb62h195_device::device_start()
{
}
