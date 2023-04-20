#include<stdio.h>
void arr_printf(int (*p)[3],int n)
{
	
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<3;j++){
			printf("%d ",p[i][j]);
		}
		puts("");
	}
}
int main()
{
	int a[2][3]={{1,2,3},{4,5,6}};
	int n=2;
	arr_printf(a,2);
	return 0;
}
//二维数组指针指向了二维数组，此时指针当成二维数组去使用
//[]的优先级比*高，（）的优先级最高，int (*p)[列数]
