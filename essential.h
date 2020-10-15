/************************************************************************
*pwminit, initialize pwm
*Purpose: Enable the pwm on both motors
*Input: void
*Return: void                                                                     
************************************************************************/
void pwminit(){
	TCCR0A = (1<<COM0A1) |(1<<COM0B1) | (1<<WGM00) | (1<<WGM01);
	TIMSK0 = (1<<TOIE0);	
	}
	/***********************************************************************
	*go, go in a direction												   *
	*Purpose: Set the same speed for the wheels							   *
	*Input: double lfm, double rfm										   *
	*Return: void                                                          *
	************************************************************************/
	void go(double *lfm, double *rfm){
		*rfm = 70;
		*lfm = 70;
		
	}
	/************************************************************************
	*turnsoftleft, turn left												 *
	*Purpose: Turn left soft when forward and set motorspeed				*
	*Input: double lfm, double rfm										    *
	*Return: void                                                           *
	************************************************************************/
	void turnsoftpleft(double *lfm, double *rfm){
		*rfm = 60;
		*lfm = 0;
	}
	/***********************************************************************
	*turnsoftright, turn right										       *
	*Purpose: Turn right soft when forward and set motorspeed			   *
	*Input: double lfm, double rfm										   *
	*Return: void                                                          *
	************************************************************************/
	void turnsoftright(double *lfm,double *rfm){
		*rfm = 0;
		*lfm = 60;
	}
	/***********************************************************************
	*turnshapright, turn right										       *
	*Purpose: Turn right hard when forward and set motorspeed			   *
	*Input: double lfm, double rfm										   *
	*Return: void                                                          *
	************************************************************************/
	void turnsharpright(double *lfm, double *rfm){
		*rfm = 0;
		*lfm = 100;
	}
	/************************************************************************
	*turnsharpleft, turn left												*
	*Purpose: Turn left hard when forward and set motorspeed				*
	*Input: double lfm, double rfm										    *
	*Return: void                                                           *
	************************************************************************/
	void turnsharpleft(double *lfm, double *rfm){
		*rfm = 100;
		*lfm = 0;
	}
/***********************************************************************
*stop, stop motors												       *
*Purpose: Turn off motors and set speed =0							   *
*Input: double lfm, double rfm										   *
*Return: void                                                          *
************************************************************************/
	void stop(double *lfm, double *rfm){
		*rfm = 0;
		*lfm=0;
		PORTB &=~ (1<<PORTB0);
		PORTD &=~(1<<PORTD4) | (1<<PORTD7) | (1<<PORTD2);
	}
/***********************************************************************
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


