#include<stdio.h>
int substitute(int);
void printbits(unsigned char);
int main()
{ 
    int a=0;
    scanf("%d", &a);
    printf("Pre: %d  Post: %d\n",a, substitute(a));
    return 0;
}
int substitute(int a)
{ 
    int i;
    for(i=0; i < 15; i++)
        if(a==i) 
            return ++a;
       
    if(a==15)
        return 0;
} 
