/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */
#ifndef SRBTMACHINE_H
#define SRBTMACHINE_H

#include "SRBTSerialDevice.h"
#include "Stream.h"
#include "SRBTModule.h"
#include "SRBTBehaviorMachine.h"
#include "SRBTBehaviorSenMachine.h"
class SRBTMachine
{
    static SRBTMachine *s_instance;
    /** Default constructor */
    int m_val;
    //SRBTModule **_mod=new SRBTModule*[5];

    SRBTMachine(){
        this->listModules= new SRBTModule*[5];
        //this->_mod=new SRBTModule*[5];
        this->_moduleCount=0;
        this->_moduleIndex=0;
        this->_behaviorCount=0;
        this->_behaviorSMCount=0;
        this->listBehavior=new SRBTBehaviorMachine*[2];
        this->listBehaviorSenMachine=new SRBTBehaviorSenMachine*[2];

    }
    public:
        /** Instance*/
        static SRBTMachine *instance(){
            if(!s_instance)
                s_instance = new SRBTMachine();
            return s_instance;
        }
        /** Return ID of active Module*/
        unsigned int GetModuleIndex(){ return m_val;};

        unsigned int GetModuleIndex2(){ return _moduleIndex;};

        /** Set the Serial for read commands ID*/
        void SetSerial(Stream *ser){this->_ser=ser;}
        String ReadSerial();

        void SetBluetooth(SoftwareSerial *ser){this->_sbt=ser;}
        String ReadBluetooth();

        void PrintSR(String _str){this->_ser->println(_str);}
        /** Set de ID*/
        void AddModule(SRBTModule *_module);
        void SetModuleIndex(unsigned int _mi)
        {
            m_val=_mi;
            _moduleIndex=_mi;
            };
        /** Default destructor */
        void CheckCommand(String _cmd);
        virtual ~SRBTMachine();
        void Update();
        void AddBehavior(SRBTBehaviorMachine *bev);
        void AddBehaviorSenMachine(SRBTBehaviorSenMachine *bev);
        void SetActiveModule(SRBTModule *_module){this->PrintSR("Active");this->activeModule=_module;};
    protected:
    private:
        unsigned int _moduleCount;
        unsigned int _behaviorCount;
        unsigned int _behaviorSMCount;
        volatile unsigned int _moduleIndex;
        SRBTSerialDevice serialDevice;
        Stream *_ser; //serial com
        SoftwareSerial *_sbt;//cbluetooth
        SRBTModule *activeModule;
        SRBTBehaviorMachine **listBehavior;
        SRBTBehaviorSenMachine **listBehaviorSenMachine;
        //SRBTModule module;
        SRBTModule **listModules;
};

#endif // SRBTMACHINE_H
