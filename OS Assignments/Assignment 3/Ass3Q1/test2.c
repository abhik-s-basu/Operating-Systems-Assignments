#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<linux/sched.h>
#include <sys/resource.h>
#include<sched.h>
#define delayAdder 449

int main(){
        struct timespec ts;
        int which = PRIO_PROCESS;
        pid_t PID = getpid();
        setpriority(which,PID,5);
        int retVal = syscall(delayAdder,100000,PID);
        if(retVal!= 0){
            printf("Error in reading file");
        }
        int ret = getpriority(which, PID);
        printf("Nice value of process is : %d\n", ret);
        double startTime = omp_get_wtime();
        for(long i =0; i<1000000000; ++i);
        double endTime = omp_get_wtime();
        double timeDiff = endTime - startTime;
        if (sched_rr_get_interval(getpid(), &ts)==-1){
            perror("Error aagya");
        }

        printf("Timeslice for Sys Call process is: %d seconds, %ld nanoseconds\n", ts.tv_sec, ts.tv_nsec);
        printf("Finished executing for Sys Call in %f seconds \n",timeDiff);

    return 0;
}