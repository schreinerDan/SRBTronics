#include "SRBTBehaviorSensor.h"
#include "srbtmachine.h"

SRBTBehaviorSensor::SRBTBehaviorSensor()
{
    this->CommandSenList= new CommandSensor[5];
    //ctor
}

SRBTBehaviorSensor::~SRBTBehaviorSensor()
{
    //dtor
}
void SRBTBehaviorSensor::AddCommand(EventType _evt,ActionsSensorType _act,SRBTSensor *sen,int _vals,int _param)
{

    //SRBTMachine::instance()->PrintSR("aCS ");
    this->CommandSenList[this->_commandCount].EventS=_evt;
    this->CommandSenList[this->_commandCount].isExecuted=false;
    this->CommandSenList[this->_commandCount].ActionS=_act;
    this->CommandSenList[this->_commandCount].sensorS=sen;


    this->CommandSenList[this->_commandCount].valSensor=_vals;
    this->CommandSenList[this->_commandCount].paramS=_param;
    this->_commandCount++;
}
void SRBTBehaviorSensor::AddCommand(EventType _evt,ActionsSensorType _act,SRBTSensor *sen,SRBTMotor *mot,int _vals,int _param)
{

    //SRBTMachine::instance()->PrintSR("aCS ");

    this->CommandSenList[this->_commandCount].isExecuted=false;
    this->CommandSenList[this->_commandCount].EventS=_evt;
    this->CommandSenList[this->_commandCount].ActionS=_act;
    this->CommandSenList[this->_commandCount].sensorS=sen;
    this->CommandSenList[this->_commandCount].motorS=mot;

    this->CommandSenList[this->_commandCount].valSensor=_vals;
    this->CommandSenList[this->_commandCount].paramS=_param;
    this->_commandCount++;
}

void SRBTBehaviorSensor::enableCommands(){
        for(int i=0;i<this->_commandCount;i++)
            {
                this->CommandSenList[i].isExecuted=false;
            }

}
bool SRBTBehaviorSensor::checkSensor()
{
        for(int i=0;i<this->_commandCount;i++)
            {
                sensorValue =this->CommandSenList[i].sensorS->GetValue();

                switch(this->CommandSenList[i].EventS)
                {
                    case SENSORVAL:
                        if(sensorValue == this->CommandSenList[i].sensorS->GetValue())
                            Exec(&this->CommandSenList[i]);
                        break;

                    case ONCOUNTERVAL:
                        if(this->CommandSenList[i].sensorS->getCounter()==this->CommandSenList[i].valSensor){
                            Serial.println("SCOUNT");
                           // this->CommandSenList[i].sensorS->Counter(-(this->CommandSenList[i].valSensor));
                            Exec(&this->CommandSenList[i]);
                        }
                        break;

                    case SENSORBLINK:

                         //.SRBTMachine::instance()->PrintSR("count<");

                        if(sensorValue <= this->CommandSenList[i].valSensor){
                            this->lastState=1;
                        }
                        else
                        {
                            if(this->lastState==1){
                                this->lastState=0;
                                SRBTMachine::instance()->PrintSR("BLINK");
                                Exec(&this->CommandSenList[i]);
                                delay(100);
                            }
                        }

                        break;

                default:
                    break;
                }

    }


}


void SRBTBehaviorSensor::Exec(CommandSensor *_cmd)
{
    if(!_cmd->isExecuted){
            this->enableCommands();
            switch (_cmd->ActionS){
                case COUNTERS:

                    _cmd->sensorS->Counter(_cmd->paramS);
                    _cmd->varCount+=_cmd->paramS;
                    //String _st=(String)_cmd->sensorS->getCounter();
                    SRBTMachine::instance()->PrintSR("***************");
                    Serial.println(_cmd->sensorS->getCounter());
                    SRBTMachine::instance()->PrintSR("***************");
                    break;
                case STOPS:
                    _cmd->isExecuted=true;
                    _cmd->motorS->Stop();
                    break;

                case RUNS:
                    _cmd->isExecuted=true;
                    _cmd->motorS->Run(_cmd->paramS);
                    break;

                default:
                    break;
            }
    }
}

