#pragma once

#include "define.h"
#include "mbed.h"
#include "mathFunction.h"
#include "math.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>



class SerialCommunication {
public:
    SerialCommunication(){
        btn = new DigitalIn(USER_BUTTON);
        led = new DigitalOut(LED1);
        pc = new Serial(USBTX, USBRX);
        pc->attach(callback(this, &SerialCommunication::onCharReceived));
        initAsciiTable();
    }
    ~SerialCommunication(){
        delete btn;
        delete led;
        delete pc;
    }

    void showReceived() const {
        pc->printf("bool : %d, int : %d, float : %f, double : %lf\n ", boolReceived, intReceived, floatReceived, doubleReceived );
    }
    bool buttonIsPressed() {
        if (*btn == 0){
            //int S = 6548782;
            //sendData(S, INT);
            //pc->printf("%d\n", S);
            return true;
        }
        else
            return false;

        
    }
    bool getBoolReceived() const{return boolReceived;}
    int getIntReceived() const {return intReceived;}
    float getFloatReceived() const {return floatReceived;}
    double getDoubleReceived() const {return doubleReceived;}

    /*void doubleIntoChar(double x)
{
    std::stringstream ss;
    ss << x;
    ss >> charTab;
    for (int i = 0; i<100; i++){
        pc->printf("%d : %c || ", charTab[i], charTab[i]);
    }
    pc->printf("\n");
    for (int i = 0; i<100; i++){
        pc->putc(charTab[i]);
    }
}*/

  
  
  
  int castDouble(){
    double * x = (double*)malloc(sizeof(double));
    *x = -5.12345;
    pc->printf("%f\n", *x);
    *((uint64_t*)x) &= 0x7FFFFFFFFFFFFFFF;
    pc->printf("%f\n", *x);
    return 0;
}


private :
    DigitalIn       *btn;
    DigitalOut      *led;
    Serial          *pc;

    enum{
        UNKNOWN = 0,
        BOOL,
        INT,
        FLOAT,
        DOUBLE,
    };
  
    bool boolReceived = false;
    int intReceived = 0;
    float floatReceived = 0.0f;
    double doubleReceived = 0.0;

    bool boolToSend =false;
    int intToSend = 0;
    float floatToSend = 0.0f;
    double doubleToSend = 0.0;

    int  startBuffer[4] = {48,48,48,-1};
    int validStart[TAILLE_CODE_START] = {99,100,114}; // cdr
    char   dataBuffer[TAILLE_MAX_BUFFER] = "\0"; // Initialized to the NULL character
    uint8_t index_dataBuff = 0;
    uint8_t index_startBuff = 0;
    bool reading = false;
    int bufferType = UNKNOWN;
    char bufferToSend[TAILLE_MAX_BUFFER] = "\0";
    char charTab[8] = {0};


    void cleanBuffer(char buffer[TAILLE_MAX_BUFFER])
    {
        for (int i = 0; i<TAILLE_MAX_BUFFER;i++){
            buffer[i] = '\0';
        }
    }

    void convertBufferToRead(char dataBuffer[TAILLE_MAX_BUFFER], int bufferType)
{
  switch (bufferType)
  {
    case UNKNOWN : 
    break;

    case BOOL :
    if (checkValue09(dataBuffer[0]) == 1 && checkValue09(dataBuffer[1]) == 0){
        if (checkValue09(dataBuffer[2]) == 0)
          boolReceived = false;
        if (checkValue09(dataBuffer[2]) == 1)
          boolReceived = true;
    }
    pc->printf("boolReceived : %d\n", boolReceived);
    break;
    
    case INT :
    intReceived = 0;
    if (checkValue09(dataBuffer[1]) == 0){
      for (int i = 0;i < checkValue09(dataBuffer[0]);i++){
        intReceived += checkValue09(dataBuffer[2+i])*pow(10,checkValue09(dataBuffer[0])-1-i);
      }
    }
    pc->printf("intReceived %d\n", intReceived);
    break;
    
    case FLOAT :
    floatReceived = 0.0f;
    for (int i = 0;i < checkValue09(dataBuffer[0]) + checkValue09(dataBuffer[1]); i++){
        floatReceived += checkValue09(dataBuffer[2+i])*pow(10,checkValue09(dataBuffer[0]) + checkValue09(dataBuffer[1]) - 1 - i); 
      }
    floatReceived /= pow(10.0f, checkValue09(dataBuffer[1]));
    
    pc->printf("floatReceived : %f\n", floatReceived); 
    
    break;
    
    case DOUBLE :
    doubleReceived = 0.0f;
    for (int i = 0;i < checkValue09(dataBuffer[0]) + checkValue09(dataBuffer[1]); i++){
        doubleReceived += checkValue09(dataBuffer[2+i])*pow(10,checkValue09(dataBuffer[0]) + checkValue09(dataBuffer[1]) - 1 - i); 
      }
    doubleReceived /= pow(10.0f, checkValue09(dataBuffer[1]));
    
    pc->printf("doubleReceived : %lf\n", doubleReceived);

    break;
    
  }


}

    template <typename T> int convertBufferToSend(T value, bool valueIsBool = false)
{
    cleanBuffer(bufferToSend);
    uint8_t c_pE = 0;
    uint8_t c_pF = 0;
    double tmpValue = (double) value;
    double partieEntiere_d;
    double partieFractionnaire_d;
    partieFractionnaire_d = modf(tmpValue, &partieEntiere_d);
    double partieFractionnaire = (float) partieFractionnaire_d;
    //pc->printf("%f\n", partieFractionnaire);
    int partieEntiere = (int) partieEntiere_d;
    int temptabFrac[100];
    int temptabEnti[100];
    if (valueIsBool)
    {
        bufferToSend[0] = convert09ToAscii(1);
        bufferToSend[1] = convert09ToAscii(0);
        if(value)
            bufferToSend[2] = convert09ToAscii(1);
        else
            bufferToSend[2] = convert09ToAscii(0);
        c_pE = 1;
    }
    else{
        while((temptabEnti[c_pE] = (int) (partieEntiere / pow(10, c_pE))) != 0)
        {
            //pc->printf("%d\n", ((int) (partieEntiere / pow(10, c_pE)))%10);
            c_pE++;
        }
        for (int i = 0; i< c_pE-1;i++){
          temptabEnti[i] -= temptabEnti[i+1]*10;
        }
        {
        double tmppE;
        while((temptabFrac[c_pF] = (int) (10*modf(partieFractionnaire*pow(10, c_pF), &tmppE))) != 0)
        {
            //pc->printf("%d\n", (int) (10*modf(partieFractionnaire*pow(10, c_pF), &tmppE)));
            
            c_pF++;
        }
        }
    }
    //pc->printf("c_pE : %d, c_pF : %d\n", c_pE, c_pF);
    bufferToSend[0] = convert09ToAscii(c_pE);
    bufferToSend[1] = convert09ToAscii(c_pF);
    if (!valueIsBool){
      for (int i = 0; i<c_pE;i++){
          bufferToSend[2+i] = convert09ToAscii(temptabEnti[c_pE - 1 - i]);
          //pc->printf("Entier %c : %d,id : %d %d\n", bufferToSend[2+i],bufferToSend[2+i],2+i, temptabEnti[i]);

      }
      for (int i = 0; i< c_pF;i++){
          bufferToSend[2+c_pE+i] = convert09ToAscii(temptabFrac[i]);
          //pc->printf("Fraction %c : %d,id : %d %d\n", bufferToSend[2+c_pE+i],bufferToSend[2+c_pE+i],2+c_pE+i, temptabFrac[i]);
      }
    }
    return c_pE + c_pF;
}

  template <typename T> void sendData(T value,int valueType, bool valueIsBool = false)
{
    //pc->printf("Start message ");
    for (int i = 0; i< TAILLE_CODE_START;i++){
    pc->putc(convertCharToAscii(validStart[i]));
    }
    //pc->printf(" Type ");
    pc->putc(convert09ToAscii(valueType));
    //pc->printf(" Buffer ");
    int nbCharToSend = convertBufferToSend(value,valueIsBool);
    //pc->printf(" nbCharToSend %d ", nbCharToSend);
    for (int i = 0; i< nbCharToSend + 2 ;i++){
        pc->putc(bufferToSend[i]);
    }
    pc->putc('\n');
}


    void onCharReceived()
{
    uint8_t  charReceived = pc->getc(); // on récupère un caractère
    //pc->printf("%d : %c: %d, reading status : %d\n",index_dataBuff, charReceived, charReceived, reading);
    if (!reading){ // Si on cherche le top départ
      if (index_startBuff < TAILLE_CODE_START ) // code de départ 123
        if(charReceived == validStart[index_startBuff])
          index_startBuff++;
        else{
          index_startBuff = 0;
        }
      else{
        if (charReceived > 48 && charReceived < 48 + DOUBLE + 1){ // type de donnée à lire
          reading = true;
          bufferType = charReceived - 48;
          //pc->printf("type : %d\n", bufferType);
        }
        index_startBuff = 0;
      }
    }
    else {
      if (charReceived == 0)
      {
        convertBufferToRead(dataBuffer, bufferType);
        reading = false;
        index_dataBuff=0;
        bufferType = UNKNOWN;
        for(int i = 0; i<TAILLE_MAX_BUFFER; i++ )
        {
          dataBuffer[i] = '\0';
        }
      }
      if (charReceived == 10)
      {
        convertBufferToRead(dataBuffer, bufferType);
        reading = false;
        index_dataBuff=0;
        bufferType = UNKNOWN;
        for(int i = 0; i<TAILLE_MAX_BUFFER; i++ )
        {
          dataBuffer[i] = '\0';
        }
      }
      dataBuffer[index_dataBuff] = charReceived; 
      //pc.printf("index_buff : %d, %d, %c\n",index_dataBuff, dataBuffer[index_dataBuff], dataBuffer[TAILLE_MAX_BUFFER-1]);
      //pc.printf("buff : %s\n", dataBuffer); //affiche dataBuffer
      *led=!*led;
      if (reading)
        index_dataBuff++;
    }
}
    


};






