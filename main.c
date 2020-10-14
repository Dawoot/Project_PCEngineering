#define F_CPU 16000000UL

#define LC1		PORTD2
#define LC2		PORTD4
#define lpwm	PORTD5
#define Rpwm	PORTD6
#define RC1		PORTD7
#define RC2		PORTB0
#define Trigger		PORTB1
#define Echo		PORTD3
#define led			PORTB2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "essential.h"
#include "uart.h"

uint16_t ax,ay,az,distance=0;

int Container=0;
double cycle=70,cycle2=70;

void enabletrigg(){
	PORTB |=(1<<Trigger);
	_delay_us(10);
	PORTB &=~(1<<Trigger);
}

void timercalc(){
	if ((PIND & (1<<PIND3)) ==0)
	{
		enabletrigg();
		
	}if (TCNT1>0)
	{
		distance = (Container/16)/58.2;
	}
}

int main(void)
{
	mpu6050_init();			//initializing the gyro/accelorometer
	
	//initUART();			//initializing uart
	
	pwminit();			//initializing PWM
    
	DDRD = (1<<LC1) | (1<<LC2) |(1<<lpwm) |(1<<Rpwm)|(1<<RC1);		//sets all of these ports to output
	
	DDRB |= (1<<RC2) ;			//Set right wheel to output
	
	DDRB |= (1<<led);				//sets these port to output
		
	PORTD |=(1<<lpwm) | (1<<Rpwm);		//sets these ports to high
	
	DDRB |= (1<<Trigger);		//sets this port to output

	DDRD &=~(1<<Echo);		//sets to input
	
	PORTD |=(1<<Echo);		//activate pull up
	
	EICRA |=(1<<ISC10);		//enables interrupt on any logic change
	
	EIMSK |=(1<<INT1);		//enables interrupt on INT1
	
	enabletrigg();			//turns on trigger
	
	turnforward();		//sets direction to forward
	
	sei();			//enables global interrupt
	
	TCCR0B = (1<<CS00) | (1<<CS02);		//sets prescaler to 1024 timer0
	
	TCCR1B =(1<<CS10);		//no prescaler timer1

    while (1) //infinite loop
    {
		
		timercalc();		//checks timer condition
		
			
				if(distance==0 || distance>15){		//condition for sensor
					
				go(&cycle2,&cycle);		//sets the same power to both wheels 
				
				PORTB &=~(1<<led); //turn off LED
								
			}
			while(distance>0 && distance<15){		//condition for sensor stopping motor
				
			turnright(&cycle2,&cycle); //sets to turn left if it is set for forward otherwise turn right
			
			PORTB |=(1<<led);			//turn on LED
			
			timercalc();		//checks timer condition 
		/*	uart_puti16(distance);
			uart_putc('\n');
			*/
			if (distance<0 && distance>10)		//turn off while loop
			{
				PORTB |=(1<<PORTB0);		//turns on right wheel again
				break;
			}
			}
			
			
		}
}
ISR(TIMER0_OVF_vect){
	OCR0A = (cycle/100)*255;		//sets the power of the right motor
	OCR0B= (cycle2/100)*255;	//sets the power of the left	motor
}
ISR(INT1_vect){
	if ((PIND & (1<<PIND3)))		//checks if the echo pin is high
	{
		TCNT1=0;		//restart timer count
		Container=0;	//reset timer container
		}else{
		Container=TCNT1;	//Contains timer value
	}	
}