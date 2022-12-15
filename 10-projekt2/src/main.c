#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <stdlib.h>         // C library. Needed for number conversions
<<<<<<< HEAD
#include <uart.h>
=======
//#include <uart.h>

/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

>>>>>>> 1b1d299d25d39ed399dbd7785f93ebae682990eb

//encoder pins
#define ServoA  PD7  //PB1 -- D9
#define ServoB  2  //PB2 -- D10

#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

//static global variable
static int8_t servoX = 63;
static int8_t servoY = 63;
static uint8_t counter2 = 0;

int main(void) {
<<<<<<< HEAD
  uart_init(UART_BAUD_SELECT(9600, F_CPU));

  uart_puts("main");
  uart_puts("\r\n");
=======
  //uart_init(UART_BAUD_SELECT(9600, F_CPU));
  //uart_puts("Main\r\n");
>>>>>>> 1b1d299d25d39ed399dbd7785f93ebae682990eb
  //configure GPIO pins
  GPIO_mode_output(&DDRD, ServoA);
  GPIO_mode_output(&DDRB, ServoB);
  // Configure Analog-to-Digital Convertion unit
  // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
  /*ADMUX |= (1<<REFS0);
  ADMUX &= ~(1<<REFS1);
  // Select input channel ADC0 (voltage divider pin)
  
  // channel ADC1
  ADCSRA |= (1<<ADEN);
  // Enable conversion complete interrupt
  ADCSRA |= (1<<ADIE);
  // Set clock prescaler to 128
  ADCSRA |= (1<<ADPS0);
  ADCSRA |= (1<<ADPS1);
  ADCSRA |= (1<<ADPS2);*/

  // Configure 16-bit Timer/Counter0 to start ADC conversion
  // Set prescaler to 16 us and enable overflow interrupt
  TIM0_overflow_1024us();
  TIM0_overflow_interrupt_enable();
  // Enables interrupts by setting the global interrupt mask
  sei();

  // Infinite loop
  while (1)
  {
    if (counter2 == 1)
    {
    //uart_puts("whilee\r\n");
    static uint16_t max = 1250; 
    static uint8_t counter1 = 0;
    if(counter1 <= servoX )
    {
      GPIO_write_high(&PORTD, ServoA);
      counter1++;
      
    }
    else if(counter1 > servoX)
    {
      GPIO_write_low(&PORTD, ServoA);
      if(counter1 == max)
      {
        counter1 = 0;
        //uart_puts("counter1_0\r\n");
        servoX++;
      }   

    }
    counter2 = 0;
    }
    

    
  }

  // Will never reach this
  return 0;
}

<<<<<<< HEAD
ISR(TIMER1_OVF_vect)
{ 
  uart_puts("TIMER1");
      uart_puts("\r\n");
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
ISR(TIMER0_OVF_vect)
{ 
  uart_puts("TIMER0");
      uart_puts("\r\n");
  uint16_t max = 1250;
  uint16_t counter1 = 0;
  uint16_t counter2 = 0;
=======

ISR(TIMER0_OVF_vect)
{
//uart_puts("timer0\r\n"); 
counter2 = 1;
}
<<<<<<< HEAD
  
  /* if(counter2 <= servoY ){
=======
void PWM(){
  uint8_t max = 1250;
  uint8_t counter1 = 0;
  uint8_t counter2 = 0;
>>>>>>> 1b1d299d25d39ed399dbd7785f93ebae682990eb
  if(counter1 <= servoX ){
    GPIO_write_high(&DDRB, ServoA);
    counter1++;
    uart_puts("counter1++");
      uart_puts("\r\n");
  }else{
    GPIO_write_low(&DDRB, ServoA);
     if(counter1 == max){
        counter1 = 0;
        uart_puts("counter1_0");
      uart_puts("\r\n");
     }   

  }

   if(counter2 <= servoY ){
>>>>>>> 698ddd3ddf2b12abd20100f4cc23291ee43ebfaa
    GPIO_write_high(&DDRB, ServoB);
    counter2++;
<<<<<<< HEAD
    uart_puts("counter2++");
      uart_puts("\r\n");
=======
    uart_puts("counter2++\r\n");
>>>>>>> 1b1d299d25d39ed399dbd7785f93ebae682990eb
  }else{
    GPIO_write_low(&DDRB, ServoB);
     if(counter2 == max){
        counter2 = 0;
<<<<<<< HEAD
        uart_puts("counter2_0");
      uart_puts("\r\n");
=======
        uart_puts("counter2_0\r\n");
>>>>>>> 1b1d299d25d39ed399dbd7785f93ebae682990eb
     }   
  }*/

<<<<<<< HEAD

ISR(ADC_vect){
=======
/*ISR(ADC_vect){
>>>>>>> 1b1d299d25d39ed399dbd7785f93ebae682990eb
    static uint8_t stateX = 0;
    static uint8_t stateY = 0;
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
    //center on X
    if (valueX >200 && valueX < 800)
    {
      stateX = 1;
    }
    //center on Y
    if (valueY >200 && valueY < 800)
    {
      stateY = 1;
    }
    //down - set row to second
    if (valueY > 800 && stateY)
    {
      servoY--;
      stateY = 0;
      uart_puts("ServoY--");
      uart_puts("\r\n");
    }
    //up - set row to first
    if (valueY < 200 && stateY)
    {
      servoY++;
      stateY = 0;
      uart_puts("ServoY++");
      uart_puts("\r\n");
    }

    //move cursor to the right
    if (valueX > 800 && stateX)
    {
      servoX++;
      stateX = 0;
      uart_puts("ServoX++");
      uart_puts("\r\n");
    }
    //move cursor to the left
    if (valueX < 200 && stateX)
    {
      servoX--;
      stateX = 0;
      uart_puts("ServoX--");
      uart_puts("\r\n");
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
}*/