//#ifndef StepperBoth_h
//#define StepperBoth_h

  struct Stepper
  {
      byte I2Cport;
      int I2CAddr8574;
      int orange_bit;
      int yellow_bit;
      int pink_bit;
      int blue_bit;
      
      unsigned long delay_btw_steps;
      int steps_per_rev;
      
      //byte WriteBuf0, WriteBuf1;
      //byte WriteBuf[2];
      //byte ReadBuf[]; 
      //int RdCnt;
  };
  
  
    void SetSpeed(Stepper &t, int rpm)
  {
    t.delay_btw_steps = 60 * 1000 / t.steps_per_rev / rpm;
    //this estimates how many ms one step should take based on rpm
  }
  
   
  void StepperInit(Stepper &t, byte I2Cport,int I2CAddr8574,int orange_bit, int yellow_bit, int pink_bit, int blue_bit, int steps_per_rev)
  {
    t.I2Cport = I2Cport;
    t.I2CAddr8574 = I2CAddr8574;
    t.orange_bit = orange_bit;
    t.yellow_bit = yellow_bit;
    t.pink_bit = pink_bit;
    t.blue_bit = blue_bit;
    t.steps_per_rev = steps_per_rev;
    //t.RdCnt = 1;
  }

void StepperRunIRF510(Stepper &t, int steps_to_move)
{
  long prevTick;
  
  int steps_left = abs(steps_to_move);  // how many steps to take
  
  int step_P1 = pow(2,t.orange_bit)+pow(2,t.yellow_bit);
  int step_P2 = pow(2,t.yellow_bit)+pow(2,t.pink_bit);
  int step_P3 = pow(2,t.pink_bit)+pow(2,t.blue_bit);
  int step_P4 = pow(2,t.blue_bit)+pow(2,t.orange_bit);
  
   // array variables (since NXC's I2C functions take array variables
  byte WriteBuf[2]; // data written to PCF8574A.  Declares a two one-byte variables
  byte ReadBuf[]; // data received from PCF8574A.  We won't be reading any data but we need this for I2CBytes
  int RdCnt = 1; // number of bytes to read
  
  SetSensorLowspeed (t.I2Cport); // PCF8574A connect to NXT
  
  // First, set address with first I2CWrite.  Recall, WriteBuf[1] has address 0xF0 0x00
  WriteBuf[1] = 0x00; // i.e. write zeros to port sets up PCF8574A for writing
  WriteBuf[0] = t.I2CAddr8574; // i.e. address is 0x70
  I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
  
  
  if (steps_to_move > 0) {   //CCW
    for (int i=0; i < steps_left; i++) { 
     
    prevTick = CurrentTick();
    WriteBuf[1] = step_P1; 
    I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
    while(CurrentTick()-prevTick < t.delay_btw_steps);
    
    prevTick = CurrentTick();
    WriteBuf[1] = step_P2;
    I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
    while(CurrentTick()-prevTick < t.delay_btw_steps);
    
    prevTick = CurrentTick();
    WriteBuf[1] = step_P3; 
    I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
    while(CurrentTick()-prevTick < t.delay_btw_steps);
    
    prevTick = CurrentTick();
    WriteBuf[1] = step_P4; 
    I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
    while(CurrentTick()-prevTick < t.delay_btw_steps);
    
    } //end for loop 
  } //end if
  
  if (steps_to_move < 0) {  //CW
    for (int i=0; i < steps_left; i++) {  
    
    prevTick = CurrentTick();
    WriteBuf[1] = step_P4; 
    I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
    while(CurrentTick()-prevTick < t.delay_btw_steps);
  
    prevTick = CurrentTick();
    WriteBuf[1] = step_P3;
    I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
    while(CurrentTick()-prevTick < t.delay_btw_steps);
    
    prevTick = CurrentTick();
    WriteBuf[1] = step_P2; 
    I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
    while(CurrentTick()-prevTick < t.delay_btw_steps);
    
    prevTick = CurrentTick();
    WriteBuf[1] = step_P1; 
    I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
    while(CurrentTick()-prevTick < t.delay_btw_steps);
    
    } //end for loop 
  } //end if
}








/***** 
  void ChooseStep(Stepper &t, int stepNum)
  {
    switch(stepNum)
    {
    case 0:
      t.WriteBuf1 = pow(2,t.orange_bit)+pow(2,t.yellow_bit);
      t.WriteBuf[1] = t.WriteBuf1;
      I2CBytes(t.I2Cport,t.WriteBuf,t.RdCnt,t.ReadBuf);
      break;
    case 1:
      t.WriteBuf1 = pow(2,t.yellow_bit)+pow(2,t.pink_bit);
      t.WriteBuf[1] = t.WriteBuf1;
      I2CBytes(t.I2Cport,t.WriteBuf,t.RdCnt,t.ReadBuf);
      break;
    case 2:
      t.WriteBuf1 = pow(2,t.pink_bit)+pow(2,t.blue_bit);
      t.WriteBuf[1] = t.WriteBuf1;
      I2CBytes(t.I2Cport,t.WriteBuf,t.RdCnt,t.ReadBuf);
      break;
    case 3:
      t.WriteBuf1 = pow(2,t.blue_bit)+pow(2,t.orange_bit);
      t.WriteBuf[1] = t.WriteBuf1;
      I2CBytes(t.I2Cport,t.WriteBuf,t.RdCnt,t.ReadBuf);
      break;
    }
  }
  
  
  void MoveSteps(Stepper &t, int stepsToMove)
  {
   int steps_left = abs(stepsToMove);
   long prevTick;
  
    SetSensorLowspeed(t.I2Cport);
  
    t.WriteBuf1 = 0x00;
    t.WriteBuf0 = t.I2CAddr8574;
    t.WriteBuf[1] = t.WriteBuf1;
    t.WriteBuf[0] = t.WriteBuf0;
    I2CBytes(t.I2Cport,t.WriteBuf,t.RdCnt,t.ReadBuf);
    
    
   if (stepsToMove > 0)
   {  //CCW
    prevTick = CurrentTick();
    while (steps_left > 0)
    {
      ChooseStep(t,abs(steps_left % 4 - 3));
      steps_left--;
      while(CurrentTick()-prevTick < t.delay_btw_steps);
      prevTick = CurrentTick();
    }
   } //end if
  
  
   if (stepsToMove < 0)
   { //CW
    prevTick = CurrentTick();
    while(steps_left > 0)
    {
      ChooseStep(t,steps_left % 4);
      steps_left--;
      while(CurrentTick()-prevTick < t.delay_btw_steps);
      prevTick = CurrentTick();
    }
   } //end if
  } //end void function
*****/



//#endif
