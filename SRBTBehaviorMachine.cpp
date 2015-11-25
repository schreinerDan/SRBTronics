/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */

#include "SRBTBehaviorMachine.h"
#include "srbtmachine.h"
SRBTBehaviorMachine::SRBTBehaviorMachine()
{
    //ctor
    this->CommandMacList = new CommandMach[5];
    this->_commandCount=0;
}

SRBTBehaviorMachine::~SRBTBehaviorMachine()
{
    //dtor
    delete this->CommandMacList;
}

void SRBTBehaviorMachine::AddCommand(String _cmd,ActionsMachineType _act,SRBTModule *mod,int _param)
{
    SRBTMachine::instance()->PrintSR("aCM "+_cmd);
    this->CommandMacList[this->_commandCount].CommandRecivedM=_cmd;
    this->CommandMacList[this->_commandCount].ActionM=_act;

    this->CommandMacList[this->_commandCount].moduleM=mod;
    this->CommandMacList[this->_commandCount].paramM=_param;
    this->_commandCount++;
}
void SRBTBehaviorMachine::CheckCommand(String _cmd)
{
    for(int i=0;i<this->_commandCount;i++)
    {

        if(_cmd==this->CommandMacList[i].CommandRecivedM)
        {
            SRBTMachine::instance()->PrintSR("Command "+_cmd);
            this->Exec(&this->CommandMacList[i]);
        }
    }
}

void SRBTBehaviorMachine::Exec(CommandMach *_cmd)
{
    switch (_cmd->ActionM){
        case GOTO:
            _cmd->moduleM->Start();
            break;
        case STOP:
            _cmd->moduleM->Stop();
            break;
        case START:
            _cmd->moduleM->Start();
            break;
        default:
            break;
    }
}
