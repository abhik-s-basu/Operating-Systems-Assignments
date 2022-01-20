#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/time.h>
#define _XOPEN_SOURCE 700
char time[100];
pid_t PID;
unsigned long r;

void sigTermHandler(){
  unsigned long rand=r/3e9;
  unsigned long hour=rand/3600;
  rand%=3600;
  unsigned long min=rand/60;
  rand%=60;
  unsigned long sec=rand;
  printf("The clock  in ST.c is: %lu h  %lu m %lu s\n",hour,min,sec);
}

unsigned long getCPUCycles(){
  unsigned long eax, edx;
  asm volatile("rdtsc\n\t": "=a" (eax), "=d" (edx));
    return (unsigned long)eax | (unsigned long)edx << 32;
}

void sigAlarmHandler(int sigNum){
  r=getCPUCycles();
  // printf("Random number in ST.c sigAlarmHandler: %lu \n",r);
  union sigval randQ;
  randQ.sival_int=r;
  sigqueue(PID,SIGTERM,randQ);
  kill(getpid(),SIGTERM);
}

int main(int argc, char const *argv[]){
  PID = atoi(argv[0]);
  struct itimerval itVal;
  itVal.it_value.tv_sec=1;
  itVal.it_value.tv_usec=0;
  itVal.it_interval = itVal.it_value;
  struct sigaction sigAct2,sigAct3;
  memset(&sigAct2,0,sizeof(sigAct2));
  memset(&sigAct3,0,sizeof(sigAct3));
  sigAct2.sa_handler = &sigTermHandler;
  sigAct3.sa_handler = &sigAlarmHandler;
  sigaction(SIGALRM,&sigAct3,NULL);
  sigaction(SIGTERM,&sigAct2,NULL);
  setitimer(ITIMER_REAL,&itVal,NULL);
  while(1){};
  return 0;
}