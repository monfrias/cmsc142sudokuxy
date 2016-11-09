#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 4

/*
SIDE NOTE: BACKTRACKING NA LANG ANG KULANG MGA BESSIE <3
*/

void printArray(int arr[N][N]) {
	int i,j;
	for(i=0; i<N; i+=1) {
		for(j=0; j<N; j+=1) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int checkRow(int arr[N][N], int row, int num) {
	int col;
	for(col=0; col<N; col+=1) {
		if(arr[row][col] == num) {
			return 0;	//not valid
		}
	}
	return 1;	//valid
}

int checkCol(int arr[N][N], int col, int num) {
	int row;
	for(row=0; row<N; row+=1) {
		if(arr[row][col] == num) {
			return 0;	//not valid
		}
	}
	return 1;	//valid
}

int checkSubgrid(int arr[N][N], int subgridRow, int subGridCol, int num) {
	int row, col;
	for(row=0; row<sqrt(N); row+=1) {
		for(col=0; col<sqrt(N); col+=1) {
			if(arr[row+subgridRow][col+subGridCol] == num) {
				return 0;	//not valid
			}
		}
	}
	return 1;	//valid
}

int isValidToInsert(int arr[N][N], int row, int col, int num) {
	int subSize = (int) sqrt(N);
	return (checkRow(arr, row, num) && checkCol(arr, col, num) && checkSubgrid(arr, row-(row%subSize), col-(col%subSize), num));
	//returns 1 if it is valid to all conditions. 0 otherwise
}

int main() {
	int i, j, num;
	int arr[N][N] = {1,0,0,3,2,0,4,0,0,2,0,0,0,0,0,0};
	int hasValue[N][N];

	printArray(arr);
	
	for(i=0; i<N; i+=1) {	//initializes another array to check whether the initial puzzle has values
		for(j=0; j<N; j+=1) {
			if(arr[i][j] != 0) {
				hasValue[i][j] = 1;	//it has a value
			} else hasValue[i][j] = 0;	//it does not have a value
		}
	}

	for(i=0; i<N; i+=1) {
		for(j=0; j<N; j+=1) {
			if(!hasValue[i][j] == 1) {	//unassigned numbers, edit
				for(num=1; num<=N; num+=1) {
					if(isValidToInsert(arr, i, j, num)) {
						arr[i][j] = num;
						//valid, go insert
					} else {
						//not valid, do backtrack
						//Insert magic code for backtracking here
					}
				}
			} else {
				//assigned numbers, do not edit
			}
		}
	}

	printArray(arr);
	printArray(hasValue);
	return 0;
}


/* |========================= KEME CODES ========================|*/
	/*FILE *fp;

	fp = fopen("sudoku.txt", "r");
	if(fp == NULL) {
		printf("No file to read!\n");
	} else {
		fscanf(fp,"%d", &numberOfPuzzles);
		fscanf(fp, "%d", &subgridSize);
		arrSize = (2*subgridSize)*(2*subgridSize);
		arr = (int* ) malloc(sizeof(int ) * arrSize);
		for(i=0; i<arrSize; i+=1) {
			fscanf(fp, "%d", arr[i]);
		}
	}
	fclose(fp);*/