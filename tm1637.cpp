#include "TM1637.h"
#include <Arduino.h>

TM1637::TM1637(uint8_t dioPin, uint8_t clkPin)
{
	dio_pin_ = dioPin;
	clk_pin_ = clkPin;
	pinMode(dio_pin_, OUTPUT);
	pinMode(clk_pin_, OUTPUT);
	clear_display();
}

void TM1637::display(const uint8_t* display_data, uint8_t length)
{
	start();
	write_byte(ADDR_AUTO_INCREASE);
	stop();
	start();
	write_byte(START_ADDR);
	for (uint8_t i = 0; i < min(length, display_num_count_); i++)
	{
		write_byte(display_data[i]);
	}
	stop();
	show();
}

void TM1637::set_display_num_count(uint8_t display_num_count)
{
	this->display_num_count_ = display_num_count;
}

void TM1637::display(uint8_t index, uint8_t value, bool show_point)
{
	if (index > display_num_count_ - 1)
	{
		return;
	}
	index = max(index, display_num_count_);
	start();
	write_byte(ADDR_FIXED);
	stop();
	start();
	write_byte(START_ADDR | index);
	// value = show_point ? 0x80 | value : value;
	write_byte(show_point ? 0x80 | value : value);
	stop();
	show();
}



void TM1637::display_byte(uint8_t index, uint8_t display_byte)
{
	if (index > display_num_count_ - 1)
	{
		return;
	}
	start();
	write_byte(ADDR_FIXED);
	stop();
	start();
	write_byte(START_ADDR | index);
	write_byte(display_byte);
	stop();
	show();
}

void TM1637::start()
{
	digitalWrite(clk_pin_, HIGH);
	digitalWrite(dio_pin_, HIGH);
	// delayMicroseconds(2);
	digitalWrite(dio_pin_, LOW);
	digitalWrite(clk_pin_, LOW);
}

void TM1637::show()
{
	start();
	write_byte((0x07 & this->brightness_) | 0x88);
	stop();
}

void TM1637::stop()
{
	digitalWrite(clk_pin_, LOW);
	digitalWrite(dio_pin_, LOW);
	digitalWrite(clk_pin_, HIGH);
	digitalWrite(dio_pin_, HIGH);
}


void TM1637::write_byte(uint8_t data)
{
	for (uint8_t index = 0; index < 8; index++)
	{
		digitalWrite(clk_pin_, LOW);
		digitalWrite(dio_pin_, data & 0x01);
		digitalWrite(clk_pin_, HIGH);
		data >>= 1;
	}
	digitalWrite(clk_pin_, LOW);
	digitalWrite(dio_pin_, HIGH);
	pinMode(dio_pin_, INPUT);
	digitalWrite(clk_pin_, HIGH);
	is_correct_ack = !digitalRead(dio_pin_);
	pinMode(dio_pin_, OUTPUT);
	digitalWrite(dio_pin_, LOW);
}

uint8_t TM1637::scan_key()
{
	uint8_t key = 0x00;
	start();
	write_byte(KEY_SCAN);
	digitalWrite(dio_pin_, HIGH);
	pinMode(dio_pin_, INPUT);
	for (uint8_t i = 0; i < 8; i++)
	{
		key <<= 1;
		digitalWrite(clk_pin_, LOW);
		digitalWrite(clk_pin_, HIGH);
		key |= digitalRead(dio_pin_);
	}
	digitalWrite(clk_pin_, LOW);
	digitalWrite(clk_pin_, HIGH);
	is_correct_ack = !digitalRead(dio_pin_);
	pinMode(dio_pin_, OUTPUT);
	digitalWrite(dio_pin_, LOW);
	stop();
	return key;
}

void TM1637::clear_display()
{
	start();
	write_byte(ADDR_AUTO_INCREASE);
	stop();
	start();
	write_byte(START_ADDR);
	for (uint8_t i = 0; i < this->display_num_count_; i++)
	{
		write_byte(0x00);
	}
	stop();
	show();
}

void TM1637::set_brightness(uint8_t brightness)
{
	if (brightness > 7)
	{
		brightness = 7;
	}
	this->brightness_ = brightness;
}

boolean TM1637::getIsCorrectAck() const
{
	return is_correct_ack;
}
