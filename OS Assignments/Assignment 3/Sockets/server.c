#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <time.h>
#define SOCKET_NAME "temp.socket"

int main(int argc, char *argv[])
{
    struct sockaddr_un name;
    int down_flag = 0;
    int ret;
    int connection_socket;
    int data_socket;
    int max=0;
	int idx=0;
    int result=0;
    char buffer[7];

    connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (connection_socket == -1){
        perror("Socket Connection Problem");
        exit(EXIT_FAILURE);
    }

    memset(&name, 0, sizeof(name));


    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);
    ret = bind(connection_socket, (const struct sockaddr *)&name, sizeof(name));
    if (ret == -1){
        perror("Binding failure");
        exit(EXIT_FAILURE);
    }


    ret = listen(connection_socket, 20);
    if (ret == -1){
        perror("Listening Faiure");
        exit(EXIT_FAILURE);
    }


    while(1){

        data_socket = accept(connection_socket, NULL, NULL);
        if (data_socket == -1){
            perror("Acception Failure");
            exit(EXIT_FAILURE);
        }
        
		while(1){
			if(max >= 50){
				exit(EXIT_SUCCESS);
			}
			ret = read(data_socket, buffer, sizeof(buffer));
            if (ret == -1){
                perror("Reading Failure");
                exit(EXIT_FAILURE);
            }
            buffer[sizeof(buffer) - 1] = 0;
			int currIdx = buffer[5];
			printf("Index is  %d, String sent is ",currIdx);
			for(int i=0;i<5;i++){
				printf("%c",buffer[i]);
			}
			printf(" to SERVER\n");
			if(currIdx == max+5){
				// printf("hello \n");
				max=currIdx;
				result=max;
				// result = buffer[5];
            	sprintf(buffer, "%d", result);
        		ret = write(data_socket, buffer, sizeof(buffer));
				// return 0;
        		if (ret == -1){
            		perror("Write Failure");
            		exit(EXIT_FAILURE);
        		}
			}
			
		}
            
        close(data_socket);
        
    }
    close(connection_socket);
	printf("exitting");
    unlink(SOCKET_NAME);

    exit(EXIT_SUCCESS);
}