/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */
#ifndef SRBTSENSOR_H
#define SRBTSENSOR_H
#include <Arduino.h>
typedef enum{
    H2L=0,
    L2H,
    BLINK
}SensorAction;
typedef enum {
    ANALOG=0,
    DIGITAL=1
}SensorType;
class SRBTSensor
{
    public:
        /** De  fault constructor */
        SRBTSensor();
        SRBTSensor(SensorType _sType,unsigned int _pin);
        /** Default destructor */

        virtual int GetValue(){this->readSensor();return this->value;}

        virtual ~SRBTSensor();

        void Counter(int inc){this->_counter+=inc;};

        int getCounter(){return this->_counter;};

    protected:

    private:

        void readSensor();

        unsigned int nPin;

        int value;

        SensorType _sensorType;

        SensorAction _sensorAction;

        int _counter;
};

#endif // SRBTSENSOR_H
