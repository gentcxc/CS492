#include<stdio.h>
int substitute(int);
int main()
{
    for(int i =0; i<16;i++)
    {
        printf("Pre Encryption: ");
        printf("%d , ",i);
        printf("Post Encryption:  ");
        printf("%d , ",substitute(i));
        printf("\n");
    }
    return 0;
}
int substitute(int a)
{    return ((a ^ 5) << 1); } 
