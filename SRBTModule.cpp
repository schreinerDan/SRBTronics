/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */
#include "SRBTModule.h"
#include "srbtmachine.h"
SRBTModule::SRBTModule()
{
        this->moduleID=0;
        this->_motorCount=0;
        this->_commandCount=0;
        this->_behaviorCount=0;
        this->_sensorBHVCount=0;
        this->listBehavior=new SRBTBehavior*[5];
        this->listCommands=new SRBTBehavior*[5];
        this->isRunning=false;
        //this->Start();
        this->listMotors=new SRBTMotor*[3];
        this->listSensorsBHV = new SRBTBehaviorSensor*[5];
}

SRBTModule::~SRBTModule()
{
    //this->Stop();
    //dtor
    delete this->listBehavior;
    delete this->listMotors;
    delete this->listCommands;
    delete this->listSensorsBHV;


}
void SRBTModule::AddMotor(SRBTMotor *_motor)
{
    this->listMotors[this->_motorCount]=_motor;
    this->_motorCount++;

}
void SRBTModule::AddBehavior(SRBTBehavior *_behavior)
{
    this->listBehavior[this->_behaviorCount]=_behavior;
    this->_behaviorCount++;
}
void SRBTModule::AddCommandBHV(SRBTBehavior *_behavior)
{
    //_behavior->parent=&this;
    this->listCommands[this->_commandCount]=_behavior;
    this->_commandCount++;
}

void SRBTModule::AddSensorBHV(SRBTBehaviorSensor* _behavior)
{

    this->listSensorsBHV[this->_sensorBHVCount]=_behavior;
    this->_sensorBHVCount++;



}
void SRBTModule::UpdateModule()
{
    for(int i=0;i<this->_motorCount;i++){
            this->listMotors[i]->UpdatePos();
    }
    for (int y=0;y<this->_sensorBHVCount;y++)
    {
        this->listSensorsBHV[y]->checkSensor();
    }


}
void SRBTModule::Start()
{
    this->Active=true;
    this->isRunning=true;
    String mId=(String)this->moduleID;
    SRBTMachine::instance()->PrintSR("Start Mod "+mId);
    SRBTMachine::instance()->SetModuleIndex(this->moduleID);
}
void SRBTModule::CheckCommand(String _cmd)
{
    for(int i=0;i<this->_commandCount;i++)
    {
        this->listCommands[i]->CheckCommand(_cmd);
    }
}
