/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */

#include "SRBTDCMotor.h"
#include <Arduino.h>
SRBTDCMotor::SRBTDCMotor()
{
    //ctort
    //this->_pin1
}

SRBTDCMotor::SRBTDCMotor(int p1,int p2,int s1, int s2)
{
    this->SetupMotor(p1,p2,s1,s2);
    this->_pin1=p1;
    this->_pin2=p2;
    this->_sen1=s1;
    this->_sen2=s2;
    pinMode(this->_pin1,OUTPUT);
    pinMode(this->_pin2,OUTPUT);
    if(this->_sen1!=0)pinMode(this->_sen1,INPUT);
    if(this->_sen2!=0)pinMode(this->_sen2,INPUT);

}


SRBTDCMotor::~SRBTDCMotor()
{
    //dtor
}
void SRBTDCMotor::RunToPos(int pos)
{
    this->direction=(pos>0)?LEFT:RIGHT;
    this->currentPos=0;
    if(pos<0)pos*=-1;
    this->toPosition=pos;
    this->runType=POSITION;

    this->motorRun();

}
void SRBTDCMotor::motorRun()
{
    if(this->direction==LEFT){
        SRBTMachine::instance()->PrintSR("LEFT");
        digitalWrite(this->_pin1,HIGH);
        digitalWrite(this->_pin2,LOW);
    }
    else {
        SRBTMachine::instance()->PrintSR("RIGHT");
        digitalWrite(this->_pin1,LOW);
        digitalWrite(this->_pin2,HIGH);

    }
    this->isRunning=true;
}
void SRBTDCMotor::Run(int pos)
{
    this->direction=(pos>0)?LEFT:RIGHT;
    this->currentPos=0;
    if(pos<0)pos*=-1;
    this->toPosition=pos;
    this->runType=LOOPING;

    this->motorRun();

}

void SRBTDCMotor::RunToSensor(int pos)
{
    this->direction=(pos>0)?LEFT:RIGHT;
    this->currentPos=0;
    if(pos<0)pos*=-1;
    this->toPosition=pos;
    this->runType=SENSORFC;


    this->motorRun();

}
void SRBTDCMotor::UpdatePos()
{
 //   SRBTMachine::instance()->PrintSR("UpdatePos");
    if (!this->isRunning) return;


switch (this->runType){

    case LOOPING:
        break;
    case SENSORFC:
        if(this->checkSensor()){
            this->isRunning=false;
            SRBTMachine::instance()->PrintSR("SENSOR");
            this->Stop();
        }
        break;
    case POSITION:
        this->currentPos+=1;
     //   String _currpos;
       // _currpos=(String)(this->currentPos);

        if (this->currentPos>=this->toPosition)
        {
            this->isRunning=false;


            SRBTMachine::instance()->PrintSR("CHEGOU ");
            this->Stop();
        }
        break;
    default:
        break;
}

}
bool SRBTDCMotor::checkSensor()
{

    int _sensorPin=(this->direction==LEFT)?this->_sen1:this->_sen2;

    if (digitalRead(_sensorPin)==1){
        return true;
    }else{
        return false;
    }
}
void SRBTDCMotor::Stop()
{
    SRBTMachine::instance()->PrintSR("Motor STOP");
    digitalWrite(this->_pin1,LOW);
    digitalWrite(this->_pin2,LOW);
    this->isRunning=false;
}
