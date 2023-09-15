// license:BSD-3-Clause
// copyright-holders:Carl,Vas Crabb
#include "emu.h"
#include "rmnkbd.h"

#include "machine/keyboard.ipp"


namespace {

INPUT_PORTS_START( rmnimbus_keyboard )
	PORT_START("LINE0") // Key row 0 scancodes 00..07
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_UNUSED)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("ESC")         PORT_CODE(KEYCODE_ESC)          PORT_CHAR(0x001bU)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_1)            PORT_CHAR('1') PORT_CHAR('!')
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_2)            PORT_CHAR('2') PORT_CHAR('"')
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_3)            PORT_CHAR('3') PORT_CHAR(0x00a3U)
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_4)            PORT_CHAR('4') PORT_CHAR('$')
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_5)            PORT_CHAR('5') PORT_CHAR('%')
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_6)            PORT_CHAR('6') PORT_CHAR('^')

	PORT_START("LINE1") // Key row 1 scancodes 08..0F
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_7)            PORT_CHAR('7') PORT_CHAR('&')
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_8)            PORT_CHAR('8') PORT_CHAR('*')
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_9)            PORT_CHAR('9') PORT_CHAR('(')
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_0)            PORT_CHAR('0') PORT_CHAR(')')
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_MINUS)        PORT_CHAR('-') PORT_CHAR('_')
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_EQUALS)       PORT_CHAR('=') PORT_CHAR('+')
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("BSPACE")      PORT_CODE(KEYCODE_BACKSPACE)    PORT_CHAR(0x0008U)
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("TAB")         PORT_CODE(KEYCODE_TAB)          PORT_CHAR(0x0009U)

	PORT_START("LINE2") // Key row 2 scancodes 10..17
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_Q)            PORT_CHAR('q') PORT_CHAR('Q')
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_W)            PORT_CHAR('w') PORT_CHAR('W')
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_E)            PORT_CHAR('e') PORT_CHAR('E')
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_R)            PORT_CHAR('r') PORT_CHAR('R')
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_T)            PORT_CHAR('t') PORT_CHAR('T')
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_Y)            PORT_CHAR('y') PORT_CHAR('Y')
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_U)            PORT_CHAR('u') PORT_CHAR('U')
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_I)            PORT_CHAR('i') PORT_CHAR('I')

	PORT_START("LINE3") // Key row 3 scancodes 18..1F
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_O)            PORT_CHAR('o') PORT_CHAR('O')
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_P)            PORT_CHAR('p') PORT_CHAR('P')
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_OPENBRACE)    PORT_CHAR('[') PORT_CHAR('{')
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_CLOSEBRACE)   PORT_CHAR(']') PORT_CHAR('}')
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("ENTER")       PORT_CODE(KEYCODE_ENTER)        PORT_CHAR(0x0D)
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("CTRL")        PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL) // Either control
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_A)            PORT_CHAR('a') PORT_CHAR('A')
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_S)            PORT_CHAR('s') PORT_CHAR('S')

	PORT_START("LINE4") // Key row 4 scancodes 20..27
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_D)            PORT_CHAR('d') PORT_CHAR('D')
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_F)            PORT_CHAR('f') PORT_CHAR('F')
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_G)            PORT_CHAR('g') PORT_CHAR('G')
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_H)            PORT_CHAR('h') PORT_CHAR('H')
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_J)            PORT_CHAR('j') PORT_CHAR('J')
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_K)            PORT_CHAR('k') PORT_CHAR('K')
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_L)            PORT_CHAR('l') PORT_CHAR('L')
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_COLON)        PORT_CHAR(';') PORT_CHAR(':')

	PORT_START("LINE5") // Key row 5 scancodes 28..2F
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_QUOTE)        PORT_CHAR('\'') PORT_CHAR('@')
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_TILDE)        PORT_CHAR('#') PORT_CHAR('~')
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("LSHIFT")      PORT_CODE(KEYCODE_LSHIFT)       PORT_CHAR(UCHAR_SHIFT_1)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_BACKSLASH)    PORT_CHAR('\\') PORT_CHAR('|')
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_Z)            PORT_CHAR('z') PORT_CHAR('Z')
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_X)            PORT_CHAR('x') PORT_CHAR('X')
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_C)            PORT_CHAR('c') PORT_CHAR('C')
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_V)            PORT_CHAR('v') PORT_CHAR('V')

	PORT_START("LINE6") // Key row 6 scancodes 30..37
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_B)            PORT_CHAR('b') PORT_CHAR('B')
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_N)            PORT_CHAR('n') PORT_CHAR('N')
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_M)            PORT_CHAR('m') PORT_CHAR('M')
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_COMMA)        PORT_CHAR(',') PORT_CHAR('<')
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_STOP)         PORT_CHAR('.') PORT_CHAR('>')
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD)                          PORT_CODE(KEYCODE_SLASH)        PORT_CHAR('/') PORT_CHAR('?')
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("RSHIFT")      PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("PRT SC")      PORT_CODE(KEYCODE_ASTERISK)     PORT_CHAR(UCHAR_MAMEKEY(ASTERISK))

	PORT_START("LINE7") // Key row 7 scancodes 38..3F
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("ALT")         PORT_CODE(KEYCODE_LALT) PORT_CODE(KEYCODE_RALT) // Either alt
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("SPACE")       PORT_CODE(KEYCODE_SPACE)        PORT_CHAR(' ')
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("CAPS LOCK")   PORT_CODE(KEYCODE_CAPSLOCK)     PORT_CHAR(UCHAR_MAMEKEY(CAPSLOCK))
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("F1")          PORT_CODE(KEYCODE_F1)           PORT_CHAR(UCHAR_MAMEKEY(F1))
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("F2")          PORT_CODE(KEYCODE_F2)           PORT_CHAR(UCHAR_MAMEKEY(F2))
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("F3")          PORT_CODE(KEYCODE_F3)           PORT_CHAR(UCHAR_MAMEKEY(F3))
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("F4")          PORT_CODE(KEYCODE_F4)           PORT_CHAR(UCHAR_MAMEKEY(F4))
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("F5")          PORT_CODE(KEYCODE_F5)           PORT_CHAR(UCHAR_MAMEKEY(F5))

	PORT_START("LINE8") // Key row 8 scancodes 40..47
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("F6")          PORT_CODE(KEYCODE_F6)           PORT_CHAR(UCHAR_MAMEKEY(F6))
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("F7")          PORT_CODE(KEYCODE_F7)           PORT_CHAR(UCHAR_MAMEKEY(F7))
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("F8")          PORT_CODE(KEYCODE_F8)           PORT_CHAR(UCHAR_MAMEKEY(F8))
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("F9")          PORT_CODE(KEYCODE_F9)           PORT_CHAR(UCHAR_MAMEKEY(F9))
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("F10")         PORT_CODE(KEYCODE_F10)          PORT_CHAR(UCHAR_MAMEKEY(F1))
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("NUM LOCK")    PORT_CODE(KEYCODE_NUMLOCK)      PORT_CHAR(UCHAR_MAMEKEY(NUMLOCK))
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("SCROLL LOCK") PORT_CODE(KEYCODE_SCRLOCK)      PORT_CHAR(UCHAR_MAMEKEY(SCRLOCK))
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP7")         PORT_CODE(KEYCODE_7_PAD)        PORT_CHAR(UCHAR_MAMEKEY(7_PAD))

	PORT_START("LINE9") // Key row 9 scancodes 48..4F
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP8")         PORT_CODE(KEYCODE_8_PAD)        PORT_CHAR(UCHAR_MAMEKEY(8_PAD))
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP9")         PORT_CODE(KEYCODE_9_PAD)        PORT_CHAR(UCHAR_MAMEKEY(9_PAD))
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP-")         PORT_CODE(KEYCODE_MINUS_PAD)    PORT_CHAR(UCHAR_MAMEKEY(MINUS_PAD))
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP4")         PORT_CODE(KEYCODE_4_PAD)        PORT_CHAR(UCHAR_MAMEKEY(4_PAD))
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP5")         PORT_CODE(KEYCODE_5_PAD)        PORT_CHAR(UCHAR_MAMEKEY(5_PAD))
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP6")         PORT_CODE(KEYCODE_6_PAD)        PORT_CHAR(UCHAR_MAMEKEY(6_PAD))
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP+")         PORT_CODE(KEYCODE_PLUS_PAD)     PORT_CHAR(UCHAR_MAMEKEY(PLUS_PAD))
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP1")         PORT_CODE(KEYCODE_1_PAD)        PORT_CHAR(UCHAR_MAMEKEY(1_PAD))

	PORT_START("LINEA") /* Key row 10 scancodes 50..57 */
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP2")         PORT_CODE(KEYCODE_2_PAD)        PORT_CHAR(UCHAR_MAMEKEY(2_PAD))
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP3")         PORT_CODE(KEYCODE_3_PAD)        PORT_CHAR(UCHAR_MAMEKEY(3_PAD))
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP0")         PORT_CODE(KEYCODE_0_PAD)        PORT_CHAR(UCHAR_MAMEKEY(0_PAD))
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD) PORT_NAME("KP.")         PORT_CODE(KEYCODE_DEL_PAD)      PORT_CHAR(UCHAR_MAMEKEY(DEL_PAD))
	PORT_BIT(0xf0, IP_ACTIVE_HIGH, IPT_UNUSED)
INPUT_PORTS_END
} // anonymous namespace


rmnimbus_keyboard_device::rmnimbus_keyboard_device(const machine_config& mconfig, const char* tag, device_t* owner, uint32_t clock)
	: buffered_rs232_device(mconfig, RMNIMBUS_KEYBOARD, tag, owner, clock)
	, device_matrix_keyboard_interface(mconfig, *this, "LINE0", "LINE1", "LINE2", "LINE3", "LINE4", "LINE5", "LINE6", "LINE7", "LINE8", "LINE9", "LINEA")
{
}


ioport_constructor rmnimbus_keyboard_device::device_input_ports() const
{
	return INPUT_PORTS_NAME(rmnimbus_keyboard);
}


void rmnimbus_keyboard_device::device_reset()
{
	buffered_rs232_device::device_reset();

	reset_key_state();
	clear_fifo();

	set_data_frame(1, 8, PARITY_NONE, STOP_BITS_1);
	set_rate(9'600);
	receive_register_reset();
	transmit_register_reset();

	output_dcd(0);
	output_dsr(0);
	output_cts(0);
	output_rxd(1);

	start_processing(attotime::from_hz(2'400));
}


void rmnimbus_keyboard_device::key_make(uint8_t row, uint8_t column)
{
	transmit_byte((row << 3) | column);
}


void rmnimbus_keyboard_device::key_break(uint8_t row, uint8_t column)
{
	transmit_byte(0x80U | (row << 3) | column);
}


void rmnimbus_keyboard_device::received_byte(uint8_t byte)
{
	logerror("received command %02x", byte);
}


DEFINE_DEVICE_TYPE(RMNIMBUS_KEYBOARD, rmnimbus_keyboard_device, "rmnimbus_keyboard", "RM Nimbus Keyboard")
