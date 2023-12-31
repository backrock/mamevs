// license:BSD-3-Clause
// copyright-holders:smf
#include "emu.h"
#include "printer.h"

//**************************************************************************
//  CENTRONICS PRINTER DEVICE
//**************************************************************************

// device type definition
DEFINE_DEVICE_TYPE(CENTRONICS_PRINTER, centronics_printer_device, "centronics_printer", "Centronics Printer")


/***************************************************************************
    IMPLEMENTATION
***************************************************************************/
//-------------------------------------------------
//  centronics_printer_device - constructor
//-------------------------------------------------

centronics_printer_device::centronics_printer_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CENTRONICS_PRINTER, tag, owner, clock),
	device_centronics_peripheral_interface( mconfig, *this ),
	m_strobe(0),
	m_data(0),
	m_busy(0),
	m_printer(*this, "printer")
{
}

//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

void centronics_printer_device::device_add_mconfig(machine_config &config)
{
	PRINTER(config, m_printer, 0);
	m_printer->online_callback().set(FUNC(centronics_printer_device::printer_online));
}

void centronics_printer_device::device_start()
{
	m_ack_timer = timer_alloc(FUNC(centronics_printer_device::ack_timer_tick), this);
	m_busy_timer = timer_alloc(FUNC(centronics_printer_device::busy_timer_tick), this);

	/* register for state saving */
	save_item(NAME(m_strobe));
	save_item(NAME(m_data));
	save_item(NAME(m_busy));
}

void centronics_printer_device::device_reset()
{
	m_busy = false;
	output_busy(m_busy);
	output_fault(1);
	output_ack(1);
	output_select(1);
}



/*-------------------------------------------------
    printer_online - callback that
    sets us busy when the printer goes offline
-------------------------------------------------*/

void centronics_printer_device::printer_online(int state)
{
	output_perror(!state);
}

/*-------------------------------------------------
    ack_timer_tick - update the printer
    acknowledge line after an appropriate delay
-------------------------------------------------*/

TIMER_CALLBACK_MEMBER(centronics_printer_device::ack_timer_tick)
{
	output_ack(param);

	if (!param)
	{
		/* data is now ready, output it */
		m_printer->output(m_data);

		/* ready to receive more data, return BUSY to low */
		m_busy_timer->adjust(attotime::from_usec(7), 0);
	}
}

/*-------------------------------------------------
    busy_timer_tick - update the printer's
    busy state
-------------------------------------------------*/

TIMER_CALLBACK_MEMBER(centronics_printer_device::busy_timer_tick)
{
	m_busy = param;
	output_busy(m_busy);

	if (param)
	{
		/* timer to turn ACK low to receive data */
		m_ack_timer->adjust(attotime::from_usec(10), 0);
	}
	else
	{
		/* timer to return ACK to high state */
		m_ack_timer->adjust(attotime::from_usec(5), 1);
	}
}

/*-------------------------------------------------
    centronics_strobe_w - signal that data is
    ready
-------------------------------------------------*/

void centronics_printer_device::input_strobe(int state)
{
	/* look for a high -> low transition */
	if (m_strobe == true && state == false && m_busy == false)
	{
		/* STROBE has gone low, data is ready */
		m_busy_timer->adjust(attotime::zero, true);
	}

	m_strobe = state;
}


/*-------------------------------------------------
    centronics_prime_w - initialize and reset
    printer (centronics mode)
-------------------------------------------------*/

void centronics_printer_device::input_init(int state)
{
	/* reset printer if line is low */
	if (state == false)
		device_reset();
}
