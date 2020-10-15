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

#include "mpu6050.h"
#include "essential.h"
#include "uart.h"

int16_t ax,ay,az,distance=0, gx,gy,gz;

int Container=0;
double cycle=0,cycle2=0;

/************************************************************************
*ouputdata, sends data
*Purpose: Send accelerometer & gyro data to uart
*Input: void
*Return: void
************************************************************************/
void outputdata(){
	mpu6050_getRawData(&ax,&ay,&az,&gx,&gy,&gz);		//getsraw accelorometerdata
	uart_puti16(ax);
	uart_putc('\n');
	uart_puti16(ay);
	uart_putc('\n');
	uart_puti16(az);
	uart_putc('\n');
	uart_puti16(gx);
	uart_putc('\n');
	uart_puti16(gy);
	uart_putc('\n');
	uart_puti16(gz);
	uart_putc('\n');
}
/*****************************************
*enabletrigg,enables trigger pin		 *
*Purpose: enable the trigger pin for 10us*
*Input: void							 *
*Return: void							 *
******************************************/
void enabletrigg(){
	PORTB |=(1<<Trigger);
	_delay_us(10);
	PORTB &=~(1<<Trigger);
}
/************************************************
*timercalc, calculate time						*	
*Purpose: enable trigger pin and calculate time	*
*Input: void
*Return: void
*************************************************/
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
	
	pwminit();			//initializing PWM
    
	DDRD = (1<<LC1) | (1<<LC2) |(1<<lpwm) |(1<<Rpwm)|(1<<RC1);		//sets all of these ports to output
	
	DDRB |= (1<<RC2) ;
	
	DDRB |= (1<<led);				//sets these port to output
		
	PORTD |=(1<<lpwm) | (1<<Rpwm);		//sets these ports to high
	
	DDRB |= (1<<Trigger);		//sets this port to output

	DDRD &=~(1<<Echo);		//sets to input
	
	PORTD |=(1<<Echo);		//activate pull up
	
	EICRA |=(1<<ISC10);		//enables interrupt on any logic change
	
	EIMSK |=(1<<INT1);		//enables interrupt on INT1
	
	
	
	enabletrigg();			//turns on trigger
	
	turnforward();		//sets direction to forward
	
	initUART();			//initializing uart
	
	sei();			//enables global interrupt
	
	TCCR0B = (1<<CS00) | (1<<CS02);		//sets prescaler to 1024 timer0
	
	TCCR1B =(1<<CS10);		//no prescaler timer1

    while (1) //infinite loop
    {
		
		timercalc();		//checks timer condition
		outputdata();
		
		if(distance>4 && distance<15){		//condition for sensor stopping motor
		
		stop(&cycle2,&cycle); //sets to stop motor
		
		PORTB |=(1<<led);			//turn on LED		
			}
			
			else{		
			
			turnforward();		//set wheel direction to forward
			
			go(&cycle2,&cycle);		//sets the same power to both wheels
			
			PORTB &=~(1<<led); //turn off LED
			
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