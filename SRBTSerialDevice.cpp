/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */
#include "SRBTSerialDevice.h"
#include <Arduino.h>
#define STX 35
#define ETX 42
#define LFX 10

SRBTSerialDevice::SRBTSerialDevice()
{
    //ctor
}

SRBTSerialDevice::~SRBTSerialDevice()
{
    //dtor
}
String SRBTSerialDevice::SerialRead(Stream* ser){
    bool startCMD=false;

    bool endCMD=false;

    this->srCommand="";

        while(ser->available()>0){

            char t= ser->read();

                    switch(t)
                    {
                        case STX:
                            startCMD = true;
                            break;

                        case ETX:
                            endCMD = true;
                            break;

                        case LFX:
                            break;

                        default:
                            if ((startCMD)&&(!endCMD)){
                                this->srCommand += t;
                            }
                            break;

                    }
         }
        delay(10);
         if((endCMD)&&(this->srCommand!=""))
            {
            return this->srCommand;
            }
         else
            {
             return "";
            }

}
String SRBTSerialDevice::BTRead(SoftwareSerial* ser){
    bool startCMD=false;

    bool endCMD=false;

    this->btCommand="";
    volatile char tk='d';
        while(ser->available()>0){

             tk= ser->read();
                    switch(tk)
                    {
                        case STX:
                            startCMD = true;
                            break;

                        case ETX:
                            endCMD = true;
                            break;

                        case LFX:
                            break;

                        default:
                            if ((startCMD)&&(!endCMD)){
                                this->btCommand += tk;
                            }
                            break;

                    }
                           Serial.print(tk);

                    delay(5);
         }
  //delay(10);
         if((endCMD)&&(this->btCommand!=""))
            {
            return this->btCommand;
            }
         else
            {
             return "";
            }

//         return ((endCMD)&&(this->srCommand!="")) ? this->srCommand : "";

        //if (this->srCommand!=""){
          //      return this->srCommand;
        //}
    //return "";
}
