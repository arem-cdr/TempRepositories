#pragma once

#include "mbed.h"
#include "define.h"
#include <iostream>


class SerialCom
{
public :

    SerialCom();
    SerialCom(PinName rx, PinName tx);
    ~SerialCom();
    bool buttonIsPressed();


private :
    DigitalIn       *btn;
    Serial          *m_serial;

    

    char m_buffer_r[8] = {0};
    int type = -1;
    bool reading = false;
    uint8_t c = 0;
    uint8_t cmax = 0;
    char buffer_test[8] = {64,230,71,234,0,100,169,206};

    char m_buffer_s[10] = {0};
    template <typename T> void sendData(T data, typeData TYPE);

    void onCharReceived();
    template <typename T> void Convert_Data_Into_Char(T data, int TYPE );

    template <typename T> T Convert_Data_Into_Value(char buffer[8], int type);
  
    void cleanBuffer(char buffer[10]){ for(int i = 0; i<10;i++){ buffer[i] = '\0';}}

};