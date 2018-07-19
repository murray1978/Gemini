#pragma once

/*
 * Ports list, incomplete, missing PORTA, PORTB and PORTG
 * Arduino Mega
 * Pin  Name/flags    Gemini use                                                    TESTING
 * Analog
 * 0    ADC0
 * 1    ADC1
 * 2    ADC2
 * 3    ADC3
 * 4    ADC4
 * 5    ADC5
 * 6    ADC6
 * 7    ADC7
 * 8    ADC8/PK0        General Gemini Data Bus D0, Or use AD0-AD7-A15,WR,ALE?      DI0  
 * 9    ADC9/PK1        General Gemini Data Bus D1                                  DI1
 * 10   ADC10/PK2       General Gemini Data Bus D2                                  DI3  
 * 11   ADC11/PK3       General Gemini Data Bus D3
 * 12   ADC12/PK4       General Gemini Data Bus D4
 * 13   ADC13/PK5       General Gemini Data Bus D5  
 * 14   ADC14/PK6       General Gemini Data Bus D6
 * 15   ADC15/PK7       General Gemini Data Bus D7
 * Digital
 * 0    D0/RX0/GPIO     Arduino programming pin, do not use
 * 1    D1/TX0/GPIO     Arduino programming pin, do not use
 * 2    D2/PWM/GPIO     MDIU_Keys      //would like to use 4 bits, Move to PK
 * 3    D3/PWM/GPIO     MDIU_Keys
 * 4    D4/PWM/GPIO     MDIU_Keys
 * 5    D5/PWM/GPIO     MDIU_Keys
 * 6    D6/PWM/GPIO     MDIU_Keys
 * 7    D7/PWM/GPIO     MDIU_Keys
 * 8    D8/PWM/GPIO     MDIU_Keys
 * 9    D9/PWM/GPIO     MDIU_Display  //Move to PA or PB
 * 10   D10/PWM/GPIO    MDIU_Display
 * 11   D11/PWM/GPIO    MDIU_Display
 * 12   D12/PWM/GPIO
 * 13   D13/PWM/GPIO
 * Comunication
 * 14   D14/TX3/GPIO
 * 15   D15/RX3/GPIO
 * 16   D16/TX2/GPIO
 * 17   D17/RX2/GPIO
 * 18   D18/TX1/GPIO    //DSO up, Comms with Ground control
 * 19   D19/RX1/GPIO    //DSO dwn
 * 20   D20/GPIO/SDA    
 * 21   D21/GPIO/SCL
 */

 /*
  * Gemini computer had a PRO command for io.
  * The comand structure was
  * X(A1-A3)Y(A4-A6)A9, A9=0 then accumilator cleared, otherwise leave alone
  * In asembler it is PRO YX
  * commands
  *   X Y  i/o 
  *   0 0   in  DCS or Rendezvous radar       PRO 00
  *   0 1  out  Instrument System/Downlink    PRO 10
  *   0 2  i/o  Time Refrence System          PRO 20
  *   0 3  out  MDR digit magnitude           PRO 30\
  *   0 4  out  
  */
 
struct PORTS{
  int p17;  // yaw ladder
  int p07;  // pitch ladder
  int p27;  // roll ladder
};

struct DATAIN{                                        //Port Assignments
  int DI04:1;
  /*
   * Mode Control
   *  DI11 + DI10 = Standby = b0110
   *  DI11 + !DI10 + DI13 = Ascent = b0011
   *  DI11 + !DI10 + !DI13 = CatchUp = b0010
   *  !DI11 + DI13 = Rendezvous = b0001 
   *  !DI11 + !DI13 = ReEntry = b0100
  */
  int DI10:1;     // Mode Control         
  int DI11:1;     // Mode Control
  int DI13:1;     // Mode Control
  // Start computaions switch
  // Enter button
  // cancel button
  // reset button
  
};

//Data Out objects
struct DATAOUT{                                       // Port Assignments
  int DO02;   // Pitch resolution control? 
  int DO03;   // Yaw resolution control?
  int DO04;   // Roll resolution control?
  int DO40:1; // insert Light
  int DO41:1; // display off
  int DO44;   // Yaw ladder buffer
  int DO61;   // Gain Change
  int DO62:1; // start computations light
  int DO05:1; // Computer running ligh
  int DO64:1; // SECO light
  //malf light
};

struct DATAOUT dout;
/*
 * struct DATAOUT dout = {
 *    
 * };
*/

struct DATAIN  din;
struct PORTS ports;

/*
 * Write a byte to a port, 
 * PORTA + PORTC =  16 bit data
 * PORTA = 8 bit address, 255 devices    
 * PORTG = WR(PG0), RD(PG1), ALE(PG2) 
 */
void outPortb( byte portAddress, unsigned int data){
  GDRD = 0xff;    //Set PORTG to outputs
  ADRD = 0xff;    //Set PORTA to outputs
  BDRD = 0xFF;    //Set PORTB to outputs
  //Set PORTA = portAddress
  PORTA = portAddress;
  //Set PORTG ALE = 1
  PORTG = B00000100;
  delay(20)
  //Set PORTA + PORTB = data
  //Set PORTG ALE = 0
  PORTG = B00000000;
  //Set PORTG WR = 1
  PORTG = B00000001;
  delay(20)
  PORTG = 0x00;
  PORTA = 0x00;
  PORTB = 0x00;
}

/*
 * Read an unsigned from a port, 
 * PORTA + PORTC =  16 bit data
 * PORTA = 8 bit address, 255 devices    
 * PORTG = WR(PG0), RD(PG1), ALE(PG2) 
 */
byte inPortb( byte port ){
  GDRD = 0xff;    //Set PORTG to outputs
  ADRD = 0xFF;    //Set PORTA to inputs
  BDRD = 0x00;    //Set PORTB to outputs
  //Set PORTA = portAddress
  PORTA = portAddress;
  //Set PORTG ALE = 1
  PORTG = B00000100;
  delay(20)
  //Set PORTA + PORTB = data
  //Set PORTG ALE = 0
  PORTG = B00000000;
  //Set PORTG WR = 1
  PORTG = B00000001;
  delay(20)
  //PORTA has lower byte
  //PORTB has higher byte
  PORTG = 0x00;
  PORTA = 0x00;
  PORTB = 0x00;
}


//Read a pin state
bool inPin( byte pin){
  return false;
}
//write a pin state
void outPin( byte pin, bool state){}

