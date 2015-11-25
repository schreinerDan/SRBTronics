#include "srbtmachine.h"
/*
SRBTMachine::SRBTMachine()
{
    //ctor
}*/

SRBTMachine::~SRBTMachine()
{
    //dtor
    delete this->listModules;
    delete this->listBehaviorSenMachine;
    delete this->listBehavior;

}
void SRBTMachine::AddBehavior(SRBTBehaviorMachine *bev){
    this->PrintSR("B m");
    this->listBehavior[this->_behaviorCount]=bev;
    this->_behaviorCount++;
}
void SRBTMachine::AddBehaviorSenMachine(SRBTBehaviorSenMachine *bev){
    this->PrintSR("B SM");
    this->listBehaviorSenMachine[this->_behaviorSMCount]=bev;
    this->_behaviorSMCount++;
}
String SRBTMachine::ReadSerial()
{
    if (!this->_ser) return "";

    return this->serialDevice.SerialRead(this->_ser);



}
String SRBTMachine::ReadBluetooth(){
    if (!this->_sbt) return "";

    return this->serialDevice.BTRead(this->_sbt);


}

void SRBTMachine::AddModule(SRBTModule *_module)
{
    this->PrintSR("a");
    _module->moduleID=this->_moduleCount;
    //SRBTMachine::PrintSR((String)this->_moduleCount);
    this->listModules[this->_moduleCount]=_module;
    //this->listModules[this->_moduleCount]=_module;
    //this->listModules[this->_moduleCount]=_module;
    this->_moduleCount++;
}

void SRBTMachine::Update()
{
    //if (!this->activeModule==NULL)
    //this->activeModule->UpdateModule();

    this->listModules[this->_moduleIndex]->UpdateModule();

    /*for(int i=0;i<this->_moduleCount;i++)
    {
        this->listModules[i]->UpdateModule();
    }*/
}
void SRBTMachine::CheckCommand(String _cmd)
{
    //this->instance()->PrintSR("Ck BvM "+_cmd);
    this->instance()->listModules[this->_moduleIndex]->CheckCommand(_cmd);

    for(int i=0;i<this->_behaviorCount;i++)
    {
        this->listBehavior[i]->CheckCommand(_cmd);
        //this->instance()->PrintSR("Ck BvM "+((String)i));
    }
    for(int i=0;i<this->_behaviorSMCount;i++)
    {
        this->listBehaviorSenMachine[i]->Update();
        //this->instance()->PrintSR("Ck BvM "+((String)i));
    }

}
