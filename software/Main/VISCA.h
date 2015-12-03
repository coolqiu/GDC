
/*
Overview of VISCA
In VISCA, the device outputting commands, for
example, a computer, is called the controller. The
device receiving the commands, an FCB camera is
called the peripheral device. In VISCA, up to seven
peripheral devices like the FCB camera can be
connected to one controller using communication
conforming to the RS-232C standard. The parameters
of RS-232C are as follows.
- Communication speed: 9.6 kbps/19.2 kbps/38.4 kbps/115.2 kbps
- Data bits : 8
- Start bit : 1
- Stop bit : 1
- Non parity
Flow control using XON/XOFF and RTS/CTS, etc., is
not supported.
	*/
#define VISCA_TERMINATOR 0xff
	