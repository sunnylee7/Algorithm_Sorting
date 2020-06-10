#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	 NUMOFNUMBERS		500000	// 5����, 7.5����, 10����, 12.5����, ..., 50�������� ������Ű�� �ð� ������ ��
#define  COUNTINGNUMBER  10000
// n�� -COUNTINGNUMBER~COUNTINGNUMBER �� ���̿� �־�� countingSort �� �� �� ���� 
 //COUNTINGNUMBER�� A[]�� ���Ұ� �����ϴ� Ƚ��


long *randNumbers = (long*)malloc(sizeof(long)* NUMOFNUMBERS);
long resultNumber[NUMOFNUMBERS];


void countingSort(long A[], long B[], long n); 

int main(int argc, char* argv[])
{
	register long n, i;
	clock_t before;
	double elapsed_time;

	std::cout << "�˰����Թ� ���� ������Ʈ �����մϴ�.\n\n";

	srand((unsigned)time(NULL));

	before = clock();
	//k�� ���� �̳������ϹǷ�, 10000���� ��ڽ��ϴ�.
	//for (i = NUMOFNUMBERS - 1; i >= 0; i--) {
	for (i = NUMOFNUMBERS - 1; i >= 0; i--) {
		n = rand()%COUNTINGNUMBER; // n�� -k~k �� ���̿� �־�� countingSort �� �� �� ���� 
		n += ((i + 1) / RAND_MAX) * RAND_MAX;  
		if (n > COUNTINGNUMBER)
			n = rand() % COUNTINGNUMBER;
	
		//n�� COUNTINGNUMBER ���� ���� �־�� �ϹǷ� ������ �����Ͽ����ϴ�.
		
		randNumbers[NUMOFNUMBERS - 1 - i] = n;
	}
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// �� ������ ��� �ð��� ������.
	fprintf(stdout, "%d ���� ���� �ѹ� ������ �ɸ� �ð�(��): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);


	//�Ŀ� ����� ������ ��
	//std::cout << "������ ���� �Է� ���� ���:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
		//std::cout << randNumbers[i]<<"\n\n";

	// ���⿡ ���� ���� �˰����� �����ؼ� �����Ű�� �� ���� �ð��� ����մϴ�.
	before = clock();
	countingSort(randNumbers, resultNumber, NUMOFNUMBERS);
	
	std::cout << "countingSort����";
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// �� ������ ��� �ð��� ������.
	std::cout << "   COUNTINGNUMBER��" << COUNTINGNUMBER << "\n";
	fprintf(stdout, "%d ���� ���� �ѹ��� count sort �ϴ� ���� �ɸ� �ð�(��): %10.3f\n\n", NUMOFNUMBERS, elapsed_time); //countingsort�� ����ð��� �ʹ� ���� �� ������ ������ ��Ÿ������ �Ͽ����ϴ�.

	//std::cout << "���� ��� ���:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
		//std::cout << resultNumber[i]<< "\n\n";

	return 0;
}

void countingSort(long A[], long B[], long n)
{
	//B�迭 �ʱ�ȭ
	for (int i = 0; i < n; i++)
		B[i] = 0;

	long *C = (long*)malloc(sizeof(long)* COUNTINGNUMBER);
	for (int i = 0; i < COUNTINGNUMBER; i++)
		C[i] = 0; //C�迭�� �ʱ�ȭ��

	for (int j = 0; j < n; j++)
		C[A[j]]++;  //A[j]�� index�� ���� 


	for (int i = 1; i < COUNTINGNUMBER; i++)
		C[i] = C[i] + C[i - 1]; //C[i]���� ����Ƚ���� �����(i�� ���� ��� ���Դ� �� �� Ƚ��+ i���� ���� ���� ������ Ƚ��)-> ���: i���� �ڸ� ����
		// i���� ū ��      {     i(i�� Ƚ��=i�� �����̹Ƿ�, i�� Ƚ����ŭ ��)    }    i���� ���� ���� <-�̷� ������ ��
		//�� �������� C[i] : i���� �۰ų� ���� ������ �Ѽ�


	for (int j = n-1; j >= 0; j--)
	{
		B[C[A[j]]-1] = A[j]; //B[C[A[j]]] : B�迭�� j���� ���� ���ҵ��� �Ѱ��� ---> �迭�� �ں��� ä����(����迭�� �������������̹Ƿ�, ����� �������� �����̹Ƿ�)
		//B[C[A[j]]-1] �� ����: C[]�� 0���� �����ε�, ���� ���������� 1���� �����Ͽ����Ƿ�, C[0]���� ����� �ȵ�, ��������� ���� �ϳ��� ������
		//=> �ذ�: ���ĵ� ������ �� ĭ�� �̵����Ѽ� ������-> �� �ս� �Ҿ�� �ʰ� ����� ���ĵ�
		C[A[j]]--; //�ڽ��� ������ ����(A[j]���� j���� ���� ���Ұ��� �Ӿƴ϶� j�� ������ ��������Ƿ�)
		
	}

	free(C);
	free(randNumbers);
}