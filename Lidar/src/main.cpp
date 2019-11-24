#include <mbed.h>
#include <iostream>
#include "BufferedSerial.h"
#include "rplidar.h"

RPLidar lidar;
BufferedSerial se_lidar(A0,A1);
Serial PC(USBTX, USBRX);

struct MapLidar{
  float distance;
  float angle;
};



MapLidar map;

void get_rplidar()
{
    if (IS_OK(lidar.waitPoint())) 
    {
        map.distance = lidar.getCurrentPoint().distance;
        map.angle = lidar.getCurrentPoint().angle;
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