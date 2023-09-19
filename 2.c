#include<stdio.h>
int substitute(int);
void printbits(unsigned char);
int main()
{
    for(int i =0; i<16;i++)
    {
        printf("Pre Encryption: ");
        printf("%d , ",i);
        printf("Post Encryption:  ");
        printf("%d , ",substitute(i));
        printbits(i);
        printf(" --> ");
        printbits(substitute(i));
        printf("\n");
    }
    return 0;
}
int substitute(int a)
{    return ((a ^ 5) <<< 1); } 
void printbits(unsigned char v) 
{
    for(int i = 7; i >= 0; i--) putchar('0' + ((v >> i) & 1));
}
