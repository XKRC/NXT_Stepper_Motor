//#ifndef StepperBoth_h
//#define StepperBoth_h

  struct IRF510Stepper
  {
      byte I2Cport;
      int I2CAddr8574;
      int orange_bit;
      int yellow_bit;
      int pink_bit;
      int blue_bit;
      
      unsigned long delay_btw_steps;
      int steps_per_rev;
       
      byte WriteBuf[2];
      byte ReadBuf[]; 
      int RdCnt;
  };
  
  void StepperInit510(IRF510Stepper &t, byte I2Cport,int I2CAddr8574,int orange_bit, int yellow_bit, int pink_bit, int blue_bit, int steps_per_rev)
  {
    t.I2Cport = I2Cport;
    t.I2CAddr8574 = I2CAddr8574;
    t.orange_bit = orange_bit;
    t.yellow_bit = yellow_bit;
    t.pink_bit = pink_bit;
    t.blue_bit = blue_bit;
    t.steps_per_rev = steps_per_rev;
    t.RdCnt = 1;
    
    SetSensorLowspeed(I2Cport);
  
    t.WriteBuf[1] = 0x00;
    t.WriteBuf[0] = I2CAddr8574;
    I2CBytes(t.I2Cport,t.WriteBuf,t.RdCnt,t.ReadBuf);
  }


  void SetSpeed(IRF510Stepper &t, int rpm)
  {
    t.delay_btw_steps = 60 * 1000 / t.steps_per_rev / rpm;
    //this estimates how many ms one step should take based on rpm
  }
  
  
  
  void ChooseStep(IRF510Stepper &t, int stepNum)
  {
    switch(stepNum)
    {
    case 0:
      t.WriteBuf[1] = pow(2,t.orange_bit)+pow(2,t.yellow_bit);
      I2CBytes(t.I2Cport,t.WriteBuf,t.RdCnt,t.ReadBuf);
      break;
    case 1:
      t.WriteBuf[1] = pow(2,t.yellow_bit)+pow(2,t.pink_bit);
      I2CBytes(t.I2Cport,t.WriteBuf,t.RdCnt,t.ReadBuf);
      break;
    case 2:
      t.WriteBuf[1] = pow(2,t.pink_bit)+pow(2,t.blue_bit);
      I2CBytes(t.I2Cport,t.WriteBuf,t.RdCnt,t.ReadBuf);
      break;
    case 3:
      t.WriteBuf[1] = pow(2,t.blue_bit)+pow(2,t.orange_bit);
      I2CBytes(t.I2Cport,t.WriteBuf,t.RdCnt,t.ReadBuf);
      break;
    }
  }
  
  
  void MoveSteps(IRF510Stepper &t, int stepsToMove)
  {
   int steps_left = abs(stepsToMove);
   long prevTick;
  
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

//#endif