/*!
 * \file 二分查找和黄金查找.cpp
 *
 * \author ranjiewen
 * \date 三月 2017
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXLength 10000000

struct Node {
	int Element[MAXLength];
	int Length;
};
typedef struct Node *List;

clock_t start1, stop1, start2, stop2;
double duration;

int BinarySearch(List Tbl, int K);
int GoldenSearch(List Tbl, int K);

int main()
{
	int i, j, result;
	List Tbl = (List)malloc(sizeof(struct Node));
	Tbl->Length = MAXLength - 1;
	for (i = 0; i < MAXLength; i++){
		Tbl->Element[i] = i;
	}

	start1 = clock();
	for (j = 1; j <= MAXLength - 1; j++){
		result = BinarySearch(Tbl, j);
	}
	stop1 = clock();
	duration = ((double)(stop1 - start1)) / CLK_TCK / (MAXLength - 1);
	printf("Duration of BinarySearch is %6.2es.\n", duration);

	start2 = clock();
	for (j = 1; j <= MAXLength - 1; j++){
		result = GoldenSearch(Tbl, j);
	}
	stop2 = clock();
	duration = ((double)(stop2 - start2)) / CLK_TCK / (MAXLength - 1);
	printf("Duration of GoldenSearch is %6.2es.\n", duration);
	return 0;
}

int GoldenSearch(List Tbl, int K){
	int left, right, mid, NoFound = -1;
	left = 1;
	right = Tbl->Length;
	while (left <= right){
		mid = left + 0.618*(right - left);
		if (K<Tbl->Element[mid]) right = mid - 1;
		else if (K>Tbl->Element[mid]) left = mid + 1;
		else return mid;
	}
	return NoFound;
}
int BinarySearch(List Tbl, int K){
	int left, right, mid, NoFound = -1;
	left = 1;
	right = Tbl->Length;
	while (left <= right){
		mid = (left + right) / 2;
		if (K<Tbl->Element[mid]) right = mid - 1;
		else if (K>Tbl->Element[mid]) left = mid + 1;
		else return mid;
	}
	return NoFound;
}
