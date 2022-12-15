/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions

//encoder pins
#define ServoA  PD7  //PD7 -- D7
#define ServoB  PB2  //PB2 -- D10

//definicion of global variables
static uint8_t servoX = 63;
static uint8_t servoY = 63;

int main(void)
{
    // Initialize USART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));
    
    //configure GPIO pins
    GPIO_mode_output(&DDRD, ServoA);
    GPIO_mode_output(&DDRB, ServoB);

    // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADMUX |= (1<<REFS0);
    ADMUX &= ~(1<<REFS1);
    // Select input channel ADC0 (voltage divider pin)
    
    // channel ADC1
    ADCSRA |= (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA |= (1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA |= (1<<ADPS0);
    ADCSRA |= (1<<ADPS1);
    ADCSRA |= (1<<ADPS2);

    // Configure 16-bit Timer/Counter0 to transmit UART data
    // Set prescaler to 16 us and enable overflow interrupt
    TIM0_overflow_16us();
    TIM0_overflow_interrupt_enable();
    // Configure 16-bit Timer/Counter1 to transmit UART data
    // Set prescaler to 33 ms and enable overflow interrupt
    TIM1_overflow_33ms();
    TIM1_overflow_interrupt_enable();


    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put strings to ringbuffer for transmitting via UART
    //uart_puts("Print one line... ");
    //uart_puts("done\r\n");

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

ISR(TIMER0_OVF_vect)
{
  //definicion of variables
  static uint16_t counterA = 0;
  static uint16_t counterB = 0;
  //operating of first servo motor (servoX)
  if (counterA <= servoX)
  {
    GPIO_write_high(&PORTD, ServoA);
    counterA++;
  }else{
    GPIO_write_low(&PORTD, ServoA);
    counterA++;
    if(counterA == 1250){
      counterA = 0;
    }
  }
  //operating of second servo motor (servoY)
  if (counterB <= servoY)
  {
    GPIO_write_high(&PORTB, ServoB);
    counterB++;
  }else{
    GPIO_write_low(&PORTB, ServoB);
    counterB++;
    if(counterB == 1250){
      counterB = 0;
    }
  }
}

ISR(TIMER1_OVF_vect)
{
  //definicion of variable
  static int8_t tec = 0;
  //changing X and Y of joystick
  if(tec == 0)
  { ADMUX &= ~(1<<MUX0);
    ADMUX &= ~(1<<MUX1);
    ADMUX &= ~(1<<MUX2);
    ADMUX &= ~(1<<MUX3);
    // Start ADC conversion
    ADCSRA |= (1<<ADSC);
    tec = 1;
  }else{
    ADMUX |=  (1<<MUX0);
    ADMUX &= ~(1<<MUX1);
    ADMUX &= ~(1<<MUX2);
    ADMUX &= ~(1<<MUX3);
    // Start ADC conversion
    ADCSRA |= (1<<ADSC);
    tec = 0;
  }
}

ISR(ADC_vect){
  //definicion of variables
  static float valueX;
  static float valueY;
  static int16_t tec = 0;
  //getting ADC from joystick
  if (tec == 0)
  {
    valueX = ADC;
    tec = 1;
  }else{
    valueY = ADC;
    tec = 0;
  }
  //down - set row to second
  if (valueY > 800)
  {
    servoY--;
  }
  //up - set row to first
  if (valueY < 200)
  {
    servoY++;
  }
  //move cursor to the right
  if (valueX > 800)
  {
    servoX++;
  }
  //move cursor to the left
  if (valueX < 200)
  {
    servoX--;
  }
  //get cursor on the start of the display
  if(servoX > 125){
    servoX = 125;
  }
  //get cursor on the end of the display
  if(servoX < 63){
    servoX = 63;
  }    
  //get cursor on the start of the display
  if(servoY > 125){
    servoY = 125;
  }
  //get cursor on the end of the display
  if(servoY < 63){
    servoY = 63;
  }   
}