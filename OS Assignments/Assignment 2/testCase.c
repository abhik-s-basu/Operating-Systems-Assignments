#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>

#define SYS_kernel_2d_memcpy 448

int main(int argc, char **argv)
{
    int r = 4;
    int c = 3;
    float mat1[4][3] = {{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0},{10.0,11.0,12.0}};
    float mat2[4][3] = {{12.0,11.0,10.0},{9.0,8.0,7.0},{6.0,5.0,4.0},{3.0,2.0,1.0}};

    printf("This is the initial mat:\n");

    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            printf("%lf ", mat2[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int res = syscall(SYS_kernel_2d_memcpy, &mat2, &mat1, 4, 3);

    if(res < 0){
        perror("ERROR! \n");
        exit(1);
    }

    printf("Printing after copying:\n");

    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            printf("%lf ", mat2[i][j]);
        }
        printf("\n");
    }

    return 0;
}