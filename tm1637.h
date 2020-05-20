#ifndef _TM1637_H_
#define _TM1637_H_

#include <Arduino.h>

#define ADDR_AUTO_INCREASE 0x40
#define ADDR_FIXED 0x44
#define START_ADDR 0xc0
#define KEY_SCAN 0x42


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
	enum PRESSED_KEY
	{
		NO_KEY =B11111111,
		K1S1= B11101111,
		K1S2= B01101111,
		K1S3 =B10101111,
		K1S4 =B00101111,
		K1S5 =B11001111,
		K1S6 =B01001111,
		K1S7 =B10001111,
		K1S8 =B00001111,
		K2S1 =B11110111,
		K2S2 =B01110111,
		K2S3 =B10110111,
		K2S4 =B00110111,
		K2S5 =B11010111,
		K2S6= B01010111,
		K2S7= B10010111,
		K2S8= B00010111
	};

	enum DISPLAY_NUM
	{
		NUM0=0x3f,
		NUM1=0x06,
		NUM2=0x5b,
		NUM3=0x4f,
		NUM4=0x66,
		NUM5=0x6d,
		NUM6=0x7d,
		NUM7=0x07,
		NUM8=0x7f,
		NUM9=0x6f
	};

	enum DISPLAY_WORD
	{
		A= 0x77,
		b= 0x7c,
		C= 0x39,
		C_UP= 0x61,
		C_DOWN =0x5c,
		d =0x5e,
		E =0x79,
		F =0x71,
		G =0x3d,
		MINUS =0x40,
		O =0x3f,
		O_UP= 0x63,
		O_DOWN =0x5c,
		U =0x3e,
		V =0x3e,
		H= 0x36,
		J =0x0e,
		L =0x38,
		P =0x73
	};

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

	PRESSED_KEY scan_key();
};


#endif //_TM1637_H_
