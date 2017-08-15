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
  }
  
  
void StepperRunIRF510(Stepper &t, int stepsToMove)
{
  long prevTick;
  int steps_left = abs(stepsToMove);
  //int steps_left = abs(steps_to_move);  // how many steps to take
  
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
  
  if (stepsToMove > 0)    //CCW
   {  
    prevTick = CurrentTick();
    while (steps_left > 0)
    {
      switch(abs(steps_left % 4 - 3))
      {
      case 0:
        WriteBuf[1] = pow(2,t.orange_bit)+pow(2,t.yellow_bit);
        break;
      case 1:
        WriteBuf[1] = pow(2,t.yellow_bit)+pow(2,t.pink_bit);
        break;
      case 2:
        WriteBuf[1] = pow(2,t.pink_bit)+pow(2,t.blue_bit);
        break;
      case 3:
        WriteBuf[1] = pow(2,t.blue_bit)+pow(2,t.orange_bit);
        break;
    } //end switch
      I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
      steps_left--;
      while(CurrentTick()-prevTick < t.delay_btw_steps);
      prevTick = CurrentTick();
    } //end while
   } //end if  
   
   
   if (stepsToMove < 0)    //CW
   {  
    prevTick = CurrentTick();
    while (steps_left > 0)
    {
      switch(steps_left % 4)
      {
      case 0:
        WriteBuf[1] = pow(2,t.orange_bit)+pow(2,t.yellow_bit);
        break;
      case 1:
        WriteBuf[1] = pow(2,t.yellow_bit)+pow(2,t.pink_bit);
        break;
      case 2:
        WriteBuf[1] = pow(2,t.pink_bit)+pow(2,t.blue_bit);
        break;
      case 3:
        WriteBuf[1] = pow(2,t.blue_bit)+pow(2,t.orange_bit);
        break;
    } //end switch
      I2CBytes(t.I2Cport, WriteBuf, RdCnt, ReadBuf);
      steps_left--;
      while(CurrentTick()-prevTick < t.delay_btw_steps);
      prevTick = CurrentTick();
    } //end while
   } //end if     
} //end void









  
/*****   
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
