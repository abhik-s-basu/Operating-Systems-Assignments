#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<sys/un.h>
#include<time.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/un.h>


struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} ;

int main() {
  key_t key,key1;
  int msgid,msgid1;
  
  struct mesg_buffer message;
  struct mesg_buffer message1;

    char randomChar[50][7] = {{0}}; 

    srand(time(NULL)); 
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++){
            randomChar[i][j] = rand() % 26 + 65;
        }     
        randomChar[i][5]=i+1;
    }

  key = ftok("client.c", 68);
  key1 = ftok("server.c",69);
  
  message.mesg_type = 1;
  message1.mesg_type=1;
  msgid = msgget(key, 0666 | IPC_CREAT);
  msgid1 = msgget(key1, 0666 | IPC_CREAT);

  int currIndex = 0;
  int maxIndex = 0;

  while (1){
		if(maxIndex >=50){
			break;
		}
        for (; currIndex<maxIndex+5; currIndex++){
			strncpy(message.mesg_text, randomChar[currIndex], sizeof(randomChar[currIndex]));
			int ret = msgsnd(msgid, &message, 10, 0);
			sleep(1); 
			if(ret==-1){
				perror("sending error");
				exit(1);
			}
		    
        }
        maxIndex = currIndex;
		int ret =msgrcv(msgid1, &message1, 10, 1, 0);
        if (ret == -1)
        {
            perror("Receving Error");
            exit(EXIT_FAILURE);
        }
        printf("Max index sent is  %s to CLIENT\n", message1.mesg_text);
    }
}