#pragma once

/*
 * Ports list
 * Arduino Mega
 * Pin  Name/flags    Gemini use
 * Analog
 * 0    ADC0
 * 1    ADC1
 * 2    ADC2
 * 3    ADC3
 * 4    ADC4
 * 5    ADC5
 * 6    ADC6
 * 7    ADC7
 * 8    ADC8/PK0        General Gemini Data Bus D0, Or use AD0-AD7-A15,WR,ALE?
 * 9    ADC9/PK1        General Gemini Data Bus D1
 * 10   ADC10/PK2       General Gemini Data Bus D2
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
 
struct PORTS{
  int p17;  // yaw ladder
  int p07;  // pitch ladder
  int p27;  // roll ladder
};

struct PORTS ports;

