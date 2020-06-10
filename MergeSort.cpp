#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	 NUMOFNUMBERS	500000		// 5만개, 7.5만개, 10만개, 12.5만개, ..., 50만개까지 증가시키며 시간 측정할 것

long randNumbers[NUMOFNUMBERS];

// selection sort를 위한 함수들
void selectionSort(long A[], long n);
long theLargest(long A[], long last);

void mergeSort(long A[], long p, long q); //p,q크므로 long type
void merge(long A[], long p, long q, long r);


int main(int argc, char* argv[])
{
	register long n, i;
	clock_t before;
	double elapsed_time;

	std::cout << "알고리즘입문 소팅 프로젝트 시작합니다.\n\n";

	srand((unsigned)time(NULL));

	before = clock();
	for (i = NUMOFNUMBERS - 1; i >= 0; i--) {
		n = rand();
		n += ((i + 1) / RAND_MAX) * RAND_MAX;
		randNumbers[NUMOFNUMBERS - 1 - i] = n;
	}
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
	fprintf(stdout, "%d 개의 랜덤 넘버 생성에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);


	// 여기에 각종 정렬 알고리즘을 구현해서 실행시키고 그 실행 시간을 출력합니다.
	// 예: Selection Sort는 다음과 같습니다.
	before = clock();
	//selectionSort(randNumbers, NUMOFNUMBERS);
	mergeSort(randNumbers, 0,  NUMOFNUMBERS);
	std::cout << "mergeSort실행";
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
	fprintf(stdout, "%d 개의 랜덤 넘버를 merge sort 하는 데에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	return 0;
}

void mergeSort(long A[], long p, long r)
{
	
	//입력을 반으로 나누기
	//전반부와 후반부를 독립적으로 정렬
	//병합
	
	if (p < r)
	{
		
		long q = 0;
		q = ((p+r)-(p + r) % 2)/2; //몫만 구해서(배열은 정수이므로) 두  배열을 분할한다.
		

		//전반부 정렬
		mergeSort(A, p, q);
		//후반부 정렬
		mergeSort(A, q+1, r);
		//병합
		merge(A,p,q,r);
	}

}

//마지막에 두 정렬을 합치는 함수 
void merge(long A[], long p, long q, long r)
{
	
	int i = 0, j = 0, t =0;
	i = p, j = q + 1;
	//tmp배열 : 정렬을 한 숫자를 임시로 둘 배열
	//tmp 동적배열하기
	int x = (r-q+1)*2 ; //
	long *tmp = (long*)malloc(sizeof(long) * x); //동적으로 필요한 만큼만 할당

	while (i <= q && j < r) {
		if (A[i] <= A[j]) //i는 분할된 배열(전반부)의 첫번째 원소, j는 분할된 배열(후반부)의 첫번째 원소
			//각각의 배열의 첫 원소의 크기를 비교, 둘 중 더 작은 수를 tmp 배열에 넣음(오름차순이므로 작은 값이 배열의 앞쪽으로 정렬)
			tmp[t++] = A[i++]; //i배열(전반부배열)의 수가 더 작은 경우 i를 tmp에 넣고, t와 i를 1씩 증가시켜줌(다음 원소로 넘어감)
		else 
			tmp[t++] = A[j++]; //j배열(후반부배열)의 수가 더 작은 경우 j를 tmp에 넣고, t와 j를 1씩 증가시켜줌(다음원소로 넘어감)
		
	}

	while (i <= q) //j>r인데, i<=q인 경우 즉, j배열(후반부배열)은 원소가 남아있지 않았는데, i배열(전반부배열)은 원소가 남아있는 상태
		tmp[t++] = A[i++]; //i배열의 원소를 tmp에 넣어준다(while문 반복하면서 남은 i배열(전반부배열)이 tmp에 다 들어가게 됨

	while (j < r) //i>q인데, j<r인 경우 즉, i배열(전반부배열)은 원소가 남아있지 않았는데, j배열(후반부배열)은 원소가 남아있는 상태
		tmp[t++] = A[j++];  //j배열의 원소를 tmp에 넣어준다(while문 반복하면서 남은 j배열(후반부배열)이 tmp에 다 들어가게 됨


	i = p;  t = 0;
	while (i <= r) //i가 r까지 간 경우 즉, 끝까지 정렬했을 때, 마지막 원소까지 정렬이 되었을 때, 결과를 A[]에 저장
		A[i++] = tmp[t++];
	
	free(tmp);
	
}

//SelectionSort는 이미 주신 함수였으므로, 프로젝트 파일을 첨부하는 대신 MergeSort에 같이 넣어 제출합니다. 
//함수 실행하고 싶은 경우, main에서 함수 호출할 것(주석처리 해둠)

void selectionSort(long A[], long n)
{
	int last, k, tmp;

	for (last = n - 1; last >= 1; last--) {
		k = theLargest(A, last);	// A[0...last] 중 가장 큰 수 A[k] 찾기
		tmp = A[last]; //가장 큰 수를 맨 끝에 둠(오름차순 정렬이므로)
		A[last] = A[k];
		A[k] = tmp;
	}
}

long theLargest(long A[], long last)
{
	long largest, i;

	largest = 0;
	for (i = 1; i <= last; i++)
		if (A[i] > A[largest])  //값들을 하나씩 비교해가면서 제일 큰 값을 찾음
			largest = i;
	return largest;
}

