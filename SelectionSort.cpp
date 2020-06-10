// sorting_project.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	NUMOFNUMBERS	500000		// 5만개, 7.5만개, 10만개, 12.5만개, ..., 50만개까지 증가시키며 시간 측정할 것

long randNumbers[NUMOFNUMBERS];

// selection sort를 위한 함수들
void selectionSort(long A[], long n);
long theLargest(long A[], long last);

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

	//std::cout << "정렬전 숫자 입력 값들 출력:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
	//	printf("%ld ", randNumbers[i]);
	//printf("\n\n");

	// 여기에 각종 정렬 알고리즘을 구현해서 실행시키고 그 실행 시간을 출력합니다.
	// 예: Selection Sort는 다음과 같습니다.
	before = clock();
	selectionSort(randNumbers, NUMOFNUMBERS);

	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
	fprintf(stdout, "%d 개의 랜덤 넘버를 selection sort 하는 데에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);

	//std::cout << "정렬 결과 출력:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
	//	printf("%ld ", randNumbers[i]);
	//printf("\n\n");

	return 0;
}

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

