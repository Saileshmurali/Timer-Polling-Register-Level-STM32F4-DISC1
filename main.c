#include "stm32f4xx.h"
void Tim_Config(void);
void GPIO_Config(void);
void Delay_ms(uint16_t time);

int main (void)
{
	Tim_Config ();
	GPIO_Config ();
		
	while (1)
	{
		GPIOD->ODR ^= (0xFUL<<12);
		Delay_ms (1000);
	}
	
}
void Delay_ms (uint16_t time)
{
	TIM2->ARR=time-1;
	TIM2->EGR=1;
	TIM2->SR &=~1;
	TIM2->CR1 |=1;
	while((TIM2->SR&0x0001)!=1);
}
void GPIO_Config (void)
{

	RCC->AHB1ENR |=(1UL<<3); //Enable GPIOD clock
	GPIOD->MODER &= ~(0xFFUL<<12*2);// Reset the bits
	GPIOD->MODER |= (0x55UL<<12*2);//Configure pins PD12-PD15 as output
}

void Tim_Config (void)
{
// Enable Timer clock
	RCC->APB1ENR |= (1<<0);  // Enable the timer 2 clock
	
// Set the prescalar and the ARR
	TIM2->PSC = 16000-1;  // 16MHz/16000= 1ms delay
	TIM2->ARR = 0xffff;  // MAX ARR value

}
