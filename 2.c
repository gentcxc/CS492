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
    int a=32123, b=409487629;
    printf("Plaintext: (16bit) a = 0x%x , (32 bit) b = 0x%x \n",a,b);
    printf("ECB Encryption: a = 0x%x , b = 0x%x \n", ecbEncrypt(a), ecbEncrypt(b));
    int ctra = ctrEncrypt(34952, a), ctrb = ctrEncrypt(34952, b);
    printf("CTR Encryption: IV: 0x%x, a = 0x%x, b = 0x%x \n", 34952,ctra,ctrb);
    int cbca= cbcEncrypt(14,a),cbcb=cbcEncrypt(14,b);
    printf("CBC Encryption: IV: 0x%x  , a = 0x%x, b = 0x%x \n",14, cbca,cbcb);
    return 0;
}
uint8_t substitute(uint8_t a)
{ 
    if( a > 15)
    {
        printf("Number over 4 bits\n");
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
    int final,f1,f2,f3,f4,f5,f6,f7,f8,t1,t2,t3,t4,t5,t6,t7,t8; //f is for field, t is permutation of x
    if(x<65536)
    {
        t1 = 0x0f & x;
        t2 = 0x0f & x>>4;
        t3 = 0x0f & x>>8;
        t4 = 0x0f & x>>12; 
        f4 = (iv ^t4 );    //step 1, take IV to start and xor it with p, 4 rightmost bits
        f4 = substitute(f4);
        f3 = f4 ^ t3;
        f3= substitute(f3);
        f2 = f3 ^ t2; 
        f2 = substitute(f2);
        f1 = f2 ^ t1;
        f1 = substitute(f1);
        return final = f1 | f2<<4 | f3<<8 | f4<<12; 
    }
    else if(x<4294967296)
    {
        t1 = 0x0f & x;           //match f's and t's, should have been  done prior.
        t2 = 0x0f & x>>4;
        t3 = 0x0f & x>>8;
        t4 = 0x0f & x>>12; 
        t5 = 0x0f & x>>16;           
        t6 = 0x0f & x>>20;
        t7 = 0x0f & x>>24;
        t8 = 0x0f & x>>28; 
        
        f8 = t8 ^ iv;
        f8 = substitute(f8);
        f7 = substitute(f8 ^ t7);
        f6 = substitute(f7 ^ t6);
        f5 = substitute(f6 ^ t5);
        f4 = substitute(f5 ^ t4);
        f3 = substitute(f4 ^ t3);
        f2 = substitute(f3 ^ t2);
        f1 = substitute(f2 ^ t1);
        return f1 | f2 <<4 | f3 << 8 | f4 << 12 | f5 << 16 | f6 << 20 | f7 << 24 | f8 << 28;
    }
}
