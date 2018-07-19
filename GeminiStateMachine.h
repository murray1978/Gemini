/*
 * The flow diagrams for Matghflow 7 are a state machine.
 * Trying to keep the flow as close as possible to the diagrams.
 * =============================================================
 * Program reports several messages via serial
 * Gemini FC: functions, methods, dataflow from MathFlow 7
 * Gemini DB: debug messages
 * Gemini DA: data messages
 * Gemini ER: error messages
 * Gemini WR: warning messages
 * Gemini INF: info messages
*/
#pragma once
#include "common.h"
#include "MDIU.h"

void dcsSUB()
{
  Serial.println("Gemini FC: dcsSUB()");
}

void dasSUB()
{
  Serial.println("Gemini FC: dasSUB()");
}

void ioa(){
  Serial.println("Gemini FC: ioa()");
}

void io(){
  Serial.println("Gemini FC: io()");
}

//94.4
void iosub(){
  Serial.println("Gemini FC: iosub()");
  if( logicControl.LC17 == false )
  {
    return;
  }
  logicControl.LC17 = false;

  if( logicControl.LC30 == true || logicControl.LC4E == true )
  {
    //set:HOPc = L(94.5)
    dcsSUB();
  }

  //set:HOPc = L(94.6)
  dasSUB();

  //Yaw ladder buffer
  outPortb( dout.DO03, 0); // Cp165,  Delta b0 range, 
  outPortb( dout.DO44, 0); //- SET LADDER BUFFER
  values.acc = inPortb (dout.DO44) + KP367; //Delta Yaw @ n
  //write(acc)(17), yaw to output
  
  values.acc = KP361; //delay
  while( values.acc-- != 0 );

  outPortb( dout.DO44, 1); //Reset ladder bufferS
  outPortb( dout.DO02, values.CP164); //Delta Pitch
  
}

void gonogo(){
  Serial.println("Gemini FC: gonogo()");
}

void gclock(){
  Serial.println("Gemini FC: gclock()");
}

//29.1 gimbal angle
void gimbalAngle()
{
  Serial.println("Gemini FC: gimbalAngle()");
  //i2c read of gimbals
}

uchar_t age(){
  Serial.println("Gemini FC: age()"); 
  return true; 
}

void mdiuSub()
{
  Serial.println("Gemini FC: mdiuSub()");

  if( inPin(din.DI04) == true ){
    int x = 0;
  }
  //55.9
  int cd = 1; //Count of digits inserted
  logicControl.LC23 = true;
  logicControl.LC15 = true;
N5512:
   //insert Light off
  outPin( dout.DO40, true );
  // RESET insert,
  // Display Clear
  MDIU_Display.clear();
  // D1,2,4,4
  outPin( dout.DO41, true); //Turn off display
  logicControl.LC16 = true;  
}



//And the big flight logic
void geminiFlightLogic()
{
  Serial.println("Gemini FC: start up");
  //Page 23, COL 78
  logicControl.LC4A = true;    //StandBy initalize
  logicControl.LC4B = true;    //Ascent not Fast Loop
  logicControl.LC4C = true;
  logicControl.LC4D = true;
  logicControl.LC4E = true;
EXECIN:                        // 78.2
  Serial.println("Gemini FC: EXCIN");
  values.CP135 = values.CP136 = values.CP137 = 0;
  outPin( dout.DO62, true);           // Start Computaions off 
  outPin( dout.DO05, true);           // Computer running off, light off
  outPin( dout.DO64, true);           // Second Engine Cutoff off, light off
  outPin( dout.DO61, true);           // Gain Change off, light off?
EXECTR:                       // 78.3
  Serial.println();
  Serial.println("Gemini FC: EXECTR LOOP");
  delay(1000);
  if( logicControl.LC4B == true){ // Check for Ascent 
    io();  
  }else{
    ioa();   //ascent fast loop
  }
  
  gonogo();
  gclock();
  
  if( age() == false ) goto EXECTR;
  
  if( logicControl.LC4B == true){ //Check for Ascent
    io();  
  }
  else
  {
    ioa();  //ascent fast loop
  }
  
  if( inPin( din.DI11) == true ){    //78.5
    if( inPin( din.DI10) == true ){
      goto STANDBY;                   //93.1
    }
    else                              //78.7
    {
      if( inPin(din.DI13) == true ){
        goto ASCENT;                  //59.1
      }
      else
      {
        goto CATCHUP;                 //1.2
      }
    }
  }
  else                                //78.6
  {
    if( inPin(din.DI13) == true )
    {
        goto RENDEZVOUS;              //1.1
    }
    else
    {
        goto REENTRY;                  //35.1 
    }
  }

STANDBY:                                //93.1
  Serial.println("Gemini FC: STANDBY");
  //Standby startup
  if( logicControl.LC4A  == true )
  {
    Serial.println("Gemini FC: STANDBY Init");
    logicControl.LC4E = logicControl.LC4B = logicControl.LC4C = logicControl.LC4D = true;
    logicControl.LC4A = false;
    gimbal.dx = gimbal.dy = gimbal.dz = 0;
    pinOut(dout.DO05, true);
  }
  else
  {
    //Sanity Check of memory, maybe used while in orbit
  }
  iosub();
  gimbalAngle();
  goto EXECTR;
  
ASCENT:                                    //59.1
  Serial.print("Gemini FC: ASCENT");
  if( logicControl.LC4B == true )                 //First pass/initalise 
  {
    Serial.print(": Init");
    logicControl.LC4A = logicControl.LC4C = logicControl.LC4D = logicControl.LC4F = true;
    logicControl.LC18 = logicControl.LC20 = logicControl.LC21 = logicControl.LC24 = logicControl.LC29 = true;
    logicControl.LC4B = logicControl.LC17 = false;
  }
  goto EXECTR;
CATCHUP:
  Serial.println("Gemini FC: CATCHUP");
  goto EXECTR;
RENDEZVOUS:
  Serial.println("Gemini FC: RENDEZVOUS");
  goto EXECTR;
REENTRY:
  Serial.println("Gemini FC: REENTRY");
  goto EXECTR;
//Non Mathflow 7 
ORBIT_PROGRADE:   //change craft orientation to prograde
  Serial.println("Gemini FC: PROGRADE");
  goto EXECTR;
ORBIT_RETROGRADE: //change craft orientation to retrograde
  Serial.println("Gemini FC: RETROGRADE");
  goto EXECTR;
ORBIT_NORMAL:     //change craft orientation to orbit normal
  Serial.println("Gemini FC: ORBIT_NORMAL");
  goto EXECTR;
ORBIT_ANTINORMAL: //change craft orientation to orbit anti normal
  Serial.println("Gemini FC: ORBIT_ANTINORMAL");
  goto EXECTR;
STAR_ALIGN:       //Align Star tracker
  Serial.println("Gemini FC: STAR_ALIGN");
  goto EXECTR;
}
