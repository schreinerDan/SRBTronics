#ifndef SRBTMOTOR_H
#define SRBTMOTOR_H
//#include "srbtmachine.h"
#include <Arduino.h>

typedef enum RunDirection{
    LEFT=0,
    RIGHT=1

};

typedef enum RunType{
    LOOPING=0,
    POSITION=1,
    SENSORFC=3

};
class SRBTMotor
{
    public:
        /** Default constructor */
        SRBTMotor();
        /** Parameter constructor */
        SRBTMotor(int p1,int p2,int s1, int s2);

        /** Default destructor */
        virtual ~SRBTMotor();
        virtual void UpdatePos();//{SRBTMachine::instance()->PrintSR("teste");}
        virtual void Run(int pos){};
        virtual void RunToPos(int pos){};
        virtual void RunToSensor(int pos){};
        int getPin1(){return this->_pin1;};
        int getPin2(){return this->_pin2;};
        int getSen1(){return this->_sen1;};
        int getSen2(){return this->_sen2;};
        virtual int getCurrentPos(){return this->currentPos;};
        virtual int getToPosition(){return this->toPosition;};


        RunType runType;
        virtual void Stop(){};
        void SetupMotor(int p1,int p2,int s1, int s2);
    protected:
    private:
        RunDirection direction;
        int _pin1;
        int _pin2;
        int _sen1;
        int _sen2;
        bool isRunning;
        int toPosition;
        int currentPos;


};

#endif // SRBTMOTOR_H
