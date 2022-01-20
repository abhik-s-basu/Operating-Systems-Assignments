#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/un.h>


int main(){

	int max=0;
	int fd;
	int idx=0;
    int result=0;
	int currIdx = 0;
	char buffer[7];

	char * path = "fifo1";
	mkfifo(path,0666);

	char * path1 = "fifo2";
	mkfifo(path1,0666);
	
	while(1){       
		while(currIdx < max+5){
			usleep(2);
			//usleep can be added
			if(max >= 50){
				exit(EXIT_SUCCESS);
			}
			fd = open(path,O_RDONLY);
			int ret = read(fd, buffer, sizeof(buffer));
			close(fd);
            if (ret == -1){
                perror("Reading Failure");
                exit(EXIT_FAILURE);
            }
            buffer[sizeof(buffer) - 1] = 0;
			currIdx = buffer[5];//updating
			printf("Index is  %d, String sent is ",currIdx);
			for(int i=0;i<5;i++){
				printf("%c",buffer[i]);
			}
			printf(" to SERVER\n");
			// printf("hello hello");
			
		}
		// printf("hello 123 \n");
		max=currIdx;
		result=max;
		// result = buffer[5];
        sprintf(buffer, "%d", result);
		fd = open(path1,O_WRONLY);
        int ret = write(fd, buffer, sizeof(buffer));
		close(fd);
				// return 0;
        if (ret == -1){
            	perror("Write Failure");
            	exit(EXIT_FAILURE);
        	}
				
	}
        
}

