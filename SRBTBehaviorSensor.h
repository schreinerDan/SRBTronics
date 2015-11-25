#ifndef SRBTBEHAVIORSENSOR_H
#define SRBTBEHAVIORSENSOR_H
#include <SRBTBehavior.h>
#include <SRBTMotor.h>
#include <SRBTSensor.h>

typedef enum {
    GOTOS=0, STOPS,RUNS,COUNTERS
} ActionsSensorType;

class SRBTBehaviorSensor:public ISRBTBhv
{
    public:
        /** Default constructor */
        SRBTBehaviorSensor();
        /** Default destructor */
        virtual ~SRBTBehaviorSensor();

        virtual void Update(){};

        void AddCommand(EventType _evt,ActionsSensorType _act,SRBTSensor *sen,int _vals,int _param);
        void AddCommand(EventType _evt,ActionsSensorType _act,SRBTSensor *sen,SRBTMotor *mot,int _vals,int _param);

       // void AddCommand(EventType _evt,ActionsSensorType _act,SRBTSensor *sen,SRBTMotor *mot,int _param){};

        //void AddCommand(EventType _evt,ActionsSensorType _act,SRBTSensor *sen,SRBTModule *mod,int _param){};

        virtual void CheckCommand(String _cmd){};

        bool checkSensor();
        protected:
    private:
        unsigned int _commandCount;
        void enableCommands();
        struct CommandSensor{
            bool isExecuted;

            String CommandRecivedS;

            EventType EventS;

            ActionsSensorType ActionS;

            SRBTSensor *sensorS;

            //SRBTModule *moduleS;

            SRBTMotor  *motorS;

            int *varCount;

            int valSensor;

            int paramS;


        }*CommandSenList;

        void Exec(CommandSensor *_cmd);

        int volatile sensorValue;

        int volatile lastState;


};

#endif // SRBTBEHAVIORSENSOR_H
