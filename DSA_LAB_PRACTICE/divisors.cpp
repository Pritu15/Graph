#include<stdio.h>
int main()
{
    int n,a;
    scanf("%d",&n);
   
        for(a=n;a>=1;a--)
        {
            if(a%n!=0)
            {
                printf("%d ",a);

            }
            
        }
   
    return 0;
}