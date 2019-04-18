/*
 * A simple library to interface with rdm6300 rfid reader.
 * Arad Eizen (https://github.com/arduino12) 23/09/18.
 * Sakib Ahmed (https://github.com/ahmadSum1) 18/04/2019
 */

#include "Arduino.h" //Needed for Stream

#ifndef _RDM6300_h_
#define _RDM6300_h_

#ifdef ARDUINO_ARCH_ESP32
	#include <HardwareSerial.h>
#else
	#include <SoftwareSerial.h>
#endif

#define RDM6300_BAUDRATE		9600
#define RDM6300_PACKET_SIZE		14
#define RDM6300_PACKET_BEGIN	0x02
#define RDM6300_PACKET_END		0x03
#define RDM6300_NEXT_READ_MS	220

class Rdm6300
{
	public:
		void begin(int rxPin, uint8_t uart_nr=1);
		void begin(Stream &serialPort = Serial); //If user doesn't specificy then Serial will be used
		bool update(void);
		uint32_t get_tag_id(void);
		bool is_tag_near(void);
	private:
#ifdef GENERIC
		Stream * _serial; //The generic connection to user's chosen serial hardware
		
#elif ARDUINO_ARCH_ESP32
		HardwareSerial * _serial;
#else
		SoftwareSerial * _serial;
#endif
		uint32_t _tag_id = 0;
		uint32_t _last_tag_id = 0;
		uint32_t _next_read_ms = 0;
};

#endif
