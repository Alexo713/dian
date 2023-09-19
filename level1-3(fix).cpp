#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int ele;   //电梯所在楼层
int st[10], end[10];   //用户起始\目标楼层情况

void sort(int a[], int b[])
{
	for (int i = 0; i < 9; i++) {
		for (int j = 9; j >i; --j) {
			if (a[j] > a[j - 1]) {
				int m1 = a[j];
				a[j] = a[j - 1];
				a[j - 1] =m1 ;
				int m2 = b[j];
				b[j] = b[j - 1];
				b[j - 1] = m2;
			}
		}
	}
}

int main()
{

	//数据输入
	printf("请输入电梯所在楼层：\n");
	scanf("%d", &ele);
	printf("请输入各用户起始楼层与终止楼层(输入T结束）：\n");
	int n1 = -1;    //n1统计用户总人数
	for (int i = 0; i < 10; i++) {
		char x = getchar();
		if (x == 'T') {
			break;   //手动输入"T"时停止输入
		}
		scanf("%d %d", &st[i], &end[i]);
		n1++;
	}
	sort(st, end);   //按起始楼层从高到低排序


    //变量初始化   
	int t = 0, n2 = 0;   //t记录时间，n2记录电梯内人数
	int dir;
	st[0] > ele ? dir = 1 : dir = -1;   //判断电梯的初始运行方向
	int top = -99;   //top标记电梯在哪一层转向
	printf("电梯的运行状况如下:\n");
	printf("楼层 人数 时间\n");
	printf("%d %d %d\n", ele, 0, 0);
	
	//电梯运行
	while (n1 > -1) {
	    
		//确定top值
		for (int i = 0; i < 10; i++) {
			if ((st[i] > 0) && ((st[i] * dir > top * dir)||(top == -99))) {
				top = st[i];
			}
		}
		
		//用户下梯
		int dw = -1, f2 = 99;
		for (int i = 0; i < 10; i++) {
			if ((ele == end[i]) && (st[i] == -1)) {
				dw = 1;
				f2 = i;
			}
		}
		if (dw == 1) {
			n2--;
			end[f2] = -1;   //下梯标记
			printf("%d %d %d", ele, n2, t);
			printf("  有人下梯\n");
			n1--;
		}
		
		//用户上梯
		int up = -1, f1 = 99;   //f1记录上梯用户索引
		for (int i = 0; i < 10; i++) {   //判断当前层有无用户需上梯
			if (ele == st[i]) {
				up = 1;
				f1 = i;
			}
		}
		if (up == 1) {
			st[f1] = -1;   //上梯标记
			n2++;
			if (end[f1] * dir > top * dir) {
				top = end[f1];   //若该用户目标楼层超出top，则将top值更新
			}
			printf("%d %d %d", ele, n2, t);
			printf("  有人上梯\n");
		}
		
		//电梯转向
		if (ele == top) {
			dir = -dir;
		}

		//继续运行
		ele += dir;
		t++;
	}
	return 0;
}