void pwminit(){
	TCCR0A = (1<<COM0A1) |(1<<COM0B1) | (1<<WGM00) | (1<<WGM01);
	TIMSK0 = (1<<TOIE0);	
	}
	void go(double *lfm, double *rfm){
		*rfm = 50;
		*lfm = 50;
		
	}
	void turnright(double *lfm, double *rfm){
		*rfm = 0;
		*lfm = 60;
	}
	void turnleft(double *lfm, double *rfm){
		*rfm = 60;
		*lfm = 0;
	}
/************************************************************************
*stop, stop motors												       *
*Purpose: Turn off motors and set speed =0							   *
*Input: double, double												   *
*Return: void                                                          *
************************************************************************/
	void stop(double *lfm, double *rfm){
		*rfm = 0;
		*lfm=0;
		PORTB &=~ (1<<PORTB0);
		PORTD &=~(1<<PORTD4) | (1<<PORTD7) | (1<<PORTD2);
	}
/************************************************************************
*turnbackwards, wheels ccw											   *
*Purpose: Set wheel direction to counterclockwise					   *
*Input: void														   *
*Return: void                                                          *
************************************************************************/
	void turnonbackwards(){
		PORTB &=~ (1<<PORTB0);
		PORTD &=~(1<<PORTD4);
		PORTD |= (1<<PORTD7);
		PORTD |=(1<<PORTD2);
	}
/************************************************************************
*turnforward, wheels cw												   *
*Purpose: Set wheel direction to clockwise							   *
*Input: void														   *
*Return: void                                                          *
************************************************************************/
	void turnforward(){
		PORTB |= (1<<PORTB0);
		
		PORTD |= (1<<PORTD4);
		
		PORTD &=~ (1<<PORTD7);
		PORTD &=~(1<<PORTD2);
	}

/************************************************************************
* charcounter, count chars												*
*Purpose: counter non void spaces in an array                           *
*Input: char pointer													*
*Return: int															*
************************************************************************/

int charcounter(char *aa){
	int i =0;
	while(1)
	if (aa[i]!= '\0')
	{
		i++;
	}
	else if (aa[i]=='\0')
	{
		break;
	}
	return i;
}


