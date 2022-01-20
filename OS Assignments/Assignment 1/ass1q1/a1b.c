#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
int count=0;
int countA=0;
int countB=0;
double A1averageA=0;
double A2averageA=0;
double A3averageA=0;
double A4averageA=0;
double A5averageA=0;
double A6averageA=0;
double A1averageB=0;
double A2averageB=0;
double A3averageB=0;
double A4averageB=0;
double A5averageB=0;
double A6averageB=0;


void *computeAveragesA (void *args){
    int fo=open(args,O_RDONLY);
    if(fo==-1){
        printf("ERROR IN FILE NAME in section A,exiting the codeoverall averages will only show for B(if B works correcty),otherwsie NAN \n");
        printf("--------------------------------------------- \n");
        pthread_exit(NULL);
        // exit(0);
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
    }
    int j=1;
    i=0;
    while(j<k){
        char *token=strtok(entryPoint[j],",");
        char *section=strtok(NULL,",");
        if(strcmp(section,"A")==0){
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
        A1averageA= a1Average;
        double a2Average=(double)a2TotalMarks/count;
        A2averageA= a2Average;
        double a3Average=(double)a3TotalMarks/count;
        A3averageA= a3Average;
        double a4Average=(double)a4TotalMarks/count;
        A4averageA= a4Average;
        double a5Average=(double)a5TotalMarks/count;
        A5averageA= a5Average;
        double a6Average=(double)a6TotalMarks/count;
        A6averageA= a6Average;
        printf("Average marks in Assignment 1 by %s is %f \n","A",a1Average);
        printf("Average marks in Assignment 2 by %s is %f \n","A",a2Average);
        printf("Average marks in Assignment 3 by %s is %f \n","A",a3Average);
        printf("Average marks in Assignment 4 by %s is %f \n","A",a4Average);
        printf("Average marks in Assignment 5 by %s is %f \n","A",a5Average);
        printf("Average marks in Assignment 6 by %s is %f \n","A",a6Average);
        printf("--------------------------------------------- \n");
    // ((int)args) = count;
    countA = count;
    pthread_exit(NULL);

}

void *computeAveragesB (void *args){
    int fo=open(args,O_RDONLY);
    if(fo==-1){
        printf("ERROR IN FILE NAME in Section B,overall averages will only show for A(if A works correcty),otherwsie NAN \n");
        printf("--------------------------------------------- \n");
        pthread_exit(NULL);
        // exit(0);
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
    }
    int j=1;
    i=0;
    while(j<k){
        char *token=strtok(entryPoint[j],",");
        char *section=strtok(NULL,",");
        if(strcmp(section,"B")==0){
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
        A1averageB= a1Average;
        double a2Average=(double)a2TotalMarks/count;
        A2averageB= a2Average;
        double a3Average=(double)a3TotalMarks/count;
        A3averageB= a3Average;
        double a4Average=(double)a4TotalMarks/count;
        A4averageB= a4Average;
        double a5Average=(double)a5TotalMarks/count;
        A5averageB= a5Average;
        double a6Average=(double)a6TotalMarks/count;
        A6averageB= a6Average;
        printf("Average marks in Assignment 1 by %s is %f \n","B",a1Average);
        printf("Average marks in Assignment 2 by %s is %f \n","B",a2Average);
        printf("Average marks in Assignment 3 by %s is %f \n","B",a3Average);
        printf("Average marks in Assignment 4 by %s is %f \n","B",a4Average);
        printf("Average marks in Assignment 5 by %s is %f \n","B",a5Average);
        printf("Average marks in Assignment 6 by %s is %f \n","B",a6Average);
        printf("--------------------------------------------- \n");
    // ((int)args) = count;
    countB = count;
    pthread_exit(NULL);

}
int main(int argc, char const *argv[])
{   
    // int fo=open("student_record.csv",O_RDONLY);
    pthread_t tid1;
    pthread_t tid2;

    char fileName[100];
    printf("Enter the name of the file for which you need to compute average: ");
    scanf("%s",fileName);
    // printf("%s \n",fileName);
    int rA=pthread_create(&tid1,NULL,computeAveragesA,fileName);
    if(rA!=0){
        printf("There is an error");
        exit(0);
    }
    
    
    int cA=pthread_join(tid1,NULL);
    if (cA!=0){
        printf("There is an error");
        exit(0);
    }
    
    int rB=pthread_create(&tid2,NULL,computeAveragesB,fileName);
    if(rB!=0){
        printf("There is an error");
        exit(0);
    }
    
    int cB=pthread_join(tid2,NULL);
    if (cB!=0){
        printf("There is an error");
        exit(0);
    }
    int countTotal=countA+countB;
    double avgA1= ((countA*A1averageA) + (countB*A1averageB))/countTotal;
    double avgA2= ((countA*A2averageA) + (countB*A2averageB))/countTotal;
    double avgA3= ((countA*A3averageA) + (countB*A3averageB))/countTotal;
    double avgA4= ((countA*A4averageA) + (countB*A4averageB))/countTotal;
    double avgA5= ((countA*A5averageA) + (countB*A5averageB))/countTotal;
    double avgA6= ((countA*A6averageA) + (countB*A6averageB))/countTotal;
    printf("Average for assignment 1 across A and B: %f\n",avgA1);
    printf("Average for assignment 2 across A and B: %f\n",avgA2);
    printf("Average for assignment 3 across A and B: %f\n",avgA3);
    printf("Average for assignment 4 across A and B: %f\n",avgA4);
    printf("Average for assignment 5 across A and B: %f\n",avgA5);
    printf("Average for assignment 6 across A and B: %f\n",avgA6);
    return 0;
}