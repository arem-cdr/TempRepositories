#include "SerialCom.h"


SerialCom::SerialCom()
{
        btn = new DigitalIn(USER_BUTTON);
        m_serial = new Serial(USBTX, USBRX);
        m_serial->attach(callback(this, &SerialCom::onCharReceived));
}

SerialCom::SerialCom(PinName tx, PinName rx)
{
        btn = new DigitalIn(USER_BUTTON);
        m_serial = new Serial(tx, rx);
        m_serial->attach(callback(this, &SerialCom::onCharReceived));
}


SerialCom::~SerialCom(){
        delete btn;
        delete m_serial;
    }

bool SerialCom::buttonIsPressed()
{
    if (*btn == 0){
        sendData<int>(45, INT);
        //Convert_Data_Into_Char(false, BOOL);
        //Convert_Data_Into_Char(7812, INT);
        //Convert_Data_Into_Char(-32.1f, FLOAT);
        //Convert_Data_Into_Char(45631.312548, DOUBLE);
        //m_serial->printf("%lf\n", 45631.312548);
        //Convert_Data_Into_Char(7812, INT);

        //Convert_Data_Into_Value<double>(buffer_test, DOUBLE);
        return true;
    }
    else
        return false;        
}

template <typename T> void SerialCom::sendData(T data, typeData TYPE)
{
    Convert_Data_Into_Char(data, TYPE);
    for (int i = 0; i<10; i++)
    {
        m_serial->putc(m_buffer_s[i]);
    }
}

void SerialCom::onCharReceived()
{
    uint8_t  charReceived = m_serial->getc(); // on récupère un caractère
    if (!reading){
        switch (charReceived)
        {
            case 100 : 
            {
                reading = true;
                type = BOOL;
                cmax = 1;
            }
            break;
            case 101 : 
            {
                reading = true;
                type = INT;
                cmax = 4;

            }
            break;
            case 102 : 
            {
                reading = true;
                type = FLOAT;
                cmax  = 4;
            }
            break;
            case 103 : 
            {
                reading = true;
                type = DOUBLE;
                cmax = 4;
            }
            break;

        }
    }
    else
    {
        if (c == cmax && charReceived == 10)
        {
            reading = false;
            switch (type)
            {
                case 0 : 
                {
                    Convert_Data_Into_Value<bool>(m_buffer_r, type);
                }
                break;
                case 1 : 
                {
                    Convert_Data_Into_Value<int>(m_buffer_r, type);
                }
                break;
                case 2 : 
                {
                    Convert_Data_Into_Value<float>(m_buffer_r, type);
                }
                break;
                case 3 : 
                {
                    Convert_Data_Into_Value<double>(m_buffer_r, type);
                }
                break;
            }
            type = -1;
            cmax = 0;
            c = 0;
        }
        if (reading){
            m_buffer_r[c] = charReceived;
            c++;
        }
    }
}

template <typename T> void SerialCom::Convert_Data_Into_Char(T data, int TYPE )
  {
    T* x = new T; 
    *x = data;
    switch(TYPE) 
    {
    case BOOL :
    {
        cleanBuffer(m_buffer_s);
        uint8_t mB = *((uint8_t*)x);
        m_buffer_s[1] = mB & 0xFF;
        m_buffer_s[0] = 100;
        m_buffer_s[2] = 10;
    }
    break;

    case INT :
    {
        cleanBuffer(m_buffer_s);
        uint32_t mI = *((uint32_t*)x);
        m_buffer_s[4] = mI & 0xFF;
        m_buffer_s[3] = (mI >> 8) & 0xFF;
        m_buffer_s[2] = (mI >> 16) & 0xFF;
        m_buffer_s[1] = (mI >> 24) & 0xFF;
        m_buffer_s[0] = 101;
        m_buffer_s[5] = 10;
    }
    break;

    case FLOAT : 
    {
        cleanBuffer(m_buffer_s);
        uint32_t mF = *((uint32_t*)x);
        //printf("mF : %ld\n", mF);
        m_buffer_s[4] = mF & 0xFF;
        m_buffer_s[3] = (mF >> 8) & 0xFF;
        m_buffer_s[2] = (mF >> 16) & 0xFF;
        m_buffer_s[1] = (mF >> 24) & 0xFF;
        m_buffer_s[0] = 102;
        m_buffer_s[5] = 10; 
    }
    break ;

    case DOUBLE :
    {
        cleanBuffer(m_buffer_s);
        uint64_t mD = *((uint64_t*)x);
        //printf("mD : %lld\n", mD);
        m_buffer_s[8] = mD & 0xFF;
        m_buffer_s[7] = (mD >> 8) & 0xFF;
        m_buffer_s[6] = (mD >> 16) & 0xFF;
        m_buffer_s[5] = (mD >> 24) & 0xFF;
        m_buffer_s[4] = (mD >> 32) & 0xFF;
        m_buffer_s[3] = (mD >> 40) & 0xFF;
        m_buffer_s[2] = (mD >> 48) & 0xFF;
        m_buffer_s[1] = (mD >> 56) & 0xFF;
        m_buffer_s[0] = 103;
        m_buffer_s[9] = 10;
    }
    break;
      
    }
     
   
    for (int i = 0; i < 10; i++){
        //m_serial->printf("%d || ",m_buffer_s[i]);
    }
    //m_serial->printf("\n");
   delete x;

  }


template <typename T> T SerialCom::Convert_Data_Into_Value(char buffer[8], int type)
{
    T data = 0;
    switch (type)
    {
    case BOOL:
    {
        if (buffer[0]==0)
            data = false;
        if (buffer[0]==1)
            data = true;
        printf("data : %d", data);
    }
    break;
    case INT:
    {
        uint32_t value = 0x00000000;
        for (uint8_t i = 0; i < 4; i++){ 
            value = value | ((uint32_t) buffer[3-i]) << (8*i);
        }
        m_serial->printf("value : %ld\n", value);
        uint32_t* p_Value = new uint32_t;
        *p_Value = value;
        data = *((T*)p_Value);
        delete p_Value;
        printf("data : %d", data);
    }
    break;
    case FLOAT:
    {
        uint32_t value = 0x00000000;
        for (uint8_t i = 0; i < 4; i++){ 
            value = value | ((uint32_t) buffer[3-i]) << (8*i);
        }
        //m_serial->printf("value : %ld\n", value);
        uint32_t* p_Value = new uint32_t;
        *p_Value = value;
        data = *((T*)p_Value);
        delete p_Value;
        printf("data : %f", data);
    }
    break;
    case DOUBLE:
    {
        uint64_t value = 0x0000000000000000;
        for (uint8_t i = 0; i < 8; i++){ 
            value = value | ((uint64_t) buffer[7-i]) << (8*i);
        }
        //m_serial->printf("value : %lld\n", value);
        uint64_t* p_Value = new uint64_t;
        *p_Value = value;
        data = *((T*)p_Value);
        delete p_Value;
        printf("data : %lf", data);
    }
    break;
    
    default:
        break;
    }
    return data;
}