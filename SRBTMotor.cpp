#include "SRBTMotor.h"

SRBTMotor::SRBTMotor()
{
    //ctor
}
SRBTMotor::SRBTMotor(int p1,int p2,int s1, int s2)
{
    this->_pin1=p1;
    this->_pin2=p2;
    this->_sen1=s1;
    this->_sen2=s2;
    pinMode(this->_pin1,OUTPUT);
    pinMode(this->_pin2,OUTPUT);
    if(this->_sen1!=0)pinMode(this->_sen1,INPUT);
    if(this->_sen2!=0)pinMode(this->_sen2,INPUT);
}
SRBTMotor::~SRBTMotor()
{
    //dtor
}
void SRBTMotor::UpdatePos()
{
//this->currentPos++;



}
void SRBTMotor::SetupMotor(int p1,int p2,int s1, int s2)
{
    this->_pin1=p1;
    this->_pin2=p2;
    this->_sen1=s1;
    this->_sen2=s2;
    pinMode(this->_pin1,OUTPUT);
    pinMode(this->_pin2,OUTPUT);
    if(this->_sen1!=0)pinMode(this->_sen1,INPUT);
    if(this->_sen2!=0)pinMode(this->_sen2,INPUT);


}
