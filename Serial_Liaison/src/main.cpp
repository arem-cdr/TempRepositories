#include "mbed.h"
#include "SerialCom.h"
#include "define.h"







int main()
{
  //SerialCommunication serial;
  SerialCom S1(USBTX, USBRX);
  SerialCom S2(D1,D0);
  
  while(1)
  {
    S2.buttonIsPressed();
    wait(0.2);
  }
  
 
}