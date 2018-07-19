/*
 * Common.h
 */
#pragma once
#include "ports.h"

#define KWNO  5.2593  // B4
#define KP220 175     // B10 sec
#define KVGO  750     // B15 ft/sec
#define KVAO  150     // B15 ft/sec
#define KIFO  250     // B10 ft/sec
#define KQO   1.66    // B4
#define KP12  100     // B17 sec
#define KP104 PI/2    // B3 ad
#define KXAO  0       // B25 ft
#define KZA0  0       // B25 ft
#define KYA0  -20909749  // B25 ft
#define KP226 0.5     // B1
#define KP336 0.93969 // B1
#define KTST2 156.1   // B17 sec 

#define KP361 7825
#define KP367 16

//LC = Logic Control
struct LOGIC_CONTROL{
  //LC = Logic Control
   bool LC15:1;    //MDIU
   bool LC16:1;    //MDIU - Display Status?
   bool LC18:1;
   bool LC20:1;
   bool LC21:1;
   bool LC23:1;    //MDIU
   bool LC24:1;
   bool LC29:1;
   bool LC17:1;
   bool LC4A:1;    //Standby Initalize
   bool LC4B:1;    //Ascent active
   bool LC4C:1;  
   bool LC4D:1;
   bool LC4E:1;
   bool LC4F:1;
   bool LC30:1;
};

struct GIMBAL{
  int x;
  int y;
  int z;
  int dx;
  int dy;
  int dz;
};

struct ACCELERATION
{
  int x;
  int y;
  int z;
  int dx;
  int dy;
  int dz;
};

struct VALUES
{
  //59, pg17
  long Wno;     //kinematic value, time step?
  int Vg;       //Velocity loss due to gravity
  int af;       //Final value of thrust acceleration
  int qno;      //?
  long thetaN;  //gimbal angle
  int zni;       
  int cp150;
  int tr;       //time to start roll program

  int acc;      //Accumilator

  int CP164;
  int CP165;    // Delta b0 range, yaw?
  int CP135;
  int CP136;
  int CP137;
};



struct LOGIC_CONTROL logicControl;
struct GIMBAL gimbal;
struct ACCELERATION accel;
struct VALUES values;

