/*
 * ADCcolor.cpp
 *
 * Created: 13-09-2014 18:40:05
 *  Author: Urvashi
 */ 


# define F_CPU 1000000
#include <avr/io.h>
# include <util/delay.h>
void lcd_init();
void disp_cmd(unsigned int cmd);
void disp_data(int cmd);
void disp_num(unsigned int num);
void disp_string(  char *str);
int adc_read(int channel);
void motor(int k,int l);
void left();
void right();
void forward();
void stop();
void backward();
int main(void)
{
	
	DDRB = 0XFF;
	DDRD=0XFF;
	lcd_init();
	disp_cmd(0X80);
	disp_string("WELCOME");
	_delay_ms(1000);
	disp_cmd(0X01);
	_delay_ms(2);
	disp_cmd(0X80);
	disp_string("Enter the value");
	

	
	int X,Y;
	while (1)
	{
		X=adc_read(0);
		Y=adc_read(1);
		
		//_delay_ms(1000);
		//disp_cmd(0X01);
		//_delay_ms(2);
		//disp_cmd(0X85);
		//disp_num(X);
		//disp_cmd(0XC5);
		//disp_num(Y);
		
		
		
		motor(X,Y);
		
		_delay_ms(100);
	}
	return 0;
}			
		
	int adc_read(int channel)
	{
		ADMUX=0X40 + channel;
		ADCSRA=0XD7;
		while((ADCSRA & 0X10) ==0);
		return ADC;
	}
	void disp_cmd(unsigned int cmd)
	{
		PORTB=((cmd & 0XF0)+0X04);
		_delay_ms(1);
		PORTB=PORTB - 0X04;
		PORTB=(((cmd<<4)& 0XF0)+0X04);
		_delay_ms(1);
		PORTB=PORTB-0X04;
		
	}
	void disp_data( int cmd)
	{
		PORTB=((cmd  & 0XF0)+0X05);
		_delay_ms(1);
		PORTB=PORTB - 0X04;
		PORTB=(((cmd <<4)& 0XF0)+0X05);
		_delay_ms(1);
		PORTB=PORTB-0X04;
		
	}

	void disp_string( char *str)
	{
		int i=0;
		while (str[i]!='\0')
		{
			disp_data (str[i]);
			i++;
			
		}
	}

	void disp_num(unsigned int num)
	{
		int a=0;
		if (num==0)
		{
			disp_data(48);
		}
		disp_cmd (0X04);
		while (num!=0)
		{
			a=num % 10;
			disp_data(a+48);
			num=num/10;
		}
		disp_cmd (0X06);
	}
	void lcd_init()
	{
		disp_cmd(0X02);
		disp_cmd(0X28);
		disp_cmd(0X0C);
		disp_cmd(0X06);
	}
	void motor(int k,int l)
	{
		
		
		
		if ((k>360 && k<390) && (l>400))
		{
			forward();
			//disp_string("FORWARD");
		}
		if ((k>250 && k<300) && (l>380 && l<400))
		{
			left();
			//disp_string("LEFT");
		}
		if ((k>390 && k<450) && (l>360 && l<380))
		{
			right();
			//disp_string("RIGHT");
		}
		if ((k>300 && k<360) && (l>300 && l< 400))
		{
			backward();
			//disp_string("BACKWARD");
		}
	}	
			
	
	void left()
	{
		PORTD=0X10;
		
		disp_cmd(0X86);
		disp_string ( "LEFT    ");
		_delay_ms(10);
		
	}

	void right()
	{
		PORTD=0x40;
	
		disp_cmd(0X86);
		disp_string ( "RIGHT    ");
		_delay_ms(10);
	}

	void forward()
	{
		PORTD=0X50;
	
		disp_cmd(0X86);

		disp_string ( "FORWARD ");
		_delay_ms(10);
	}
	void backward()
	{
		PORTD=0XA0;
		
		disp_cmd(0X86);
		
		disp_string ( "BACKWARD ");
		_delay_ms(10);
	}
	void stop()
	{
		PORTD=0X00;
		
		disp_cmd(0X86);
		
		disp_string ( "STOP ");
	}	