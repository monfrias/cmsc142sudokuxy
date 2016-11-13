#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 4


//printing of array
void printArray(int arr[][N], int size) {
	int i,j;
	for(i=0; i<size; i+=1) {
		for(j=0; j<size; j+=1) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

//check if there is no dublicate on the main diagonals of the puzzle
// int sudokuX(int arr[][N], int row, int size, int num) {
// 	int 
// }

//checking the rows if the input good to use
int checkRow(int arr[][N], int row, int size, int num) {
	int col;
	for(col=0; col<size; col+=1) {
		if(arr[row][col] == num) {
			return 0;
		}
	}
	return 1;
}

//checking the col if the input is good to use
int checkCol(int arr[][N], int col, int size, int num) {
	int row;
	for(row=0; row<size; row+=1) {
		if(arr[row][col] == num) {
			return 0;
		}
	}
	return 1;
}

//checking the subgrid if the input is good to use
int checkSubgrid(int arr[][N], int subgridRow, int subGridCol, int size, int num) {
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

//summarizes the different checkers for the input
int isvalidInput(int arr[][N], int row, int col, int size, int num){
	int size2 = (int) sqrt(size);
	if(checkRow(arr,row,size,num) == 0)
		return 0;
	if(checkCol(arr,col,size,num) == 0)
		return 0;
	if(checkSubgrid(arr, row-row%(size2), col-col%(size2), size,num)==0)
		return 0;
	// if(checkSudokuX())
	// 	return 0;
	return 1;
}

//checks the finished sudoku solution if it good
int isValidSoln(int arr[][N], int size){
	int i,j;
	int checkerRow[size];
	int checkerCol[size];
	int checkerDiag1[size];
	int checkerDiag2[size];

	//initialize checkerArray
	for(i=0;i<size;i+=1){
		checkerRow[i]=0;
		checkerCol[i]=0;
		checkerDiag1[i]=0;
		checkerDiag2[i]=0;
	}

	//checks for unfilled cells
	for(i=0;i<size;i+=1){
		for(j=0;j<size;j+=1){
			if(arr[i][j] == 0)
				return 0;
		}
	}

	//check if there are no duplicates -> row
	for(i=0;i<size;i+=1){
		for(j=0;j<size;j+=1){
			checkerRow[arr[i][j]-1] +=1;
		}

		for(j=0;j<size;j+=1){
			if(checkerRow[j] != i+1)
				return 0;
		}
	}

	//check if there re no duplicates -> col
	for(i=0;i<size;i+=1){
		for(j=0;j<size;j+=1){
			checkerCol[arr[j][i]-1] +=1;
		}

		for(j=0;j<size;j+=1){
			if(checkerCol[j] != i+1)
				return 0;
		}
	}

	//check if there is no duplicates in the main diagonal 1
	for(i=0;i<size;i+=1){
		for(j=0;j<size;j+=1){
			if(i==j){
				checkerDiag1[arr[j][i]-1] +=1;
			}

			for(j=0;j<size;j+=1){
				if(checkerDiag1[j] != i+1)
					return 0;	
			}
		}
	}

	//check if there is no duplicates in the main diagonal 2
	for(i=0;i<size;i+=1){
		for(j=0;j<size;j+=1){
			if((i+j)==size-1){
				checkerDiag2[arr[j][i]-1] +=1;
			}

			for(j=0;j<size;j+=1){
				if(checkerDiag2[j] != i+1)
					return 0;
			}
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
	int arr[N][N] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	/*int arr[9][9] = 	{1,0,0,0,2,0,0,0,4,
						0,2,0,0,0,8,0,1,0,
						0,0,3,0,4,0,2,0,0,
						0,0,0,4,0,3,0,0,0,
						0,1,0,0,5,0,0,4,0,
						0,0,0,7,6,9,0,0,0,
						0,0,6,0,7,0,8,0,0,
						0,9,0,0,8,0,0,7,0,
						8,0,7,0,9,0,0,0,6};*/
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

	for(i=0;i<numCells;i+=1){
		for(j=0;j<numOpts;j+=1){
			inputOpts[i][j] = -1;
		}
	}

	//setting up the coords table
	for(i=0;i<size;i+=1){
		for(j=0;j<size;j+=1){
			if(arr[i][j] == 0){
				move += 1;
				coords[move][0] = i;
				coords[move][1] = j;
			}
		}
	}

	printArray(arr,size);

	move = 0;
	while(tos[start]>0){
		if(tos[move]>0){

			if(inputOpts[move][tos[move]] != -1)
				arr[coords[move][0]][coords[move][1]] = inputOpts[move][tos[move]];

			move +=1;
			tos[move]=0;

			if(isValidSoln(arr,size) != 0){
				countValid+=1;	
				printf("Solution %d:\n",countValid);
				printArray(arr,size);
				//printf("%d\n",tos[start]);
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
			//backtrack
			move -= 1;
			inputOpts[move][tos[move]] = -1;
			tos[move] -=1;
			//printf("MOVE: %d\n", move);
			if(move!=0)
				arr[coords[move][0]][coords[move][1]] = 0;
		}
	}
}