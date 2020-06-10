#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	 NUMOFNUMBERS		500000	// 5만개, 7.5만개, 10만개, 12.5만개, ..., 50만개까지 증가시키며 시간 측정할 것
#define  COUNTINGNUMBER  10000
// n은 -COUNTINGNUMBER~COUNTINGNUMBER 값 사이에 있어야 countingSort 를 쓸 수 있음 
 //COUNTINGNUMBER는 A[]의 원소가 등장하는 횟수


long *randNumbers = (long*)malloc(sizeof(long)* NUMOFNUMBERS);
long resultNumber[NUMOFNUMBERS];


void countingSort(long A[], long B[], long n); 

int main(int argc, char* argv[])
{
	register long n, i;
	clock_t before;
	double elapsed_time;

	std::cout << "알고리즘입문 소팅 프로젝트 시작합니다.\n\n";

	srand((unsigned)time(NULL));

	before = clock();
	//k값 범위 이내여야하므로, 10000개로 잡겠습니다.
	//for (i = NUMOFNUMBERS - 1; i >= 0; i--) {
	for (i = NUMOFNUMBERS - 1; i >= 0; i--) {
		n = rand()%COUNTINGNUMBER; // n은 -k~k 값 사이에 있어야 countingSort 를 쓸 수 있음 
		n += ((i + 1) / RAND_MAX) * RAND_MAX;  
		if (n > COUNTINGNUMBER)
			n = rand() % COUNTINGNUMBER;
	
		//n은 COUNTINGNUMBER 범위 내에 있어야 하므로 조건을 변경하였습니다.
		
		randNumbers[NUMOFNUMBERS - 1 - i] = n;
	}
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
	fprintf(stdout, "%d 개의 랜덤 넘버 생성에 걸린 시간(초): %10.2f\n\n", NUMOFNUMBERS, elapsed_time);


	//후에 지우고 실행할 것
	//std::cout << "정렬전 숫자 입력 값들 출력:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
		//std::cout << randNumbers[i]<<"\n\n";

	// 여기에 각종 정렬 알고리즘을 구현해서 실행시키고 그 실행 시간을 출력합니다.
	before = clock();
	countingSort(randNumbers, resultNumber, NUMOFNUMBERS);
	
	std::cout << "countingSort실행";
	elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
	std::cout << "   COUNTINGNUMBER은" << COUNTINGNUMBER << "\n";
	fprintf(stdout, "%d 개의 랜덤 넘버를 count sort 하는 데에 걸린 시간(초): %10.3f\n\n", NUMOFNUMBERS, elapsed_time); //countingsort의 수행시간이 너무 빨라서 더 세밀한 단위로 나타내도록 하였습니다.

	//std::cout << "정렬 결과 출력:\n\n";
	//for (i = 0; i < NUMOFNUMBERS; i++)
		//std::cout << resultNumber[i]<< "\n\n";

	return 0;
}

void countingSort(long A[], long B[], long n)
{
	//B배열 초기화
	for (int i = 0; i < n; i++)
		B[i] = 0;

	long *C = (long*)malloc(sizeof(long)* COUNTINGNUMBER);
	for (int i = 0; i < COUNTINGNUMBER; i++)
		C[i] = 0; //C배열을 초기화함

	for (int j = 0; j < n; j++)
		C[A[j]]++;  //A[j]를 index로 설정 


	for (int i = 1; i < COUNTINGNUMBER; i++)
		C[i] = C[i] + C[i - 1]; //C[i]에는 누적횟수가 저장됨(i의 값이 몇번 나왔는 지 그 횟수+ i보다 작은 값이 등장한 횟수)-> 결과: i값의 자리 결정
		// i보다 큰 값      {     i(i의 횟수=i의 갯수이므로, i의 횟수만큼 들어감)    }    i보다 작은 값들 <-이런 식으로 들어감
		//이 시점에서 C[i] : i보다 작거나 같은 원소의 총수


	for (int j = n-1; j >= 0; j--)
	{
		B[C[A[j]]-1] = A[j]; //B[C[A[j]]] : B배열의 j보다 작은 원소들의 총개수 ---> 배열의 뒤부터 채워줌(결과배열은 오름차순정렬이므로, 현재는 내림차순 정렬이므로)
		//B[C[A[j]]-1] 인 이유: C[]가 0부터 시작인데, 위의 루프에서는 1부터 시작하였으므로, C[0]값이 출력이 안됨, 결과적으로 값이 하나씩 누락됨
		//=> 해결: 정렬된 값들을 한 칸씩 이동시켜서 저장함-> 값 손실 잃어나지 않고 제대로 정렬됨
		C[A[j]]--; //자신의 개수를 빼줌(A[j]에는 j보다 작은 원소개수 뿐아니라 j의 개수도 들어있으므로)
		
	}

	free(C);
	free(randNumbers);
}