/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */
#include "SRBTSensor.h"

SRBTSensor::SRBTSensor()
{
    //ctor
}
SRBTSensor::SRBTSensor(SensorType _sType,unsigned int _pin)
{
    this->nPin=_pin;
    pinMode(this->nPin,INPUT);
    this->_sensorType=_sType;
    this->_counter=0;

}

SRBTSensor::~SRBTSensor()
{
    //dtor
}
void SRBTSensor::readSensor()
{
    int _val;
    if (this->_sensorType==ANALOG)
        {
            _val=analogRead(this->nPin);
        }
    else
        {
            _val=digitalRead(this->nPin);
        }

  this->value=_val;

}


