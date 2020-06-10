#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	 NUMOFNUMBERS	500000		// 5����, 7.5����, 10����, 12.5����, ..., 50�������� ������Ű�� �ð� ������ ��

long randNumbers[NUMOFNUMBERS];

// selection sort�� ���� �Լ���
void selectionSort(long A[], long n);
long theLargest(long A[], long last);

void mergeSort(long A[], long p, long q); //p,qũ�Ƿ� long type
void merge(long A[], long p, long q, long r);


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


	// ���⿡ ���� ���� �˰����� �����ؼ� �����Ű�� �� ���� �ð��� ����մϴ�.
	// ��: Selection Sort�� ������ �����ϴ�.
	before = clock();
	//selectionSort(randNumbers, NUMOFNUMBERS);
	mergeSort(randNumbers, 0,  NUMOFNUMBERS);
	std::cout << "mergeSort����";
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// �� ������ ��� �ð��� ������.
	fprintf(stdout, "%d ���� ���� �ѹ��� merge sort �ϴ� ���� �ɸ� �ð�(��): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	return 0;
}

void mergeSort(long A[], long p, long r)
{
	
	//�Է��� ������ ������
	//���ݺο� �Ĺݺθ� ���������� ����
	//����
	
	if (p < r)
	{
		
		long q = 0;
		q = ((p+r)-(p + r) % 2)/2; //�� ���ؼ�(�迭�� �����̹Ƿ�) ��  �迭�� �����Ѵ�.
		

		//���ݺ� ����
		mergeSort(A, p, q);
		//�Ĺݺ� ����
		mergeSort(A, q+1, r);
		//����
		merge(A,p,q,r);
	}

}

//�������� �� ������ ��ġ�� �Լ� 
void merge(long A[], long p, long q, long r)
{
	
	int i = 0, j = 0, t =0;
	i = p, j = q + 1;
	//tmp�迭 : ������ �� ���ڸ� �ӽ÷� �� �迭
	//tmp �����迭�ϱ�
	int x = (r-q+1)*2 ; //
	long *tmp = (long*)malloc(sizeof(long) * x); //�������� �ʿ��� ��ŭ�� �Ҵ�

	while (i <= q && j < r) {
		if (A[i] <= A[j]) //i�� ���ҵ� �迭(���ݺ�)�� ù��° ����, j�� ���ҵ� �迭(�Ĺݺ�)�� ù��° ����
			//������ �迭�� ù ������ ũ�⸦ ��, �� �� �� ���� ���� tmp �迭�� ����(���������̹Ƿ� ���� ���� �迭�� �������� ����)
			tmp[t++] = A[i++]; //i�迭(���ݺι迭)�� ���� �� ���� ��� i�� tmp�� �ְ�, t�� i�� 1�� ����������(���� ���ҷ� �Ѿ)
		else 
			tmp[t++] = A[j++]; //j�迭(�Ĺݺι迭)�� ���� �� ���� ��� j�� tmp�� �ְ�, t�� j�� 1�� ����������(�������ҷ� �Ѿ)
		
	}

	while (i <= q) //j>r�ε�, i<=q�� ��� ��, j�迭(�Ĺݺι迭)�� ���Ұ� �������� �ʾҴµ�, i�迭(���ݺι迭)�� ���Ұ� �����ִ� ����
		tmp[t++] = A[i++]; //i�迭�� ���Ҹ� tmp�� �־��ش�(while�� �ݺ��ϸ鼭 ���� i�迭(���ݺι迭)�� tmp�� �� ���� ��

	while (j < r) //i>q�ε�, j<r�� ��� ��, i�迭(���ݺι迭)�� ���Ұ� �������� �ʾҴµ�, j�迭(�Ĺݺι迭)�� ���Ұ� �����ִ� ����
		tmp[t++] = A[j++];  //j�迭�� ���Ҹ� tmp�� �־��ش�(while�� �ݺ��ϸ鼭 ���� j�迭(�Ĺݺι迭)�� tmp�� �� ���� ��


	i = p;  t = 0;
	while (i <= r) //i�� r���� �� ��� ��, ������ �������� ��, ������ ���ұ��� ������ �Ǿ��� ��, ����� A[]�� ����
		A[i++] = tmp[t++];
	
	free(tmp);
	
}

//SelectionSort�� �̹� �ֽ� �Լ������Ƿ�, ������Ʈ ������ ÷���ϴ� ��� MergeSort�� ���� �־� �����մϴ�. 
//�Լ� �����ϰ� ���� ���, main���� �Լ� ȣ���� ��(�ּ�ó�� �ص�)

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

