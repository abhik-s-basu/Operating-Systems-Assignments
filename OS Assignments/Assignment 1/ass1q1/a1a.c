#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

void computeAverages (char *fileName, char *sec){
    int fo=open(fileName,O_RDONLY);
    // char *buffer=(char*)malloc(100*sizeof(char));
    if(fo==-1){
        printf("Error in reading file. \n");
        exit(0);
    }
    int count=0;
    int a1TotalMarks=0;
    int a2TotalMarks=0;
    int a3TotalMarks=0;
    int a4TotalMarks=0;
    int a5TotalMarks=0;
    int a6TotalMarks=0;
    char entryPoint[1000][1000];
    char buffer;
    int i=0;
    int k=0;
    while(read(fo,&buffer,1)){
        if (buffer=='\n'){
            strcat(entryPoint[k],"\0");
            k++;
            i=0;
        }
        entryPoint[k][i++]=buffer;
        // printf("%s\n",entryPoint[k]);
    }
    // for (int z=0;z<k;z++){
    //     printf("%s\n",entryPoint[z]);
    // }
        // char *curr=strdup(entryPoint);
    int j=1;
    i=0;
    while(j<k){
        char *token=strtok(entryPoint[j],",");
        char *section=strtok(NULL,",");
        if(strcmp(section,sec)==0){
        char *a1 = strtok(NULL,",");
        a1TotalMarks +=atoi(a1);
        char *a2 = strtok(NULL,",");
        a2TotalMarks +=atoi(a2);
        char *a3 = strtok(NULL,",");
        a3TotalMarks +=atoi(a3);
        char *a4 = strtok(NULL,",");
        a4TotalMarks +=atoi(a4);
        char *a5 = strtok(NULL,",");
        a5TotalMarks +=atoi(a5);
        char *a6 = strtok(NULL,"\n");
        a6TotalMarks +=atoi(a6);
        // printf("Marks scored by  %s is  %d %d %d %d %d %d \n",token,atoi(a1),atoi(a2),atoi(a3),atoi(a4),atoi(a5),atoi(a6));
        count++;
    }
        j++;  
}
        double a1Average=(double)a1TotalMarks/count;
        double a2Average=(double)a2TotalMarks/count;
        double a3Average=(double)a3TotalMarks/count;
        double a4Average=(double)a4TotalMarks/count;
        double a5Average=(double)a5TotalMarks/count;
        double a6Average=(double)a6TotalMarks/count;
        printf("Average marks in Assignment 1 by %s is %f \n",sec,a1Average);
        printf("Average marks in Assignment 2 by %s is %f \n",sec,a2Average);
        printf("Average marks in Assignment 3 by %s is %f \n",sec,a3Average);
        printf("Average marks in Assignment 4 by %s is %f \n",sec,a4Average);
        printf("Average marks in Assignment 5 by %s is %f \n",sec,a5Average);
        printf("Average marks in Assignment 6 by %s is %f \n",sec,a6Average);
        close(fo);
}

int main(int argc, char *argv[]) {
    char fileName [100];
    printf("Enter the name of the file for which you need to compute average: ");
    scanf("%s",fileName);
    pid_t pid = fork();
    int status;
    if (pid == 0) { /* child process */
        //section a printing
        printf("--------------------------------------------------------\n");
        printf("Child process executed first with ID as %d. \n",getpid());
        printf("--------------------------------------------------------\n");
        computeAverages(fileName,"A");
        exit(0);
        
    }
    else if (pid==-1){
        printf("No child created \n");
        printf("The error is %d.\n",errno);
    }
    else { 
        waitpid(pid,&status,0);
        printf("--------------------------------------------------------\n");
        printf("Parent process executed second with ID as %d. \n",getpid());
        printf("--------------------------------------------------------\n");
        computeAverages(fileName,"B");//section B printing
    }
}