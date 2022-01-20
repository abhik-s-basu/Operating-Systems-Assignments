#include <errno.h>
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
    struct sockaddr_un addr;
    int ret;
    int data_socket;
    char buffer[7];
    char randomChar[50][7] = {{0}}; 

    srand(time(NULL)); 
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++){
            randomChar[i][j] = rand() % 26 + 65;
        }     
        randomChar[i][5]=i+1;
    }

    data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (data_socket == -1)
    {
        perror("Socket creation failure");
        exit(EXIT_FAILURE);
    }

    

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
    ret = connect(data_socket, (const struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        fprintf(stderr, "The server is down.\n");
        exit(EXIT_FAILURE);
    }

    int currIndex = 0;
    int maxIndex = 0;
    int maxSentIndex=0;
    while (1){
		if(maxIndex >=50){
			break;
		}
        for (; currIndex<maxIndex+5; currIndex++){
            ret = write(data_socket, randomChar[currIndex], strlen(randomChar[currIndex]) + 1);
            if (ret == -1){
                perror("Write Error");
                exit(1);}
        }
        maxIndex = currIndex;
	
        ret = read(data_socket, buffer, sizeof(buffer));
        if (ret == -1)
        {
            perror("Read Error");
            exit(EXIT_FAILURE);
        }

        buffer[sizeof(buffer) - 1] = 0;

        printf("Max index sent is  %s to CLIENT\n", buffer);
		
    }

    close(data_socket);

    exit(EXIT_SUCCESS);
}