#pragma once

class LED_Display{
public:
      
      LED_Display(byte din, byte cs, byte clk )
      {
        MAX7219DIN = din;
        MAX7219CS  = cs;
        MAX7219CLK = clk;
        init();
        brightness(15);
      }
      
      ~LED_Display(){}
      
      void clear()
      {
        for( int i = 1; i < 9; i++)
          sendData(i, 0);  
      }

      void blank()
      {
        for( int i = 1; i < 9; i++)
        {
          sendData(i,15);
        }
      }

      void brightness( byte b)
      {
        sendData(10,b);
      }

      void showData(unsigned long data)
      {
          unsigned long k = data;
          bool blank = false;

          for( int i = 0; i < 9; i++ )
          {
              if(blank){
                sendData(i, 15);
              }
              else
              {
                sendData(i, k%10);
              }
              
              k /= 10;
              if( k == 0 ) blank = true;
          }
      }

      void setDigit( byte digit, byte val)
      {
        if( val < 0 || val > 9) return;
        if( digit < 1 || digit > 9) return; 
        sendData(digit, val);
      }
      
private:
  void init()
  {
    pinMode(MAX7219DIN, OUTPUT);
    pinMode(MAX7219CS, OUTPUT);
    pinMode(MAX7219CLK, OUTPUT);
    digitalWrite(MAX7219CS, HIGH);    // Deselect display
    digitalWrite(MAX7219CLK, LOW);    // Clock low
    sendData(15,0);                   // Test mode off 
    sendData(12,1);                   // Display On
    sendData(9,255);                  // Decode all digits
    sendData(11,7);                   // Scan all
    clear(); 
  }

  void sendData( byte r, byte d )
  {
    digitalWrite(MAX7219CS, LOW);       //Select display
    
    for( int i = 128; i > 0; i=i>>1)
    {
      if( i & r )
      {
        digitalWrite(MAX7219DIN, HIGH);
      }
      else
      {
        digitalWrite(MAX7219DIN, LOW);
      }

      digitalWrite(MAX7219CLK, HIGH);   //Toggle clock  
      digitalWrite(MAX7219CLK, LOW);
    }
    
    for( int i = 128; i > 0; i=i>>1)
    {
            if( i & d )
      {
        digitalWrite(MAX7219DIN, HIGH);
      }
      else
      {
        digitalWrite(MAX7219DIN, LOW);
      }

      digitalWrite(MAX7219CLK, HIGH);   //Toggle clock  
      digitalWrite(MAX7219CLK, LOW);
    }
    digitalWrite(MAX7219CS, HIGH );     //Deselct display
  }
  
  
  byte MAX7219DIN;
  byte MAX7219CS;
  byte MAX7219CLK;

};
