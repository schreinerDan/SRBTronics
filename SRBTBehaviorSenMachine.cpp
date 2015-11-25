#include "SRBTBehaviorSenMachine.h"
#include "srbtmachine.h"
SRBTBehaviorSenMachine::SRBTBehaviorSenMachine()
{
    //ctor
}

SRBTBehaviorSenMachine::~SRBTBehaviorSenMachine()
{
    //dtor
}
void SRBTBehaviorSenMachine::AddCommand(EventType _evt,ActionsSenMachineType _act,SRBTSensor *sen,int _vals,int _param)
{

    //SRBTMachine::instance()->PrintSR("aCS ");
    this->CommandSenMachineList[this->_commandCount].EventSM=_evt;
    this->CommandSenMachineList[this->_commandCount].ActionSM=_act;
    this->CommandSenMachineList[this->_commandCount].sensorSM=sen;


    this->CommandSenMachineList[this->_commandCount].valSensorSM=_vals;
    this->CommandSenMachineList[this->_commandCount].paramSM=_param;
    this->_commandCount++;
}
void SRBTBehaviorSenMachine::AddCommand(EventType _evt,ActionsSenMachineType _act,SRBTSensor *sen,SRBTMotor *mot,int _vals,int _param)
{

    //SRBTMachine::instance()->PrintSR("aCS ");
    this->CommandSenMachineList[this->_commandCount].EventSM=_evt;
    this->CommandSenMachineList[this->_commandCount].ActionSM=_act;
    this->CommandSenMachineList[this->_commandCount].sensorSM=sen;
    this->CommandSenMachineList[this->_commandCount].motorSM=mot;

    this->CommandSenMachineList[this->_commandCount].valSensorSM=_vals;
    this->CommandSenMachineList[this->_commandCount].paramSM=_param;
    this->_commandCount++;
}
void SRBTBehaviorSenMachine::AddCommand(EventType _evt,ActionsSenMachineType _act,SRBTSensor *sen,SRBTModule *mod,int _vals,int _param)
{

    //SRBTMachine::instance()->PrintSR("aCS ");
    this->CommandSenMachineList[this->_commandCount].EventSM=_evt;
    this->CommandSenMachineList[this->_commandCount].ActionSM=_act;
    this->CommandSenMachineList[this->_commandCount].sensorSM=sen;
    this->CommandSenMachineList[this->_commandCount].moduleSM=mod;

    this->CommandSenMachineList[this->_commandCount].valSensorSM=_vals;
    this->CommandSenMachineList[this->_commandCount].paramSM=_param;
    this->_commandCount++;
}
bool SRBTBehaviorSenMachine::checkSensor()
{
        for(int i=0;i<this->_commandCount;i++)
            {
                sensorValue =this->CommandSenMachineList[i].sensorSM->GetValue();

                switch(this->CommandSenMachineList[i].EventSM)
                {
                    case SENSORVAL:
                        if(sensorValue == this->CommandSenMachineList[i].sensorSM->GetValue())
                            Exec(&this->CommandSenMachineList[i]);
                        break;

                    case ONCOUNTERVAL:
                        if(this->CommandSenMachineList[i].sensorSM->getCounter()==this->CommandSenMachineList[i].valSensorSM){
                            Serial.println("SCOUNT");
                            this->CommandSenMachineList[i].sensorSM->Counter(-(this->CommandSenMachineList[i].valSensorSM));
                            Exec(&this->CommandSenMachineList[i]);
                        }
                        break;

                    case SENSORBLINK:

                         //.SRBTMachine::instance()->PrintSR("count<");

                        if(sensorValue <= this->CommandSenMachineList[i].valSensorSM){
                            this->lastState=1;
                        }
                        else
                        {
                            if(this->lastState==1){
                                this->lastState=0;
                                SRBTMachine::instance()->PrintSR("BLINK");
                                Exec(&this->CommandSenMachineList[i]);
                                delay(100);
                            }
                        }

                        break;

                default:
                    break;
                }

    }


}
void SRBTBehaviorSenMachine::Exec(CommandSensorMachine *_cmd)
{
    switch (_cmd->ActionSM){
        case COUNTERSM:
            _cmd->sensorSM->Counter(_cmd->paramSM);
            _cmd->varCountSM+=_cmd->paramSM;
            //String _st=(String)_cmd->sensorS->getCounter();
            SRBTMachine::instance()->PrintSR("***************");
            Serial.println(_cmd->sensorSM->getCounter());
            SRBTMachine::instance()->PrintSR("***************");
            break;
        case STOPSM:
            _cmd->motorSM->Stop();
            break;

        case RUNSM:
            _cmd->motorSM->Run(_cmd->paramSM);
            break;
        case GOTOSM:
            _cmd->moduleSM->Start();
            //_cmd->motorS->Run(_cmd->paramS);
            break;

        default:
            break;
    }
}

