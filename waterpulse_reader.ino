#include <user_interface.h>;//Biblioteca necessaria para acessar os Timers
#include <time.h>
#include <stdlib.h>

#define input D3

int timerCount=0,r=0,state=0,outPin=0,trashCount=0,timerFlag=0;
int inVec[50],vecSum=0, prevState=0,pulse=0;


os_timer_t tmr0;//Cria o Timer. Maximo de 7 Timers.

void setup() {
  Serial.begin(115500);
  //srand(time(NULL));   // Initialization, should only be called once.
  pinMode(input,INPUT);
  os_timer_setfn(&tmr0, timer, NULL); //timer, subrotina, null
  os_timer_arm(&tmr0, 10, true); //timer, tempo em ms (entre 1ms e 2s), loop=true 
}

void loop() {
  if(timerFlag==1){
    //Serial.println(vecSum);
    timerFlag--;
    vecSum=0;
    for (int i=0;i<49;i++){
      inVec[i]=inVec[i+1];
      vecSum+=inVec[i];
    }
    inVec[49]=digitalRead(input);
    vecSum+=inVec[49];
    //Serial.println(inVec[49]);

    prevState=state;
    if (vecSum==50)
      state=1;
    if (vecSum==0)
      state=0;

    if (prevState!=state){
      pulse++;
      Serial.println(pulse);
    }
  }
  
}

void timer(void*z){ //software timer de 1ms - Conta o relógio internalo
  timerFlag++;
}
