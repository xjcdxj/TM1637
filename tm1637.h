#ifndef _TM1637_H_
#define _TM1637_H_

#include <Arduino.h>

#define ADDR_AUTO_INCREASE 0x40
#define ADDR_FIXED 0x44
#define START_ADDR 0xc0
#define KEY_SCAN 0x42
#define A  0x77
#define b  0x7c
#define C  0x39
#define C_UP  0x61
#define C_DOWN  0x5c
#define d  0x5e
#define E  0x79
#define F  0x71
#define G  0x3d
#define MINUS  0x40
#define O  0x3f
#define O_UP  0x63
#define O_DOWN  0x5c
#define U  0x3e
#define V  0x3e
#define H  0x36
#define J  0x0e
#define L  0x38
#define P  0x7
#define NO_KEY  B11111111
#define K1S1  B11101111
#define K1S2  B01101111
#define K1S3  B10101111
#define K1S4  B00101111
#define K1S5  B11001111
#define K1S6  B01001111
#define K1S7  B10001111
#define K1S8  B00001111
#define K2S1  B11110111
#define K2S2  B01110111
#define K2S3  B10110111
#define K2S4  B00110111
#define K2S5  B11010111
#define K2S6  B01010111
#define K2S7  B10010111
#define K2S8  B00010111
static uint8_t display_num[10] = {
	0x3f,
	0x06,
	0x5b,
	0x4f,
	0x66,
	0x6d,
	0x7d,
	0x07,
	0x7f,
	0x6f
};
class TM1637
{
private:
	boolean is_correct_ack = true;
	uint8_t display_num_count_ = 4; //set the number of, more than 6 will be ignored
	uint8_t brightness_ = 7;
	uint8_t dio_pin_, clk_pin_;

	void start();

	void stop();

	void show(); //show the value
	void write_byte(uint_least8_t data); //write byte value to chip

public:




	boolean getIsCorrectAck() const;

	TM1637(uint8_t dioPin, uint8_t clkPin);

	void set_brightness(uint8_t brightness);


	void set_display_num_count(uint8_t display_num_count);



	/*
	 display a number in position
	*/
	void display(uint8_t index, uint8_t value, bool show_point);

	//put byte to the position
	void display_byte(uint8_t index, uint8_t display_byte);

	//display an array from 0 index
	void display(const uint8_t* display_data, uint8_t length);

	void clear_display();

	void test();

	uint8_t scan_key();
};


#endif //_TM1637_H_
