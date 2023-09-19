#include<stdio.h>
int* substitute(int*);
int main()
{
    int x[] ={1,0,1,0};
    int *a = x;
    printf("Pre Encryption: ");
    for(int i=0; i<4; i++)
          printf("%d", a[i]);
    printf("\n");

    substitute(a);
    printf("Post Encryption: ");
    for(int i=0; i<4; i++)
        printf("%d", a[i]);
    printf("\n");
    return 0;
}
int* substitute(int *a)
{
    if( a[0]==0 && a[1] == 0 && a[2] ==0 && a[3] == 0)
        a[0]=1;
    else
    {
    int *x =a;
      a[0] = x[1];
      a[1] = x[2];
      a[2] = x[3];   
      a[3] = 0;
     }
    return a;
}


