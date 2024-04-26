#include<reg51.h>
#define data P3
#define wait 10
sbit rs=P2^0;
sbit rw=P2^1;
sbit en=P2^2;
int t1, t2,t3;

char flag=0;
char j=0;
void disp_num(int num);
void lcd_int();
void cmd(unsigned char c);
void dat(unsigned char d);
void lcd_string(char *s);
void equal( int j1);

void delay(unsigned  int t)
{
	int m,g;
	for(m=0;m<t;m++)
		for(g=0;g<1275;g++);
}

int main()
{ 
	int i,n=0;
	lcd_int();
	while(1)
	{
		P1=0xfe;
		i=P1;
		switch(i)
		{
			case 0x7e:
				lcd_string("/");
			flag=1;
			j=1;
				delay(wait);
				break;
			
			case 0xbe:
				lcd_string("9");
				delay(wait);
				if(flag==0)
					t1=t1*10+9;
				else
					t2=t2*10+9;
				break;
			
			case 0xde:
				lcd_string("8");
				delay(wait);
			if(flag==0)
					t1=t1*10+8;
				else
					t2=t2*10+8;
				break;
			
			case 0xee:
				lcd_string("7");
				delay(wait);
			if(flag==0)
					t1=t1*10+7;
				else
					t2=t2*10+7;
				break;
		}
		
		P1=0xfd;
		i=P1;
		switch(i)
		{
			case 0x7d:
				lcd_string("*");
			flag=1;
			j=2;
				delay(wait);
				break;
			
			case 0xbd:
				lcd_string("6");
				delay(wait);
			if(flag==0)
					t1=t1*10+6;
				else
					t2=t2*10+6;
				break;
			
			case 0xdd:
				lcd_string("5");
				delay(wait);
			if(flag==0)
					t1=t1*10+5;
				else
					t2=t2*10+5;
				break;
			
			case 0xed:
				lcd_string("4");
				delay(wait);
			if(flag==0)
					t1=t1*10+4;
				else
					t2=t2*10+4;
				break;
		}
		
		P1=0xfb;
		i=P1;
		switch(i)
		{
			case 0x7b:
				lcd_string("-");
			   flag =1;
			j=3;
				delay(wait);
				break;
			
			case 0xbb:
				lcd_string("3");
				delay(wait);
			if(flag==0)
					t1=t1*10+3;
				else
					t2=t2*10+3;
				break;
			
			case 0xdb:
				lcd_string("2");
				delay(wait);
			if(flag==0)
					t1=t1*10+2;
				else
					t2=t2*10+2;
				break;
			
			case 0xeb:
				lcd_string("1");
				delay(wait);
			if(flag==0)
					t1=t1*10+1;
				else
					t2=t2*10+1;
				break;
		}
		
		P1=0xf7;
		i=P1;
		switch(i)
		{
			case 0x77:
				lcd_string("+");
				delay(wait);
			j=4;
				flag =1;
				break;
			
			case 0xb7:
				lcd_string("=");
			 delay(wait);
			equal(j);
				break;
			
			case 0xd7:
				lcd_string("0");
				delay(wait);
				if(flag==0)
					t1=t1*10+0;
				else
					t2=t2*10+0;
				break;
			
			case 0xe7:
			cmd(0x01);
			flag=0;
		  j=0;
			t1=0;
			t2=0;
			break;
			
		
		}
		
	}
}

void lcd_int()
{
	cmd(0x38); //2 lines 5X7 lcd
	cmd(0xc0); //cursor on 2nd line 
	cmd(0x0e); //display on cursor blinking 
	cmd(0x01); //clear display
	cmd(0x80); //cursor to 1st line
}

void cmd(unsigned char c)
{
	data=c;
	rs=0;
	rw=0;
	en=1;
	delay(10);
	en=0;
	delay(10);
}

void dat(unsigned char d)
{
	data=d;
	rs=1;
	en=1;
	delay(10);
	en=0;
	delay(10);
}
	
void lcd_string(char *s)
{
while(*s)
{
dat(*s++);
}
}
void disp_num(int num)            //displays number on LCD
{
unsigned char UnitDigit  = 0;  //It will contain unit digit of numb
unsigned char TenthDigit = 0; 
	//It will contain 10th position digit of numb
unsigned char decimal = 0;
int h;
int numb;
h=(int)(num*10);
numb=num;
if(numb<0)
{
numb = -1*numb;  // Make number positive
lcd_string("-");	// Display a negative sign on LCD
}

TenthDigit = (numb/10);	         // Findout Tenth Digit
if( TenthDigit != 0)	         // If it is zero, then don't display
dat(TenthDigit+0x30);	 // Make Char of TenthDigit and then display it on LCD
else
	dat(0x30);
UnitDigit = numb - TenthDigit*10;
dat(UnitDigit+0x30);	 // Make Char of UnitDigit and then display it on LCD


delay(20);
}
	
void equal( int j1){
       switch (j1){
						case 1:
							disp_num(t1/t2);
						break;
						case 2:
							disp_num(t1*t2);
						break;
						case 3:
						disp_num(t1-t2);
						break;
						case 4:
						disp_num(t1+t2);
						break;
					}}
