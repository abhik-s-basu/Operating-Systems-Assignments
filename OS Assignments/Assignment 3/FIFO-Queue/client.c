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

	char buffer[7];
    char randomChar[50][7] = {{0}}; 
	int fd;

    srand(time(NULL)); 
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++){
            randomChar[i][j] = rand() % 26 + 65;
        }     
        randomChar[i][5]=i+1;
    }
	
	char * path = "fifo1";
	mkfifo(path,0666);

	char * path1 = "fifo2";
	mkfifo(path1,0666);
	
	int currIndex = 0;
    int maxIndex = 0;
    int maxSentIndex=0;



    while (1){
		
		if(maxIndex >=50){
			break;
		}
        for (; currIndex<maxIndex+5; currIndex++){
			fd = open(path,O_WRONLY);
           int  ret = write(fd, randomChar[currIndex], strlen(randomChar[currIndex]) + 1);
		   close(fd);
		   usleep(1); 
            if (ret == -1){
                perror("Write Error");
                exit(1);}
        }
        maxIndex = currIndex;
		fd = open(path1,O_RDONLY);
		int ret = read(fd, buffer, sizeof(buffer));
		close(fd);
        if (ret == -1)
        {
            perror("Read Error");
            exit(EXIT_FAILURE);
        }
        buffer[sizeof(buffer) - 1] = 0;
        printf("Max index sent is  %s to CLIENT\n", buffer);
		
    }


}