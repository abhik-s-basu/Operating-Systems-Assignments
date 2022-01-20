#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<sys/time.h>
#include<time.h>
#include<signal.h>
#include<stdint.h>
#include<inttypes.h>
#include<string.h>
#include<fcntl.h>

int main()
{
    
    int fd = open("/dev/urandom",O_RDONLY);
    while(1){
        unsigned char arr[8];
        int numData = read(fd,&arr,8);
        unsigned long long var = 0;
        for(int i = 0;i<8;i++){
            var = var << 8;
            var |= arr[i];
        }
        if(!syscall(451,var)){
            printf("Produced: %llu \n",var);
        }

    }
    

    
    

    return 0;
}
