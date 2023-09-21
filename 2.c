#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
uint8_t substitute(uint8_t);
int ecbEncrypt(int);
int ctrEncrypt(int, int);
int cbcEncrypt(int, int);
void printbits(unsigned char);
int main()
{ 
    int a;
    scanf("%d", &a);
    printf("Pre: %d  Post: %d\n",a, substitute(a));
    printf("\n%d\n", ecbEncrypt(a));
    printf("\n%d\n", ctrEncrypt(34952, a));
    return 0;
}
uint8_t substitute(uint8_t a)
{ 
    if( a > 15)
    {
        printf("Number over 4 bits");
        return 0;
    }
    int i;
    for(i=0; i < 15; i++)
        if(a==i) 
            return ++a;
    if(a==15)
        return 0;
}
int ecbEncrypt(int x)
{
    uint32_t l4mask = 0x0f;
    int final;
    uint8_t t1=0,t2=0,t3=0,t4=0,t5,t6,t7,t8;
    if(x < 16) 
        return substitute(x);
    else if (x < 256)
    {
        t2=x>>4;
        t1=l4mask & x;
        final = substitute(t1) | substitute(t2) << 4;
        return final;
    }
    else if(x<65536)
    {
        t1=l4mask & x;
        t2 = l4mask & x >> 4;
        t3 = l4mask & x >> 8;
        t4 = l4mask & x >> 12;
        final = substitute(t1) | substitute(t2) << 4 | substitute(t3) << 8 | substitute(t4) << 12;
        return final;
    }
    else if(x<4294967296)
    {
        t1=l4mask & x;
        t2 = l4mask & x >> 4;
        t3 = l4mask & x >> 8;
        t4 = l4mask & x >> 12;
        t5 = l4mask & x >> 16;
        t6 = l4mask & x >> 20;
        t7 = l4mask & x >> 24;
        t8 = l4mask & x >> 28;
        final = substitute(t1) | substitute(t2) << 4 | substitute(t3) << 8 | substitute(t4) << 12 |
            substitute(t5) << 16 | substitute(t6) << 20 | substitute(t7) <<24 | substitute(t8) << 28;
        return final;
    }
}
int ctrEncrypt(int iv, int x)
{
    int e;
    e =  ecbEncrypt(iv);
    return e ^ x;
}
int cbcEncrypt(int iv, int x)
{
    int middle;
    middle = 0x0f & (iv ^ x);    //step 1, take IV to start and xor it with p, 4 rightmost bits
    


}
void printbits(unsigned char v) 
{
    int i;
    for(i = 7; i >= 0; i--) putchar('0' + ((v >> i) & 1));
}
