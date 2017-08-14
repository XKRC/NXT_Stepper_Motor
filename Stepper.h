void StepperIRF510(byte I2Cport,int I2CAddr8574,int orange_bit, int yellow_bit,
                                 int pink_bit, int blue_bit,int steps_to_move,unsigned long WAIT_MS)
{
  int steps_left = abs(steps_to_move);  // how many steps to take
  
  int step_P1 = pow(2,orange_bit)+pow(2,yellow_bit);
  int step_P2 = pow(2,yellow_bit)+pow(2,pink_bit);
  int step_P3 = pow(2,pink_bit)+pow(2,blue_bit);
  int step_P4 = pow(2,blue_bit)+pow(2,orange_bit);
  
   // array variables (since NXC's I2C functions take array variables
  byte WriteBuf[2]; // data written to PCF8574A.  Declares a two one-byte variables
  byte ReadBuf[]; // data received from PCF8574A.  We won't be reading any data but we need this for I2CBytes
  int RdCnt = 1; // number of bytes to read
  
  SetSensorLowspeed (I2Cport); // PCF8574A connect to NXT
  
  // First, set address with first I2CWrite.  Recall, WriteBuf[1] has address 0xF0 0x00
  WriteBuf[1] = 0x00; // i.e. write zeros to port sets up PCF8574A for writing
  WriteBuf[0] = I2CAddr8574; // i.e. address is 0x70
  I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
  
  
  if (steps_to_move > 0) {   //CCW
    for (int i=0; i < steps_left; i++) {  
    WriteBuf[1] = step_P1; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);
  
  
    WriteBuf[1] = step_P2;
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);

    WriteBuf[1] = step_P3; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);

    WriteBuf[1] = step_P4; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);
    Wait(100);
    } //end for loop 
  } //end if
  

  if (steps_to_move < 0) {  //CW
    for (int i=0; i < steps_left; i++) {  
    WriteBuf[1] = step_P4; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);
  
  
    WriteBuf[1] = step_P3;
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);

    WriteBuf[1] = step_P2; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);

    WriteBuf[1] = step_P1; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);
    Wait(100);
    } //end for loop 
  } //end if
}

void StepperULN2003A(byte I2Cport,int I2CAddr8574,int orange_bit, int yellow_bit,
                                 int pink_bit, int blue_bit,int steps_to_move,unsigned long WAIT_MS)
{
  int steps_left = abs(steps_to_move);  // how many steps to take
  
  int step_P1 = pow(2,orange_bit)+pow(2,yellow_bit);
  int step_P2 = pow(2,yellow_bit)+pow(2,pink_bit);
  int step_P3 = pow(2,pink_bit)+pow(2,blue_bit);
  int step_P4 = pow(2,blue_bit)+pow(2,orange_bit);
  
   // array variables (since NXC's I2C functions take array variables
  byte WriteBuf[2]; // data written to PCF8574A.  Declares a two one-byte variables
  byte ReadBuf[]; // data received from PCF8574A.  We won't be reading any data but we need this for I2CBytes
  int RdCnt = 1; // number of bytes to read
  
  SetSensorLowspeed (I2Cport); // PCF8574A connect to NXT
  
  // First, set address with first I2CWrite.  Recall, WriteBuf[1] has address 0xF0 0x00
  WriteBuf[1] = 0x00; // i.e. write zeros to port sets up PCF8574A for writing
  WriteBuf[0] = I2CAddr8574; // i.e. address is 0x70
  I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
  
  
  if (steps_to_move > 0) {   //CCW
    for (int i=0; i < steps_left; i++) {  
    WriteBuf[1] = 255-step_P1; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);
  
  
    WriteBuf[1] = 255-step_P2;
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);

    WriteBuf[1] = 255-step_P3; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);

    WriteBuf[1] = 255-step_P4; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);
    } //end for loop 
  } //end if
  

  if (steps_to_move < 0) {  //CW
    for (int i=0; i < steps_left; i++) {  
    WriteBuf[1] = 255-step_P4; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);
  
  
    WriteBuf[1] = 255-step_P3;
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);

    WriteBuf[1] = 255-step_P2; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);

    WriteBuf[1] = 255-step_P1; 
    I2CBytes(S1, WriteBuf, RdCnt, ReadBuf);
    Wait(WAIT_MS);
    } //end for loop 
  } //end if
}
