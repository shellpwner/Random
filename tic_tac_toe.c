#include<stdio.h>
#include<stdlib.h>

void dispGrid(int** grid){
	system("clear");
	for(int i=0;i<3;i++){									//			
		for(int j=0;j<3;j++){								//		
			if(grid[i][j] == 5){                    		//
				printf("   |");								//Translating integer grid to spaces and XOs
			}else if(grid[i][j] == 1){						//	
				printf(" X |");								//		
			}else{											//			
				printf(" O |");								//			
			}
		}printf("\n");
	}
	// for(int i=0;i<3;i++){
	// 	for(int j=0;j<3;j++){			//	  debugging
	// 		printf("%d",grid[i][j]);      //    debugging 
	// 	}printf("\n");					//debugging
	// }								//debugging
}

void p1(int** grid){
	int x,y;															//
	printf("Player 1 (X): ");											// Player 1's board placement	
	scanf("%d,%d",&x,&y);												// 
	while(grid[x][y] != 5){									//verification if the chosen spot is vacant or not
		printf("That cell has already been occupied, pick again: ");	//
		scanf("%d,%d",&x,&y);											//loop until the entered point is vacant	
	}																	//
	grid[x][y] = 1;														//set the board
	
}

void p2(int** grid){
	int x,y;															//
	printf("Player 2 (O): ");											// Player 2's board placement	
	scanf("%d,%d",&x,&y);												// 
	while(grid[x][y] != 5){									//verification if the chosen spot is vacant or not
		printf("That cell has already been occupied, pick again: ");	//
		scanf("%d,%d",&x,&y);											//loop until the entered point is vacant	
	}																	//
	grid[x][y] = 0;														//set the board
	
}

int wld_verify(int** grid){		//this function will return 1 if x won, 0 is O won, -1 if draw and 5 if no result
	int sumr(int i){
		return grid[i][0] + grid[i][1] + grid[i][2];
	}
	int sumc(int i){
		return grid[0][i] + grid[1][i] + grid[2][i];
	}			
	int sumd(int i){
		if(i==0){
			return grid[0][0] + grid[1][1] + grid[2][2];
		}else{
			return grid[0][2] + grid[1][1] + grid[2][0];
		}
	}
	int sums[8] = {sumr(0),sumr(1),sumr(2),sumc(0),sumc(1),sumc(2),sumd(0),sumd(1)};//array contining sums of grid
	int flag = 0,nums[9],I=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			nums[I] = grid[i][j];
			I++;
		}
	}
	for(int i=0;i<9;i++){
		if(nums[i] == 5){       // chekcing if there are any empty places in the grid
			flag = 1;			// flag becomes 1 if there are empty spots. Else remains 0 (default)
			break;
		}
	}
	// for(int i=0;i<8;i++){					//debugging
	// 	printf("%d  ",sums[i]);				  //  debugging 
	// }printf("\n");							//debugging 
	// printf("Flag: %d\n",flag);
	// if flag is 0 and the sums array doesn't contain either 3 or 0; then its a draw
	int sums_check(int* sums){ //returns -1 if no win, 1 if 3 is in array, 0 if 0 is in array
		int ret;
		for(int i=0;i<8;i++){
			if(sums[i] == 3){
				ret = 1;      // X wins
				break;
			}else if(sums[i] == 0){
				//printf("i at which sums is 0: %d\n",i);     /debugging
				ret = 0;      //O wins
				break;
			}else{
				ret = -1  ;    // No result
			}
		}
		return ret;
	}
	if(flag == 0 && sums_check(sums) == -1){
		return -1;
	}else if(flag == 1 && sums_check(sums) == 1){
		return 1;
	}else if(flag == 1 && sums_check(sums) == 0){
		return 0;
	}else if(flag == 1 && sums_check(sums) == -1){
		return 5;
	}

}//summary of wld_verify
//returns 0 if O wins, 1 if X wins, 5 if no result, -1 if draw

int main(){
	int** grid;
	grid = (int**)malloc(3*sizeof(int*));				//
	for(int i=0;i<3;i++){                               //creating the grid
		grid[i] = (int*)malloc(3*sizeof(int));			//
	}	

	for(int i=0;i<3;i++){								//
		for(int j=0;j<3;j++){							//filling thr grid with emptie cells. (5-empty, 1-X, 0-O)
			grid[i][j] = 5;								//
		}
	}
	while(1>0){
		p1(grid);
		dispGrid(grid);
		if(wld_verify(grid) != 5){
			if(wld_verify(grid) == 1){
				printf("Player 1 wins!!!\n");
				break;
			}else if(wld_verify(grid) == 0){
				printf("Player 2 wins!!!\n");
				break;
			}else{
				printf("DRAW!!!\n");
				break;
			}
		}else{
			p2(grid);
			dispGrid(grid);
			if(wld_verify(grid) != 5){
				if(wld_verify(grid) == 1){
					printf("Player 1 wins!!!\n");
					break;
				}else if(wld_verify(grid) == 0){
					printf("Player 2 wins!!!\n");
					break;
				}else{
					printf("DRAW!!!\n");
					break;
				}
			}
		}	
	}
	return 0;
}