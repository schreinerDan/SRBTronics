/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */

#ifndef SRBTBEHAVIORSENMACHINE_H
#define SRBTBEHAVIORSENMACHINE_H
#include <SRBTBehavior.h>
#include <SRBTMotor.h>
#include <SRBTSensor.h>
#include <SRBTModule.h>

typedef enum {
    GOTOSM=0, STOPSM,RUNSM,COUNTERSM
} ActionsSenMachineType;


class SRBTBehaviorSenMachine:public ISRBTBhv
{
    public:
        /** Default constructor */
        SRBTBehaviorSenMachine();
        /** Default destructor */
        virtual ~SRBTBehaviorSenMachine();
        virtual void Update(){checkSensor();};
        void AddCommand(EventType _evt,ActionsSenMachineType _act,SRBTSensor *sen,int _vals,int _param);
        void AddCommand(EventType _evt,ActionsSenMachineType _act,SRBTSensor *sen,SRBTMotor *mot,int _vals,int _param);
        void AddCommand(EventType _evt,ActionsSenMachineType _act,SRBTSensor *sen,SRBTModule *mod,int _vals,int _param);

        bool checkSensor();

        virtual void CheckCommand(String _cmd){};
    protected:
    private:
         unsigned int _commandCount;

        struct CommandSensorMachine{

            String CommandRecivedSM;

            EventType EventSM;

            ActionsSenMachineType ActionSM;

            SRBTSensor *sensorSM;

            SRBTModule *moduleSM;

            SRBTMotor  *motorSM;

            int *varCountSM;

            int valSensorSM;

            int paramSM;


        }*CommandSenMachineList;

        void Exec(CommandSensorMachine *_cmd);

        int volatile sensorValue;

        int volatile lastState;

};

#endif // SRBTBEHAVIORSENMACHINE_H
