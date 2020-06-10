// sorting_project.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
// ���α׷� ����: <Ctrl+F5> �Ǵ� [�����] > [��������� �ʰ� ����] �޴�
// ���α׷� �����: <F5> Ű �Ǵ� [�����] > [����� ����] �޴�

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	NUMOFNUMBERS	500000		// 5����, 7.5����, 10����, 12.5����, ..., 50�������� ������Ű�� �ð� ������ ��

long randNumbers[NUMOFNUMBERS];

// selection sort�� ���� �Լ���
void selectionSort(long A[], long n);
long theLargest(long A[], long last);

int main(int argc, char* argv[])
{
	register long n, i;
	clock_t before;
	double elapsed_time;

	std::cout << "�˰����Թ� ���� ������Ʈ �����մϴ�.\n\n";

	srand((unsigned)time(NULL));

	before = clock();
	for (i = NUMOFNUMBERS - 1; i >= 0; i--) {
		n = rand();
		n += ((i + 1) / RAND_MAX) * RAND_MAX;
		randNumbers[NUMOFNUMBERS - 1 - i] = n;
	}
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// �� ������ ��� �ð��� ������.
	fprintf(stdout, "%d ���� ���� �ѹ� ������ �ɸ� �ð�(��): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	//std::cout << "������ ���� �Է� ���� ���:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
	//	printf("%ld ", randNumbers[i]);
	//printf("\n\n");

	// ���⿡ ���� ���� �˰����� �����ؼ� �����Ű�� �� ���� �ð��� ����մϴ�.
	// ��: Selection Sort�� ������ �����ϴ�.
	before = clock();
	selectionSort(randNumbers, NUMOFNUMBERS);

	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// �� ������ ��� �ð��� ������.
	fprintf(stdout, "%d ���� ���� �ѹ��� selection sort �ϴ� ���� �ɸ� �ð�(��): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	//std::cout << "���� ��� ���:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
	//	printf("%ld ", randNumbers[i]);
	//printf("\n\n");

	return 0;
}

void selectionSort(long A[], long n)
{
	int last, k, tmp;

	for (last = n - 1; last >= 1; last--) {
		k = theLargest(A, last);	// A[0...last] �� ���� ū �� A[k] ã��
		tmp = A[last]; //���� ū ���� �� ���� ��(�������� �����̹Ƿ�)
		A[last] = A[k];
		A[k] = tmp;
	}
}

long theLargest(long A[], long last)
{
	long largest, i;

	largest = 0;
	for (i = 1; i <= last; i++)
		if (A[i] > A[largest])  //������ �ϳ��� ���ذ��鼭 ���� ū ���� ã��
			largest = i;
	return largest;
}

