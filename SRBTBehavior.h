/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */

#ifndef SRBTBEHAVIOR_H
#define SRBTBEHAVIOR_H
#include <Arduino.h>
#include "SRBTMotor.h"
//#include "srbtmachine.h"
typedef enum {
    RUN=0, STOP, GOTOM, CLOSE, OPEN,RUNSENSOR,RUNPOS,SENSORCOUNT
} ActionsType;
typedef enum {
    SENSORVAL=0,SENSORH2L,SENSORL2H,SENSORBLINK, ONCOUNTERVAL,WHILESENSORNOT, ONRECEIVECMD, ONMODULESTART, ONMODULESTOP,SENSOROUT,SENSORIN
} EventType;



class ISRBTBhv
{
    public:
        /** Default constructor */

        /** Default destructor */
        virtual ~ISRBTBhv(){};
        virtual void Update(){};
        virtual void CheckCommand(String _cmd){};
    protected:
    private:
};
class SRBTBehavior:public ISRBTBhv
{
    public:
        /** Default constructor */
        SRBTBehavior();
        /** Default destructor */
        virtual ~SRBTBehavior();
        virtual void Update(){};
        void AddCommand(String _cmd,ActionsType _act,unsigned int _mid,SRBTMotor *mtr,int _param);
        virtual void CheckCommand(String _cmd);
    protected:
    private:
        unsigned int _commandCount;
        struct Command{
            String CommandRecived;
            ActionsType Action;
            unsigned int MotorID;
            SRBTMotor *motorA;
            int param;


        }*CommandList;


        struct Action {
            EventType EvType;
            ActionsType AcType;
            unsigned int param;
            String cmdReceived;
            //Command com;

            bool isRun;
            int var;
            int inc;

        } *ActionList;
        void Exec(Command *_cmd);


};

#endif // SRBTBEHAVIOR_H
