#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/time.h>
#define _XOPEN_SOURCE 700

pid_t PID;

int randGenerator()
{
    int rand;
    int timer=0;
    const int timeout = 10;
    while (timer<timeout)
    {
        asm("rdrand %0\n\t":"=a"(rand)::);
        if (rand) break;
        timer++;
    }
    return rand;
}

void sigAlarmHandler(int sigNum){
  int rand=randGenerator();
  printf("Random number in SR.c sigAlarmHandler: %d \n",rand);
  union sigval randQ;
  randQ.sival_int=rand;
  sigqueue(PID,SIGTERM,randQ);
}

int main(int argc, char const *argv[]){
  PID = atoi(argv[0]);
  struct itimerval itVal;
  itVal.it_value.tv_sec=1;
  itVal.it_value.tv_usec=0;
  itVal.it_interval = itVal.it_value;
  struct sigaction sigAct1;
  memset(&sigAct1,0,sizeof(sigAct1));
  sigAct1.sa_handler = &sigAlarmHandler;
  sigaction(SIGALRM,&sigAct1,NULL);
  setitimer(ITIMER_REAL,&itVal,NULL);
  while(1){};
  return 0;
}