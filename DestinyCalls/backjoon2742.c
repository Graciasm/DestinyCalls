#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//n을 입력 받고, 세로로 n부터 1까지 출력하는 프로그램
int main()
{
	int n,i;
	scanf("%d", &n);
	for (i = n; i >= 1; i--)
	{
		printf("%d\n", i);
	}
	return 0;
}