#include<stdint.h>
#include<stdio.h>
#include "c.c"

extern void b(int64_t x);
void a(){
    printf("In function A right now \n\n");
    int64_t num;
    printf("Enter the 64 bit number:");
    scanf("%lld",&num);
    printf("\n");
    b(num);
}
int main(int argc, char const *argv[])
{
    a();
    return 0;
}
