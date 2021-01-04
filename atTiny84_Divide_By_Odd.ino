/*
                            atTiny84 Divide By Odd
                            Vernon Billingsley 2021

                            Divide the Clock in on interrupt Pin 5
                            by the odd divisions...

                             Pin 13 /1
                             Pin 12 /3
                             Pin 11 /5
                             Pin 10 /7
                             Pin 9  /9
                             Pin 8  /11
                             Pin 7  /13
                             Pin 6  /15 
  
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission
    notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE. 
 */
/************************* Defines ********************************/

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

/************************** Variables *****************************/
volatile uint8_t divide_by_3 = 0;
volatile boolean db3 = false;
volatile uint8_t divide_by_5 = 0;
volatile boolean db5 = false;
volatile uint8_t divide_by_7 = 0;
volatile boolean db7 = false;
volatile uint8_t divide_by_9 = 0;
volatile boolean db9 = false;
volatile uint8_t divide_by_11 = 0;
volatile boolean db11 = false;
volatile uint8_t divide_by_13 = 0;
volatile boolean db13 = false;
volatile uint8_t divide_by_15 = 0;
volatile boolean db15 = false;

/**************************  Functions ****************************/


/******************************************************************/
/*************************** Setup ********************************/
/******************************************************************/
void setup() {

  /************************* Setup Pins ***************************/
  /*Pin 5 as Input  */
  DDRB &= ~_BV (2);
  /*PA0 to PA7, pin 13 to 6 as Output */
  DDRA |= _BV (0);
  DDRA |= _BV (1);
  DDRA |= _BV (2);
  DDRA |= _BV (3);
  DDRA |= _BV (4);
  DDRA |= _BV (5);
  DDRA |= _BV (6);
  DDRA |= _BV (7);


  /************************* Setup Interrupt *********************/
  /*Interrupt on change */
  cbi(MCUCR, ISC01);
  sbi(MCUCR, ISC00);
  sbi(GIMSK, INT0);
  sei();

}/**************************  End Setup **************************/

ISR(INT0_vect) {
  /*Read the state of PB2 */
  uint8_t pin_state = (PINB & _BV (2));
  /*If the pin is HIGH */
  if (pin_state) {
    /*Set PA0, divide by 1 HIGH */
    PORTA |= _BV (0);

    if (divide_by_3 < 2 && !db3) {
      PORTA |= _BV (1);
      divide_by_3 ++;
    }
    if (divide_by_5 < 3 && !db5) {
      PORTA |= _BV (2);
      divide_by_5 ++;
    }
    if (divide_by_7 < 4 && !db7) {
      PORTA |= _BV (3);
      divide_by_7 ++;
    }
    if (divide_by_9 < 5 && !db9) {
      PORTA |= _BV (4);
      divide_by_9 ++;
    }
    if (divide_by_11 < 6 && !db11) {
      PORTA |= _BV (5);
      divide_by_11 ++;
    }
    if (divide_by_13 < 7 && !db13) {
      PORTA |= _BV (6);
      divide_by_13 ++;
    }
    if (divide_by_15 < 8 && !db15) {
      PORTA |= _BV (7);
      divide_by_15 ++;
    }

  } else {
    /*Set PA0, divide by 1 LOW */
    PORTA &= ~_BV (0);
  }
  /*********************************************/
  if (divide_by_3 == 2 && !db3) {
    divide_by_3 = 0;
    db3 = true;
  }
  if (divide_by_5 == 3 && !db5) {
    divide_by_5 = 0;
    db5 = true;
  }
  if (divide_by_7 == 4 && !db7) {
    divide_by_7 = 0;
    db7 = true;
  }
  if (divide_by_9 == 5 && !db9) {
    divide_by_9 = 0;
    db9 = true;
  }
  if (divide_by_11 == 6 && !db11) {
    divide_by_11 = 0;
    db11 = true;
  }
  if (divide_by_13 == 7 && !db13) {
    divide_by_13 = 0;
    db13 = true;
  }
  if (divide_by_15 == 8 && !db15) {
    divide_by_15 = 0;
    db15 = true;
  }
  /*************************************************/
  if (!pin_state) {
    if (divide_by_3 < 2 && db3) {
      PORTA &= ~_BV (1);
      divide_by_3 ++;
    }
    if (divide_by_5 < 3 && db5) {
      PORTA &= ~_BV (2);
      divide_by_5 ++;
    }
    if (divide_by_7 < 4 && db7) {
      PORTA &= ~_BV (3);
      divide_by_7 ++;
    }
    if (divide_by_9 < 5 && db9) {
      PORTA &= ~_BV (4);
      divide_by_9 ++;
    }
    if (divide_by_11 < 6 && db11) {
      PORTA &= ~_BV (5);
      divide_by_11 ++;
    }
    if (divide_by_13 < 7 && db13) {
      PORTA &= ~_BV (6);
      divide_by_13 ++;
    }
    if (divide_by_15 < 8 && db15) {
      PORTA &= ~_BV (7);
      divide_by_15 ++;
    }
  }
  /*************************************************/
  if (divide_by_3 == 2 && db3) {
    divide_by_3 = 0;
    db3 = false;
  }
  if (divide_by_5 == 3 && db5) {
    divide_by_5 = 0;
    db5 = false;
  }
  if (divide_by_7 == 4 && db7) {
    divide_by_7 = 0;
    db7 = false;
  }
  if (divide_by_9 == 5 && db9) {
    divide_by_9 = 0;
    db9 = false;
  }
  if (divide_by_11 == 6 && db11) {
    divide_by_11 = 0;
    db11 = false;
  }
  if (divide_by_13 == 7 && db13) {
    divide_by_13 = 0;
    db13 = false;
  }
  if (divide_by_15 == 8 && db15) {
    divide_by_15 = 0;
    db15 = false;
  }
}/***********************end isr  *********************/

/******************************************************************/
/**************************** Loop ********************************/
/******************************************************************/
void loop() {
  // put your main code here, to run repeatedly:

}/*************************** End Loop *****************************/
