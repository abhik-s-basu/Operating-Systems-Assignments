#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#define _XOPEN_SOURCE 700

void sigTermHandler(int signo, siginfo_t *si,void *ucontext){
    printf("Handled %d sent by process id %d \n",signo,si->si_pid);
    printf("Random number generated is %d \n",si->si_value.sival_int);
}
int main(){
  pid_t S1=fork();
  if(S1<0){
    printf("Error!, couldn't create S1 process \n");
    exit(0);
  }
  else if(S1 > 0){
    char strS1[10];
    sprintf(strS1, "%d",S1);
    pid_t ST=fork();
    if(ST<0){
      printf("Error!, couldn't create ST process \n");
      exit(0);
    }
    else if(ST>0){
      pid_t SR=fork();
      if(SR<0){
        printf("Error!, couldn't create SR process \n");
        exit(0);
      }
      else if(SR>0){
        while(1){};
      }
      else{
      execl("SR",strS1,NULL);
      }
    }
    else {
      execl("ST",strS1,NULL);
    }
  }
  else{
    // pid_t pid=getpid();
    struct sigaction sigAct;
    memset(&sigAct,0,sizeof(sigAct));
    sigAct.sa_sigaction = &sigTermHandler;
    sigAct.sa_flags=SA_SIGINFO;
    sigaction(SIGTERM,&sigAct,NULL);
    while(1){};
  }
  return 0;
}