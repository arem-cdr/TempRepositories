#include "mbed.h"
#include <SerialCom.h>







int main()
{
  SerialCom S1(USBTX, USBRX);
  SerialCom S2(A0,A1);
  
  while(1)
  {
    S2.buttonIsPressed();
    S2.Traitement_DataReceived();
  }
  
 
}