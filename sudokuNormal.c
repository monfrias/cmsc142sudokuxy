#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 4

void printArray(int arr[][4], int size) {
	int i,j;
	for(i=0; i<size; i+=1) {
		for(j=0; j<size; j+=1) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int checkRow(int arr[][4], int row, int size, int num) {
	int col;
	for(col=0; col<size; col+=1) {
		if(arr[row][col] == num) {
			return 0;
		}
	}
	return 1;
}

int checkCol(int arr[][4], int col, int size, int num) {
	int row;
	for(row=0; row<size; row+=1) {
		if(arr[row][col] == num) {
			return 0;
		}
	}
	return 1;
}

int checkSubgrid(int arr[][4], int subgridRow, int subGridCol, int size, int num) {
	int row, col;
	for(row=0; row<sqrt(size); row+=1) {
		for(col=0; col<sqrt(size); col+=1) {
			if(arr[row+subgridRow][col+subGridCol] == num) {
				return 0;
			}
		}
	}
	return 1;
}

int isvalidInput(int arr[][4], int row, int col, int size, int num){
	int size2 = (int) sqrt(size);
	if(checkRow(arr,row,size,num) == 0)
		return 0;
	if(checkCol(arr,col,size,num) == 0)
		return 0;
	if(checkSubgrid(arr, row-row%(size2), col-col%(size2), size,num)==0)
		return 0;
	return 1;
}

int isValidSoln(int arr[][4], int size){
	int i,j;
	int checkerRow[size];
	int checkerCol[size];

	//initialize checkerArray
	for(i=0;i<size;i+=1){
		checkerRow[i]=0;
		checkerCol[i]=0;
	}

	for(i=0;i<size;i+=1){
		for(j=0;j<size;j+=1){
			if(arr[i][j] == 0)
				return 0;
		}
	}

	//check if there are no duplicates -> row
	for(i=0;i<size;i+=1){
		for(j=0;j<size;j+=1){
			checkerRow[j] +=1;
		}

		for(j=0;j<size;j+=1){
			if(checkerRow[j] != i+1)
				return 0;
		}
	}

	return 1;
}

int main(){
	int size = N;
	int numCells = (size*size)+2;
	int numOpts = size+2;
	int inputOpts[numCells][numOpts];
	int coords[numCells][2];
	int tos[numCells];
	int arr[N][N] = {1,0,0,3,2,0,4,0,0,2,0,0,0,0,0,0};
	int i,j;
	int start, move,num;
	int countValid = 0;

	start = 0;
	move = 0;

	tos[start] = 1;
	//setting up coords table
	for(i=0;i<size*size;i+=1){
		coords[i][0] = -1;
		coords[i][1] = -1;
	}

	//setting up the coords table
	for(i=0;i<size;i+=1){
		for(j=0;j<size;j+=1){
			inputOpts[i][j] = -1;
			if(arr[i][j] == 0){
				//printf("here\n");
				move += 1;
				coords[move][0] = i;
				coords[move][1] = j;
			}
		}
	}

	move = 0;
	while(tos[start]>0){
		if(tos[move]>0){
			if(inputOpts[move][tos[move]] != -1)
				arr[coords[move][0]][coords[move][1]] = inputOpts[move][tos[move]];

			//printArray(arr,size);

			move +=1;
			tos[move]=0;

			if(isValidSoln(arr,size) == 1){
				countValid+=1;
				printArray(arr,size);
			}else{
				//check of other possible answers
				//populating the stack with only possible answers per cell (puzzle)
				for(num=N; num>=1; num-=1) {
					if(coords[move][0] != -1) {
						if(isvalidInput(arr,coords[move][0],coords[move][1],size,num)){
							tos[move]+=1;
							inputOpts[move][tos[move]] = num;
						}
					}
				}
			}
		}else{
			move -= 1;
			inputOpts[move][tos[move]] =-1;
			tos[move] -=1;
			if(move!=0)
				arr[coords[move][0]][coords[move][1]] = 0;
		}
	}
}