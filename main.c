#include <stdint.h>


uint32_t *pAHB1ENR     = (uint32_t*)0x40023830;
uint32_t *pAPB2ENR     = (uint32_t*)0x40023844;
uint32_t *pGPIOB_MODER  = (uint32_t*)0x40020400;
uint32_t *pGPIOA_MODER  = (uint32_t*)0x40020000;
uint32_t *pGPIOB_ODR    = (uint32_t*)0x40020414;
uint32_t *pGPIOA_ODR    = (uint32_t*)0x40020014;
uint32_t *pGPIOB_BSRR   = (uint32_t*)0x40020418;
uint32_t *pGPIOA_BSRR   = (uint32_t*)0x40020018;



#define RS 0x20 //0010 0000
#define RW 0x40 //0100 0000
#define EN 0x80  //1000 0000

unsigned char msg1[]=("      YASH");
unsigned char msg2[]=("     JADHAV");
void GPIO_Init(void);
void LCD_Command(unsigned char command);
void LCD_Data(unsigned char data);
void LCD_Init(void);
void delayMs(int delay);


int main(void)
{
	LCD_Init();
	while(1)
	{
       //infinite loop
	}

}



void GPIO_Init(void)
{
	*pAHB1ENR  |= 0X03; // enable clock access for GPIOA and GPIOB
	*pGPIOB_MODER |=0X5400; //selecting PB5,PB6,PB7 as output
	*pGPIOA_MODER |=0X00005555; // selecting PA0-PA7 as output
	*pGPIOB_BSRR = ((RS | RW | EN) << 16);  //RESET ALL TO ZERO

}

void LCD_Command(unsigned char command)
{
	// RS=0  RW=0
	*pGPIOB_BSRR =(RS|RW)<<16;
	*pGPIOA_ODR =command;
	*pGPIOB_BSRR =EN ; //ENABLE EN
	delayMs(2);
	*pGPIOB_BSRR =EN<<16 ; //clear EN


}

void LCD_Data(unsigned char data)
{
	//RS=1 ,RW=0
	*pGPIOB_BSRR =RS;
	*pGPIOB_BSRR =RW<<16;
	*pGPIOA_ODR =data;
	*pGPIOB_BSRR =EN ; //ENABLE EN
	delayMs(30);
	*pGPIOB_BSRR =EN<<16 ; //clear EN
	delayMs(30);
}

void LCD_Init(void)
{
	unsigned char i=0;

	GPIO_Init();
	LCD_Command(0x38); // Function set: 8-bit, 2 line, 5x8 dots
	delayMs(20);
	LCD_Command(0x0c); // Display ON, Cursor OFF, Blink OFF
	delayMs(20);
	LCD_Command(0x06);  // Entry mode set: Increment cursor, no display shift
	delayMs(20);
	LCD_Command(0x01);  //clear screen move cursor home
	delayMs(20);
	delayMs(5000);

	LCD_Command(0x80); //cursor to line 1
	delayMs(20);
	while (msg1[i]!='\0')
		{
			LCD_Data(msg1[i]);
			i++;
		}
	delayMs(20);
	LCD_Command(0xC0); //cursor to line 2
	i=0;
	for(;msg2[i]!='\0';i++) //sending each character and loading their ASCII code individually
	{
		LCD_Data(msg2[i]);
	}
	delayMs(20);

}

void delayMs(int delay)  //delay function
{
	int i;
	for (;delay>0;delay--)
	{
		for(i=0;i<3195;i++)
		{

		}
	}
}
