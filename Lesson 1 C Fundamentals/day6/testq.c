#include <stdio.h>
void babuer(int *pa ,int sz)
{
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz - i -1; j++)
        {
            int x;
            if (pa[j]>pa[j+1])
            {
                x=pa[j];
                pa[j]=pa[j+1];
                pa[j+1]=x;
            }
            
        }0
        
    }
    for (int y = 0; y < sz; y++)
    {
        printf("%d ",pa[y]);
    }
}
int main(int argc, char const *argv[])
{
    int arr[] = {10,8,4,3,7,1,5,6,2,9,7};
    int sz = sizeof(arr)/sizeof(arr[0]);
    babuer(arr,sz);
    return 0;
}
