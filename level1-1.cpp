#include<stdio.h>
#include<math.h>
#define _CRT_SECURE_NO_WARNINGS



int st, end, ele;   //起始楼层，去往楼层,电梯所在楼层
int main()
{
	scanf_s("%d %d %d", &st, &ele, &end);
	if (st > 0 && st < 11 && ele>0 && ele < 11 && end>0 && end < 11)
	{
		printf("%d %d %d\n", ele, 0, 0);
		int t1 = abs(st - ele);
		printf("%d %d %d\n", st, t1, 1);
		ele = st;
		int t2 = t1 + abs(ele - end);
		printf("%d %d %d", end, t2, 0);
		return 0;
	}
	else
	{
		printf("输入楼层无效");
		return 0;
	}
}