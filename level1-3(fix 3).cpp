#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int ele;   //电梯所在楼层
int max = 4;   //电梯核载人数
int st[10], end[10];   //用户起始\目标楼层情况

void sort(int a[], int b[])
{
	for (int i = 0; i < 9; i++) {
		for (int j = 9; j > i; --j) {
			if (a[j] > a[j - 1]) {
				int m1 = a[j];
				a[j] = a[j - 1];
				a[j - 1] = m1;
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
	printf("请输入各用户起始楼层与终止楼层(输入T结束)：\n");
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
	int top = 99, btm = -99;   //top,btm标记电梯在哪一层转向
	printf("电梯的运行状况如下:\n");
	printf("楼层 人数 时间\n");
	printf("%d %d %d\n", ele, 0, 0);

	//电梯运行
	while (n1 > 0) {

		//向上(下)运行时确定top(btm)值
		if (dir == 1) {
			for (int i = 0; i < 10; i++) {
				if ((st[i] > 0) && ((st[i] > top) || (top == 99))) {
					top = st[i];
				}
				if ((st[i] == -1) && (end[i] > top)) {
					top = end[i];
				}
			}
		}
		else {
			for (int i = 0; i < 10; i++) {
				if ((st[i] > 0) && ((st[i] < btm) || (btm == -99))) {
					btm = st[i];
				}
				if ((st[i] == -1) && (end[i] > 0) && (end[i] < btm)) {
					btm = end[i];
				}
			}
		}

		//用户下梯
		for (int i = 0; i < 10; i++) {
			int dw = -1, f1 = 99;   //f1记录下梯用户索引
			if ((ele == end[i]) && (st[i] == -1) && (end[i] > 0)) {   //判断当前层有无用户需下梯
				dw = 1;
				f1 = i;
			}
			if (dw == 1) {
				n2--;
				end[f1] = -1;   //下梯标记
				printf("%d %d %d", ele, n2, t);
				printf("  有人下梯\n");
				n1--;
			}
		}

		//超载处理
		if (n2 == max) {
			if (((ele == top) && (dir == 1)) || ((ele == btm) && (dir == -1))) {
				dir = -dir;
			}
			ele += dir;
			t++;
			continue;
		}

		//用户上梯
		for (int i = 0; i < 10; i++) {
			int up = -1, f2 = 99;
			if ((ele == st[i]) && (end[i] != -1)) {
				up = 1;
				f2 = i;
			}
			if (up == 1) {
				n2++;
				st[f2] = -1;
				printf("%d %d %d", ele, n2, t);
				printf("  有人上梯\n");
			}
		}


		//电梯转向
		if (((ele == top) && (dir == 1)) || ((ele == btm) && (dir == -1))) {
			dir = -dir;
		}

		//继续运行
		ele += dir;
		t++;
	}
	return 0;
}