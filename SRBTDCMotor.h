#ifndef SRBTDCMOTOR_H
#define SRBTDCMOTOR_H
#include <srbtmachine.h>
#include <SRBTMotor.h>


class SRBTDCMotor : public SRBTMotor
{
    public:
        /** Default constructor */
        SRBTDCMotor();
        SRBTDCMotor(int p1,int p2,int s1, int s2);
        /** Default destructor */
        virtual ~SRBTDCMotor();
        virtual void UpdatePos();//{SRBTMachine::instance()->PrintSR("DC");}

        virtual void Run(int pos);
        virtual void RunToPos(int pos);
        virtual void RunToSensor(int pos);
        virtual void Stop();
        virtual int getCurrentPos(){return this->currentPos;};
        virtual int getToPosition(){return this->toPosition;};

        //virtual void Run();
        //virtual void RunToPos
    protected:
    private:
        void motorRun();
        bool checkSensor();

        int _pin1;
        int _pin2;
        int _sen1;
        int _sen2;
        bool isRunning;
        int toPosition;
        int currentPos;
        RunDirection direction;



};

#endif // SRBTDCMOTOR_H
