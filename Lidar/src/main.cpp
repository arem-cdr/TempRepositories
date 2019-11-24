#include <mbed.h>
#include<queue>
#include "BufferedSerial.h"
#include "rplidar.h"

RPLidar lidar;
BufferedSerial se_lidar(A0,A1);
Serial PC(USBTX, USBRX);

void get_rplidar()
{
     if (IS_OK(lidar.waitPoint())) 
     {
       PC.printf("%f, %f, %d, %d\n", lidar.getCurrentPoint().distance, lidar.getCurrentPoint().angle, lidar.getCurrentPoint().quality, lidar.getCurrentPoint().startBit);
    } 
    else
    {
  
       lidar.startScan();
  
    }
    
}


int main()
{
  PC.baud(115200);
  lidar.begin(se_lidar);
  lidar.setAngle(0,360);

  while(1)
  {
    get_rplidar();
  }
  return 0;
}