#ifndef SRBTMODULE_H
#define SRBTMODULE_H
//#include "srb
#include "SRBTBehavior.h"
#include "SRBTBehaviorSensor.h"
#include "SRBTMotor.h"
class ISRBTMod
{
    public:
        virtual ~ISRBTMod(){};
        virtual void UpdateModule(){};
        virtual void Start(){};
        virtual void Stop(){};
        virtual void CheckCommand(String _cmd){};

    protected:
    private:
};
class SRBTModule:public ISRBTMod
{
    public:
        /** Default constructor */
        SRBTModule();
        /** Default destructor */
        virtual ~SRBTModule();
        virtual void UpdateModule();
        virtual void CheckCommand(String _cmd);
        void AddMotor(SRBTMotor *_motor);
        void AddBehavior(SRBTBehavior *_behavior);
        void AddCommandBHV(SRBTBehavior *_behavior);
        void AddSensorBHV(SRBTBehaviorSensor *_behavior);
        virtual void Start();
        virtual void Stop(){this->Active=false;};
        unsigned int moduleID;
        volatile bool isRunning;
        SRBTMotor *GetMotor(int idx){return this->listMotors[idx];}
    protected:
    private:
        SRBTMotor   **listMotors;
        SRBTBehavior **listBehavior;
        SRBTBehavior **listCommands;
        SRBTBehaviorSensor **listSensorsBHV;
        unsigned int _motorCount;
        unsigned int _behaviorCount;
        unsigned int _commandCount;
        unsigned int _sensorBHVCount;
        bool Active;
};

#endif // SRBTMODULE_H
