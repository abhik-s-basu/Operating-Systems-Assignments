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
	
int main(){
	int max=0;
	int fd;
	int idx=0;
    int result=0;
	int currIdx = 0;
	char buffer[7];

	key_t key,key1;
  	int msgid,msgid1;
    struct mesg_buffer message;
    struct mesg_buffer message1;
	
	key = ftok("client.c", 68);
	key1 = ftok("server.c", 69);
	
	message.mesg_type=1;
	message1.mesg_type=1;
	msgid = msgget(key, 0666 | IPC_CREAT);
	msgid1 = msgget(key1, 0666 | IPC_CREAT);

	while(1){       
		while(currIdx < max+5){
			if(max >= 50){
				exit(EXIT_SUCCESS);
			}
			int ret =msgrcv(msgid, &message, 10, 1, 0);
			sleep(1);
            if (ret == -1){
                perror("Receiving Failure");
                exit(EXIT_FAILURE);
            }
            message.mesg_text[sizeof(message.mesg_text) - 1] = 0;
			char cI = message.mesg_text[5];//updating
			currIdx = (int)cI;
			printf("Index is  %d, String sent is ",currIdx);
			for(int i=0;i<5;i++){
				printf("%c",message.mesg_text[i]);
			}
			printf(" to SERVER\n");
			
		}
		max=currIdx;
		result=max;
        sprintf(message1.mesg_text, "%d", result);
		int ret = msgsnd(msgid1, &message1, 10, 0);
        if (ret == -1){
            	perror("Sending Failure");
            	exit(EXIT_FAILURE);
        	}
				
	}
	msgctl(msgid, IPC_RMID, NULL);
	msgctl(msgid1, IPC_RMID, NULL);

}