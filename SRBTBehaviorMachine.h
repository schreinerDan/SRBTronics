#ifndef SRBTBEHAVIORMACHINE_H
#define SRBTBEHAVIORMACHINE_H

#include <SRBTBehavior.h>
#include <SRBTModule.h>

typedef enum {
    GOTO=0, END, START
} ActionsMachineType;

class SRBTBehaviorMachine : public ISRBTBhv
{
    public:
        /** Default constructor */
        SRBTBehaviorMachine();
        /** Default destructor */
        virtual ~SRBTBehaviorMachine();
        virtual void Update(){};
        void AddCommand(String _cmd,ActionsMachineType _act,SRBTModule *mod,int _param);
        virtual void CheckCommand(String _cmd);

    protected:
    private:
        unsigned int _commandCount;
        struct CommandMach{
            String CommandRecivedM;
            ActionsMachineType ActionM;
            SRBTModule *moduleM;
            int paramM;


        }*CommandMacList;
        void Exec(CommandMach *_cmd);


};

#endif // SRBTBEHAVIORMACHINE_H
