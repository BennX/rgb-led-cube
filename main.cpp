#define F_CPU 22118400 // as the avr is running faster then spec
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "input/Input.h"
#include "display/Display.h"
#include "cube/Cube.h"

#include "util/settings.h"

long long ms();
void setup_cube_isr();
void toggle_info_led();

int main(void)
{
	cli();
	// set led port as output
	DDRB |= (1 << PINB3);

	Display::init();
	Display::out_p(0, 0) << PSTR("Init Routines");
	Cube &cube = Cube::instance();
	setup_cube_isr();
	Display::clear();
	Display::out_p(0, 0) << PSTR("Done");
	
	sei();

	for (uint8_t z = 0; z < 5; z++)
		for (uint8_t y = 0; y < 5; y++)
			for (uint8_t x = 0; x < 5; x++)
				cube << Voxel(x, y, z, Color(x / 4.0 * MAX_COLOR, y / 4.0 * MAX_COLOR, z / 4.0 * MAX_COLOR));

	long long start = 1; //long long since ms is a long long
	uint16_t delta = 0;	 // delta value always positiv
	uint16_t timer = 0;
	while (true)
	{
		start = ms();
		Display::update(delta);
		delta = ms() - start;
		timer += delta;
	}
}

void toggle_info_led()
{
	PORTB ^= (1 << PINB3); //toggle the testled
}

long long millis = 0;
long long ms()
{
	return millis;
}

void setup_cube_isr()
{
	//16 Bit timer
	TCCR1A = 0x00;						  // CTC on OCR1A
	TCCR1B |= (1 << CS00) | (1 << WGM12); //no prescaler
	TIMSK1 |= (1 << OCIE1A);			  //compare interrupt on A
	//OCR1A = 0x0ACD;//2765  = 8khz
	//OCR1A = 2212; // 10khz
	OCR1A = 1843; // 12khz
				  //OCR1A = 1580; // 14khz
				  //OCR1A = 1382; // 16khz
}

uint8_t counter = 0;
ISR(TIMER1_COMPA_vect)
{
	Cube::instance().render();

	counter++;
	if (counter % 12 == 0) //12khz
	{
		// 1khz routine here no need to clean counter
		millis++;
		Input::instance().update();
	}
}
