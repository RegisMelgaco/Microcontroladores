#include <avr/io.h>
#include <util/delay.h>


int count_with_overflow(int counter) {
	if(counter > 9999) {
		return 0;
	} else {
		return counter + 1;
	}
}

void display_digit (char display, char digit) {
	int time = 10;
	
	char sev_seg_num_code[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
	char lcd_code[4] = {0x07, 0x0b, 0x0d, 0x0e};
		
		
	// turn-on display
	PORTC = lcd_code[display];
	// send digit code
	PORTD = sev_seg_num_code[digit];
	
	_delay_ms(time);
}

void display_number (int num) {
	int i = 0;
	int number = num;
	
	for (i = 0; i < 4; i++) {
		display_digit(i, (number % 10));
		number /= 10;
	}
}

int main(void)
{
	int counter = 0;
	
	DDRC = 0xff;
	DDRD = 0xff;
	
	while (1)
	{
		counter = count_with_overflow(counter);
		
		// show same number 100 times, so the number will be displayed for 1 second
 		for (int i = 0; i < 25; i++)
 			display_number(counter);
	}
	
	return 0;
}
