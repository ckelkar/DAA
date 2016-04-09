#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int count=1;
int hole_x,hole_y;
int** allocatearray(int n)  //allocates memory to matrix
{
int **array;
int i;
array=malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	array[i]=malloc(n*sizeof(int));
return array;
}

void trominotile(int **tromino,int k, int board_top_x, int board_top_y,int hole_x,int hole_y) //applies trominotile algorithm to input matrix
{
int i,j;
	if(k==1)
	{
		for(i=0;i<pow(2,k);i++){
			for(j=0;j<pow(2,k);j++){
				if(tromino[board_top_x+i][board_top_y+j]==0)
				tromino[board_top_x+i][board_top_y+j]=count;
			}
		}
	count++;
	return;
	}
	else
	{
		 int hole1_x=board_top_x;
		 int hole1_y=board_top_y;
		 int size=pow(2,k);
			for(i=board_top_x;i<board_top_x+size;i++){ //serches for the hole
				for(j=board_top_y;j<board_top_y+size;j++){
					if(tromino[i][j]!=0){
					hole1_x=i;
					hole1_y=j;
					}
				}
			}
				if(hole1_x < board_top_x+ size/2 && hole1_y < board_top_y+size/2) //if found in first quadrant
				{
					trominotile(tromino,k-1,board_top_x,board_top_y,hole1_x,hole1_y);
					
					tromino[board_top_x+size/2][board_top_y+size/2-1] = count;
					tromino[board_top_x+size/2][board_top_y+size/2] = count;
					tromino[board_top_x+size/2-1][board_top_y+size/2] = count;
					
					count++;
					
					trominotile(tromino,k-1,board_top_x,board_top_y+size/2,hole1_x,hole1_y);
					trominotile(tromino,k-1,board_top_x+size/2,board_top_y,hole1_x,hole1_y);
					trominotile(tromino,k-1,board_top_x+size/2,board_top_y+size/2,hole1_x,hole1_y);
				}
				else if (hole1_x < board_top_x + size/2 && hole1_y >= board_top_y+size/2) //if found in third quadrant
				{
					trominotile(tromino,k-1,board_top_x,board_top_y+size/2,hole1_x,hole1_y);
					
					tromino[board_top_x+size/2][board_top_y+size/2-1] = count;
					tromino[board_top_x+size/2][board_top_y+size/2] = count;
					tromino[board_top_x+size/2-1][board_top_y+size/2-1] = count;
					
					count++;
					
					trominotile(tromino,k-1,board_top_x,board_top_y,hole1_x,hole1_y);
					trominotile(tromino,k-1,board_top_x+size/2,board_top_y,hole1_x,hole1_y);
					trominotile(tromino,k-1,board_top_x+size/2,board_top_y+size/2,hole1_x,hole1_y);
					
				}
				else if (hole1_x >= board_top_x + size/2 && hole1_y < board_top_y+size/2) //if found in second quadrant
				{
					trominotile(tromino,k-1,board_top_x+size/2,board_top_y,hole1_x,hole1_y);
					
					tromino[board_top_x+size/2-1][board_top_y+size/2] = count;
					tromino[board_top_x+size/2][board_top_y+size/2] = count;
					tromino[board_top_x+size/2-1][board_top_y+size/2-1] = count;
					
					count++;
					
					trominotile(tromino,k-1,board_top_x,board_top_y,hole1_x,hole1_y);
					trominotile(tromino,k-1,board_top_x,board_top_y+size/2,hole1_x,hole1_y);
					trominotile(tromino,k-1,board_top_x+size/2,board_top_y+size/2,hole1_x,hole1_y);
					
				}
				else //if found in fourth quadrant
				{
					trominotile(tromino,k-1,board_top_x+size/2,board_top_y+size/2,hole1_x,hole1_y);
					
					tromino[board_top_x+size/2-1][board_top_y+size/2] = count;
					tromino[board_top_x+size/2][board_top_y+size/2-1] = count;
					tromino[board_top_x+size/2-1][board_top_y+size/2-1] = count;
					
					count++;
					
					trominotile(tromino,k-1,board_top_x+size/2,board_top_y,hole1_x,hole1_y);
					trominotile(tromino,k-1,board_top_x,board_top_y+size/2,hole1_x,hole1_y);
					trominotile(tromino,k-1,board_top_x,board_top_y,hole1_x,hole1_y);
				}	
		
	}

}

void display(int **array, int n) //displays matrix
{
int i,j,mid;
printf("\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
		if(array[i][j]==-1)
		printf("X\t");
		else
		printf("%d\t",array[i][j]);
		}
	printf("\n");
	}
}

int main(int argc,char *argv[])
{
int board_top_x,board_top_y,k,size;

	if(argc!=2 || atoi(argv[1])==0){  //checks for the validity of arguments
	printf("\ninvalid input!!!!!!");
	exit(0);
	}
	
k=atoi(argv[1]);
size=pow(2,k);
hole_x=rand()%size+0;
hole_y=rand()%size+0;
int **tromino=allocatearray(size);
tromino[hole_x][hole_y]=-1;
trominotile(tromino,k,0,0,hole_x,hole_y);
display(tromino,size);
}


