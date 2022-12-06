#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions
#include <uart.h>

//joyStick button
#define BUTTON PB2
#define BUTTONenc PB3
//encoder pins
#define A  4 
#define B  5        

//static global variable
static int8_t joyX = 0;
static int8_t joyY = 0;


//encoder pins
#define A  4 
#define B  5

//static global variable
static uint8_t joyX = 0;
static uint8_t joyY = 0;


int main(void)
{
  // Initialize display
  lcd_init(LCD_DISP_ON);
  uart_init(UART_BAUD_SELECT(9600, F_CPU));

  //Setting GPIO pins
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
    TIM0_overflow_16ms();
    TIM0_overflow_interrupt_enable();
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
<<<<<<< HEAD
  
=======
  Encoder();
>>>>>>> aeab7299ca8768d0c97361e7170f9d638a1e1d25
  //lcd_clrscr();
  
     
}
<<<<<<< HEAD
ISR(TIMER0_OVF_vect){
  Encoder();
}
=======
>>>>>>> aeab7299ca8768d0c97361e7170f9d638a1e1d25




ISR(ADC_vect)
{
<<<<<<< HEAD

    static uint8_t state = 0;
=======
    lcd_gotoxy(0, 0); 
    lcd_puts("value:");
    lcd_gotoxy(0, 1); 
    lcd_puts("key:");
    
>>>>>>> aeab7299ca8768d0c97361e7170f9d638a1e1d25
    char string[4];
    static float valueX;
    static float valueY;
    static int16_t tec = 0;
    
    if (tec == 0)
    {
      valueX = ADC;
      tec = 1;
    }else{
      valueY = ADC;
      tec = 0;
    }
<<<<<<< HEAD
    
   /* itoa(valueX,string, 10);
=======
    /*
    itoa(valueX,string, 10);
>>>>>>> aeab7299ca8768d0c97361e7170f9d638a1e1d25
    lcd_gotoxy(6, 0);
    lcd_puts(string);

    itoa(valueY,string, 10);
    lcd_gotoxy(6, 1);
    lcd_puts(string);*/

<<<<<<< HEAD
    if(!GPIO_read(&PINB, BUTTON)){
      lcd_clrscr();
    }
    //down
    if (valueY > 800)
    {
      joyY=1;
    }
    //up
    if (valueY < 200)
    {
      joyY=0;
    }
    if (valueX >200 && valueX < 800)
    {
      state = 1;
    }
    

    //right
    if (valueX > 800 && state)
    {
      joyX++;
      state = 0;
    }
    //left
    if (valueX < 200 && state)
    {
      joyX--;
      state = 0;
 
    }
    if(joyX > 15){
      joyX = 0;
    }
    if(joyX < 0){
      joyX = 15;
    }
      
=======
    if(GPIO_read(&PINB, BUTTON)){
      //pressed
      //lcd_gotoxy(11, 1);
      //lcd_puts("+");

      lcd_gotoxy(joyX,joyY);
      lcd_puts(" ");

    }else{
      //don´t press
      //lcd_gotoxy(11, 1);
      //lcd_puts("-");
    }
>>>>>>> aeab7299ca8768d0c97361e7170f9d638a1e1d25


}

//method for encoder
void Encoder(){
  static uint8_t A_curr, B_curr, A_prev;
<<<<<<< HEAD
=======
  static uint8_t prom = 0;
>>>>>>> aeab7299ca8768d0c97361e7170f9d638a1e1d25
  static int8_t counter = 0;
  static char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  A_curr = GPIO_read(&PINB, A); 
  B_curr = GPIO_read(&PINB, B);
 
  if(A_curr != A_prev && A_curr  == 1)
  {
    //turning left
<<<<<<< HEAD
    if (B_curr == A_curr)
    {
      counter--;
=======
    if (B_curr ==A_curr)
    {
    prom = 1;
  
    }
    //turning right
    else{
       
        prom = 2;
     
>>>>>>> aeab7299ca8768d0c97361e7170f9d638a1e1d25
    }
    //turning right
    else{
        counter++;
    }  
  }
  A_prev = A_curr;
<<<<<<< HEAD
  if (counter < 0)
  {
    counter = 25;
  }
  if (counter > 25)
  {
    counter == 0;
  } 
  lcd_gotoxy(joyX,joyY);
  lcd_putc(alphabet[counter]);
  
=======
  if (prom == 1)
  {
    //lcd_gotoxy(10, 0); 
    //lcd_puts("CCW");
    uart_puts("CCW");
    uart_puts("\r\n\n");
    counter--;

  }
  if (prom == 2)
  {
    //lcd_gotoxy(10, 0);
    //lcd_puts("CW ");
    uart_puts("CW ");
    uart_puts("\r\n\n");
    counter++;
  }
  if (counter <= -1)
  {
    counter = 25;
  }
  if (counter >= 26)
  {
    counter == 0;
  }

  lcd_gotoxy(joyX,joyY);
  lcd_puts(alphabet[counter]);
>>>>>>> aeab7299ca8768d0c97361e7170f9d638a1e1d25

}