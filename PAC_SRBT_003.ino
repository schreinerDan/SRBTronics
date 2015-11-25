/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */

#include <SoftwareSerial.h>
#include <TimerThree.h>
#include <srbtmachine.h>
#include "SRBTMotor.h"
#include "SRBTDCMotor.h"
#include "SRBTModule.h"
#include "SRBTBehavior.h"
#include "SRBTBehaviorMachine.h"
#include "SRBTSensor.h"
#include "SRBTBehaviorSensor.h"
#include "SRBTBehaviorSenMachine.h"

#include "SRBTSerialDevice.h"



SRBTMachine *SRBTMachine::s_instance=0;
SRBTSerialDevice BTDevice;
SRBTMotor * mtr_est_ser=new SRBTDCMotor(30,31,0,0);//Motor esteira serializador

SRBTMotor * mtr_ban_ser=new SRBTDCMotor(22,23,0,0);//Motor bandeja manipulador frascos
SRBTMotor * mtr_gar_ser=new SRBTDCMotor(44,45,0,0);//Motor garra manipulador frascos
SRBTMotor * mtr_tam_ser=new SRBTDCMotor(26,27,0,0);//Motor fecha tampa manipulador frascos
SRBTMotor * mtr_por_ser=new SRBTDCMotor(48,49,2,3);//Motor porta compartimento de alimentacao de capsulas serializador
SRBTMotor * mtr_fun_ser=new SRBTDCMotor(38,39,0,0);//Motor fundo falso serializador

SRBTModule serializer;//=new SRBTModule();
SRBTModule manfrascos;//=new SRBTModule();
SRBTModule pesagem;

SRBTBehavior bhv_est_ser; //Comportamento da esteira serializador
SRBTBehavior bhv_man;//Comportamento modulo manipulador de frascos
SRBTBehavior bhv_por_ser;//comportamento portas do serializador

SRBTBehaviorSenMachine  bhv_senmachine;//comportamento dos sensores da maquina

//SRBTSensor   sen_est_count=new SRBTSensor(ANALOG,A0);
SRBTSensor sen_est_count(ANALOG,A0);//Sensor reflexivo contagem das capsulas

SRBTBehaviorSensor bhv_sen_cout; //Comportamento sensor de contagem de capsulas
SRBTBehaviorMachine bhv_main;//Comportamento dos modulos da maquina
//TODOreceber valor do menu 

int TotalCapsulas = 60;//Numero de capsulas do lote
int parcialCapsulas=0;
SoftwareSerial serialBT(10,11);//Modulo Bluetooth 

void setup() {

    Serial.begin(9600);//Inicia comunicacao com PC
    SRBTMachine::instance()->SetSerial(&Serial);//Adiciona serial na maquina
    
    serialBT.begin(9600);//Inicia Bluetooth
    SRBTMachine::instance()->SetBluetooth(&serialBT);//Adiciona bluetooth na maquina
    
    Serial.println("Init");
    
    Serial1.begin(4800);//Inicia comunicacao com Balanca
    
    InitMachine();//Inicia os parametros da maquina
    Timer3.initialize(10000);
    Timer3.attachInterrupt(timerloop);


}

bool PesagemActive=false;
volatile bool recebendo=false;
String cmdBt="";

void loop() {
  recebendo=false;
    cmdBt="";
    if(serialBT.available()){
      String cmf=SRBTMachine::instance()->ReadBluetooth();//Le dados do Bluetooth
         if (cmdBt!=""){
            Serial.println(cmdBt);
            SRBTMachine::instance()->CheckCommand(cmf);//Verifica comando 
         }  
     }
    
    if(Serial.available()){
      recebendo=true;
      String cmf=SRBTMachine::instance()->ReadSerial();//Le dados da Serial
      if (cmf!=""){
          Serial.println(cmf);
          SRBTMachine::instance()->CheckCommand(cmf);//Verifica comando
      }
    }
    
    
//Para fins de Testes
//TODO implementar classe para tratamento de pesagem por amostragem
   if(sen_est_count.getCounter()==5){ //se contador chega a 5 capsulas
        noInterrupts();
        Serial.println(sen_est_count.getCounter());

        parcialCapsulas+=sen_est_count.getCounter();
        Serial.println(parcialCapsulas);

        sen_est_count.Counter(-sen_est_count.getCounter());//zera contador
        
        interrupts();
        if (parcialCapsulas == TotalCapsulas){// se contador chega ao numero de capsulas do lote
     
            Serial.println("**********************");
            Serial.println("  FIM DO PROCESSO      ");
            Serial.println("**********************");
            parcialCapsulas=0;
            manfrascos.Start();


        }
        else{//se parcial das capsulas for < que total de capsulas do lote


          pesagem.Start();//inicia pesagem
          PesagemActive=true;
        }
   }
   

   if (PesagemActive==true){
        recebendo=true;
        Serial.println("PESAGEM");
        String  balData="";
        //Recebe dados da balanca
        while(Serial1.available()>0)
        {
            char b = Serial1.read();
            if (b!=10){
                balData+=b;
            }
        }
        if (balData!="")
        {
            //TODO implementar calculo de desvio padrao 
            Serial.println(balData);//Imprime dados recebidos da balanca
            
            PesagemActive=false;
            serializer.Start();//inicial modulo serializador
            Serial.println("Reiniciando Serializador");
            delay(5000);//aguarda o transporte das capsulas da balanca ate o frasco
            mtr_est_ser->Run(1);// reinicia a esteira
        }
        delay(50);

   }
   
   if(recebendo){
    delay(100);
   
   }
   

  delay(100);
}


void timerloop()
{
   //  Serial.println(analogRead(A0));

    SRBTMachine::instance()->Update();// Atualiza maquina
}

void InitMachine(){

    bhv_main.AddCommand("start_ser",GOTO,&serializer,0);//Quando recebe comando #start_ser* , inicia modulo serializador
    bhv_main.AddCommand("start_man",GOTO,&manfrascos,0);//Quando recebe comando #start_man* , inicia modulo manipulador de frascos

    SRBTMachine::instance()->AddBehavior(&bhv_main);//Adiciona comportamento a maquina

    bhv_sen_cout.AddCommand(SENSORBLINK,COUNTERS,&sen_est_count,780,1);//Quando sensor reflexivo recebe valor <que 780 e volta para estado inicial , incrementa +1
    bhv_sen_cout.AddCommand(ONCOUNTERVAL,STOPS,&sen_est_count,mtr_est_ser,5,0);//Quando contador chega a 5, para o motor da esteira

    //Adiciona os motores ao modulo serializador
    serializer.AddMotor(mtr_est_ser);
    serializer.AddMotor(mtr_por_ser);
    serializer.AddMotor(mtr_fun_ser);
    
    bhv_est_ser.AddCommand("on-est",RUN,0,mtr_est_ser,1);//Quando recebe comando #on-est* liga a esteira
    bhv_est_ser.AddCommand("st-est",STOP,0,mtr_est_ser,0);//Quando recebe comando #st-est* desliga esteira



    delay(20);
    bhv_por_ser.AddCommand("op_por",RUNSENSOR,0,mtr_por_ser,-2);//Quando recebe comando #op_por* abre a porta ate o sensor de fim de curso
    delay(20);
    bhv_por_ser.AddCommand("cl_por",RUNSENSOR,0,mtr_por_ser,20);//Quando recebe comando #cl_por* fecha a porta ate o sensor de fim de curso
    delay(20);
    bhv_por_ser.AddCommand("op_fun",RUNPOS,0,mtr_fun_ser,-20);//Quando recebe comando #op_por* abre parcialmente fundo falso (20 milisecs)
    delay(20);
    bhv_por_ser.AddCommand("cl_fun",RUNPOS,0,mtr_fun_ser,20);//Quando recebe comando #op_por* fecha parcialmente fundo falso (20 milisecs)
    delay(20);

    //Adiciona os comportamentos ao modulo serializador
    serializer.AddCommandBHV(&bhv_est_ser);
    delay(100);
    serializer.AddCommandBHV(&bhv_por_ser);
    delay(100);
    serializer.AddSensorBHV(&bhv_sen_cout);

    //Adiciona motores do modulo manipulador de frascos
    manfrascos.AddMotor(mtr_ban_ser);
    manfrascos.AddMotor(mtr_gar_ser);
    manfrascos.AddMotor(mtr_tam_ser);

    bhv_man.AddCommand("op-ban-man",RUNPOS,0,mtr_ban_ser,-100);//Quando recebe comando #op-ban-man* abre a bandeja
    bhv_man.AddCommand("cl-ban-man",RUNPOS,0,mtr_ban_ser,100);//Quando recebe comando #cl-ban-man* fecha a bandeja
    bhv_man.AddCommand("op-ban-man",RUNPOS,0,mtr_gar_ser,-30);//Quando recebe comando #op-ban-man* abre a garra
    bhv_man.AddCommand("cl-ban-man",RUNPOS,0,mtr_gar_ser,30);//Quando recebe comando #cl-ban-man* fecha a garra
    bhv_man.AddCommand("cl-tam-man",RUNPOS,0,mtr_tam_ser,-100);//Quando recebe comando #cl-tam-man* fecha a tampa do frasco

    manfrascos.AddCommandBHV(&bhv_man);//adiciona comportamento ao modulo manipulador de frascos


    delay(100);

    SRBTMachine::instance()->AddModule(&manfrascos);//adiciona modulo manipulador de frascos `a maquina

    delay(100);

    SRBTMachine::instance()->AddModule(&serializer);//adiciona modulo serializador `a maquina


    delay(100);

    SRBTMachine::instance()->AddModule(&pesagem);//adiciona modulo pesagem `a maquina


    delay(100);

    manfrascos.Start();//inicia modulo manipulador de frascos



}







