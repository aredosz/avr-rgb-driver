#define LED_RED PB1
#define LED_GREEN PB2
#define LED_BLUE PB3
#define LED_RED_BLINKING PB4
#define MICROSWITCH_MODE PD2
#define MICROSWITCH_EFFECT PD3
#define POTENTIOMETER_GREEN PC0
#define POTENTIOMETER_BLUE PC1
#define POTENTIOMETER_RED PC2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "animate.h"
#include "masks.h"

volatile struct Masks masks = {1, 0, 0, 0, 0, 0, 0};
volatile struct Animate animate = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};

int main(void) {
	DDRB |= 1<<LED_RED;//set PB1 as output
	DDRB |= 1<<LED_GREEN;//set PB2 as output
	DDRB |= 1<<LED_BLUE;//set PB3 as output
	DDRB |= 1<<LED_RED_BLINKING;//set PB4 as output
	DDRC &= ~(1<<POTENTIOMETER_GREEN);//set ADC0 (PC0) as input
	DDRC &= ~(1<<POTENTIOMETER_BLUE);//set ADC1 (PC1) as input
	DDRC &= ~(1<<POTENTIOMETER_RED);//set ADC2 (PC2) as input
	DDRD &= ~(1<<MICROSWITCH_MODE);//set PD2 as input
	DDRD &= ~(1<<MICROSWITCH_EFFECT);//set PD3 as input

	PORTB |= 1<<LED_RED_BLINKING;//set high state for PB4
	PORTD |= 1<<MICROSWITCH_MODE;//turn on pull up resistor
	PORTD |= 1<<MICROSWITCH_EFFECT;//turn on pull up resistor

	MCUCR |= 1<<ISC01 | 1<<ISC11;//configure interrupts triggered by falling edge
	GICR |= 1<<INT0 | 1<<INT1;//turn on interrupts for INT0 (PD2) and INT1 (PD3)
	sei();//turn on interrupts

	ADMUX = 1<<REFS1 | 1<<REFS0 | 1<<ADLAR;//select internal 2.56V voltage reference with external capacitor at AREF pin and select ADC0. ADLAR bit is for left
	//adjusting ADC result to allow easy 8bit reading
	ADCSRA = 1<<ADEN | 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0 | 1<<ADIE | 1<<ADSC;//turn on ADC, set prescaler 128x, turn on interrupts and start A2D conversion

	TCCR1A |= 1<<COM1A1 | 1<<COM1B1 | 1<<WGM11;//set non-inverting mode and fast pwm
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10;//set fast pwm and no prescaling
	ICR1 = 255;

	TCCR2 |= 1<<WGM21 | 1<<WGM20 | 1<<COM21 | 1<<CS20;//set fast pwm, non-inverting mode and no prescaling

	turnOffLights();

	TCCR0 |= 1<<CS01 | 1<<CS00;//set prescaler 64x
	TIMSK |= 1<<TOIE0;

	while (1) {

	}

	return 0;
}

ISR(INT0_vect) {
	if (masks.switchModeDebouncing == 0) {
		masks.autoColor++;
		masks.effectNo = 0;
		masks.switchModeDebouncing = 1;
		masks.debouncingModeCounter = 0;
	}
}

ISR(INT1_vect) {
	if (masks.switchEffectDebouncing == 0) {
		masks.effectNo = ++masks.effectNo % 5;
		masks.switchEffectDebouncing = 1;
		masks.debouncingEffectCounter = 0;
	}
}

ISR(ADC_vect) {
	switch (ADMUX & 0x0F) {
	case 0x00:
		if (masks.autoColor == 0) {
			OCR1B = ADCH;
		}
		ADMUX = (ADMUX & 0xF0) | 0x01;//set ADC1
		break;

	case 0x01:
		if (masks.autoColor == 0) {
			OCR2 = ADCH;
		}
		ADMUX = (ADMUX & 0xF0) | 0x02;//set ADC2
		break;

	case 0x02:
		if (masks.autoColor == 0) {
			OCR1A = ADCH;
		}
		ADMUX &= 0xF0;//set ADC0
		break;
	}

	ADCSRA |= 1<<ADSC;
}

ISR(TIMER0_OVF_vect) {
	masks.blinkingCounter++;
	masks.debouncingEffectCounter++;
	masks.debouncingModeCounter++;
	if ((masks.autoColor == 1 && masks.blinkingCounter >= 12) || (masks.autoColor == 0 && masks.blinkingCounter >= 6)) {
		masks.blinkingCounter = 0;
		PORTB ^= 1<<LED_RED_BLINKING;
	}
	if (masks.switchModeDebouncing && masks.debouncingModeCounter >= 6) {
		masks.switchModeDebouncing = 0;
	}
	if (masks.switchEffectDebouncing && masks.debouncingEffectCounter >= 6) {
		masks.switchEffectDebouncing = 0;
	}

	if (masks.autoColor) {
		switch (masks.effectNo) {
		case 0:
			effectStarting(&animate);
			break;

		case 1:
			effectPolice(&animate);
			break;

		case 2:
			effectSnake(&animate);
			break;

		case 3:
			effectFlame(&animate);
			break;

		case 4:
		default:
			effectGYRMBC(&animate);
		}
	}
}
