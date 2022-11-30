#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions
#include <uart.h>
#define BUTTON PB2
//encoder pins

 #define A  4 
 #define B  5

int main(void)
{
  // Initialize display
  lcd_init(LCD_DISP_ON);
  uart_init(UART_BAUD_SELECT(9600, F_CPU));
  GPIO_mode_input_pullup(&DDRB, BUTTON);
  GPIO_mode_input_nopullup(&DDRB, A);
  GPIO_mode_input_nopullup(&DDRB, B);


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

    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Set prescaler to 33 ms and enable overflow interrupt
    TIM1_overflow_33ms();
    TIM1_overflow_interrupt_enable();



    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

ISR(TIMER1_OVF_vect)
{ 
  static int8_t tec = 0;
   
  if(tec == 0)
  {  	ADMUX &= ~(1<<MUX0);
      ADMUX &= ~(1<<MUX1);
      ADMUX &= ~(1<<MUX2);
      ADMUX &= ~(1<<MUX3);
      // Start ADC conversion
      ADCSRA |= (1<<ADSC);
      tec = 1;
      }
  else{ADMUX |=  (1<<MUX0);
    ADMUX &= ~(1<<MUX1);
    ADMUX &= ~(1<<MUX2);
    ADMUX &= ~(1<<MUX3);
        // Start ADC conversion
    ADCSRA |= (1<<ADSC);
    tec = 0;
  }
  Encoder();   
  }




ISR(ADC_vect)
{
    lcd_gotoxy(0, 0); 
    lcd_puts("value:");
    lcd_gotoxy(0, 1); 
    lcd_puts("key:");

    char string[4];
    static float value;
    static float value2;
    static int16_t tec = 0;
    
    if (tec == 0)
    {
      value = ADC;
      tec = 1;
    }else{
      value2 = ADC;
      tec = 0;
    }
    
    itoa(value,string, 10);
    lcd_gotoxy(6, 0);
    lcd_puts(string);

    
    itoa(value2,string, 10);
    lcd_gotoxy(6, 1);
    lcd_puts(string);
    if(GPIO_read(&PINB, BUTTON)){
      lcd_gotoxy(11, 1);
      lcd_puts("+");
    }else{
      lcd_gotoxy(11, 1);
      lcd_puts("-");
    }
}
void Encoder(){
  static uint8_t A_curr, B_curr, A_prev, B_prev; 
  A_curr = GPIO_read(&PINB, A); 
  B_curr = GPIO_read(&PINB, B);
 
  if(A_curr != A_prev && A_curr  == 1)
  {
    if (B_curr ==A_curr)
    {
    lcd_gotoxy(10, 0); 
    lcd_puts("CCW");
    uart_puts("CCW");
    uart_puts("\r\n\n");
  
    }else{
       lcd_gotoxy(10, 0);
        lcd_puts("CW ");
        uart_puts("CW ");
        uart_puts("\r\n\n");
     
    }
   
  }
  A_prev = A_curr;

}