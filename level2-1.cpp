#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int ele;   //��������¥��
int max = 4;   //���ݺ�������
int stz[10], st[10], endz[10], end[10], time[10];   //�û���ʼ¥�㡢Ŀ��¥�������ʱ��(��׺z��ʾ�ݴ�)

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

	//��������
	printf("�������������¥�㣺\n");
	scanf("%d", &ele);
	printf("��������û���ʼ¥�㡢��ֹ¥�������ʱ��(����T����)��\n");
	int n1 = -1;    //n1ͳ���û�������
	for (int i = 0; i < 10; i++) {
		char x = getchar();
		if (x == 'T') {
			break;   //�ֶ�����"T"ʱֹͣ����
		}
		scanf("%d %d %d", &stz[i], &endz[i],&time[i]);
		n1++;
	}

	//������ʼ��   
	int t = 0, n2 = 0;   //t��¼ʱ�䣬n2��¼����������
	int dir, fir = time[0];
	for (int i = 1; i < 10; i++) {
		if (time[i] < fir) {   //������һ�����е��û�
			fir = time[i];
			st[0] = stz[i]; 
			end[0] = endz[i];
		}
	}
	if (fir > 0) {
		for (int i = 0; i < 10; i++) {
			time[i] -= fir;   //���������ʱ�����0�������к���ʱ����ǰ��
		}
	}
	st[0] > ele ? dir = 1 : dir = -1;   //�жϵ��ݵĳ�ʼ���з���
	int top = 99, btm = -99;   //top,btm��ǵ�������һ��ת��
	printf("���ݵ�����״������:\n");
	printf("¥�� ���� ʱ��\n");
	printf("%d %d %d\n", ele, 0, 0);

	//��������
	while (n1 > 0) {

		//�º��д���
		for (int i = 0; i < 10; i++) {
			if (time[i] == t) {
				st[9] = stz[i];
				end[9] = endz[i];
				sort(st, end);
			}
		}

		//�޺���ʱ��ͣ
		if (n2 == 0) {
			int run = -1;
			for (int i = 0; i < 10; i++) {
				if ((st[i] > 0) || (end[i] > 0)) {
					run = 1;
				}
			}
			if (run == -1) {
				t++;
				continue;
			}
		}

		//����(��)����ʱȷ��top(btm)ֵ
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

		//�û�����
		for (int i = 0; i < 10; i++) {
			int dw = -1, f1 = 99;   //f1��¼�����û�����
			if ((ele == end[i]) && (st[i] == -1) && (end[i] > 0)) {   //�жϵ�ǰ�������û�������
				dw = 1;
				f1 = i;
			}
			if (dw == 1) {
				n2--;
				end[f1] = -1;   //���ݱ��
				printf("%d %d %d", ele, n2, t);
				printf("  ��������\n");
				n1--;
			}
		}

		//���ش���
		if (n2 == max) {
			if (((ele == top) && (dir == 1)) || ((ele == btm) && (dir == -1))) {
				dir = -dir;
			}
			ele += dir;
			t++;
			continue;
		}

		//�û�����
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
				printf("  ��������\n");
			}
		}

		//����ת��
		if (((ele == top) && (dir == 1)) || ((ele == btm) && (dir == -1))) {
			dir = -dir;
		}

		//��������
		ele += dir;
		t++;
	}
	return 0;
}