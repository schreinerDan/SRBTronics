/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */

#include "SRBTBehavior.h"
#include "srbtmachine.h"
SRBTBehavior::SRBTBehavior()
{
    this->CommandList=new Command[5];
    this->_commandCount=0;
    //ctor
}

SRBTBehavior::~SRBTBehavior()
{
    delete this->CommandList;

    //dtor
}
void SRBTBehavior::AddCommand(String _cmd,ActionsType _act,unsigned int _mid,SRBTMotor* mtr,int _param)
{
    this->CommandList[this->_commandCount].CommandRecived=_cmd;
    this->CommandList[this->_commandCount].Action=_act;
    this->CommandList[this->_commandCount].MotorID=_mid;
    this->CommandList[this->_commandCount].motorA=mtr;
    this->CommandList[this->_commandCount].param=_param;
    this->_commandCount++;
}
void SRBTBehavior::CheckCommand(String _cmd)
{
    for(int i=0;i<this->_commandCount;i++)
    {
        if(_cmd==this->CommandList[i].CommandRecived)
        {
            String mtid=(String)this->CommandList[i].MotorID;
        //    SRBTMachine::instance()->PrintSR("Command "+_cmd);
            SRBTMachine::instance()->PrintSR("Motor  "+mtid);
            this->Exec(&this->CommandList[i]);
        }
    }
}
void SRBTBehavior::Exec(Command *_cmd)
{
    switch (_cmd->Action){
        case RUN:
            _cmd->motorA->Run(_cmd->param);
            break;
        case RUNPOS:
            _cmd->motorA->RunToPos(_cmd->param);
            break;
        case RUNSENSOR:
            _cmd->motorA->RunToSensor(_cmd->param);
            break;
        case STOP:
            _cmd->motorA->Stop();
            break;

        default:
            break;
    }
}
