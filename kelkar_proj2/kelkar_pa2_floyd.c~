#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int parsefile(char filename[]) //calculates length of the file
{
int length=0;
char ch;
char *p;
FILE *fp;
char line[1000];

fp=fopen(filename,"r");
	if(!fp){
	printf("\nerror in opening file");
	exit(0);
	}




int ret=fscanf(fp,"%s",line);
p = strtok(line,","); 
	while (p != NULL)
  	{	
  		length++;
    		p = strtok (NULL, ",");
  	}
  	
  

fclose(fp);
return length;
}

int** allocatearray(int n) // creates matrix
{
int **array;
int i;
array=malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	array[i]=malloc(n*sizeof(int));
return array;
}

void populatearray(int **array,int n,char filename[]) // scans file and inserts element in matrix
{
FILE *fp;
char *p;
char ch;
int size=n*n;
int temparray[size];
int i=0,j=0;
char *line=(char *)malloc(n*sizeof(char));

fp=fopen(filename,"r"); //checks for the input file
	if(!fp){
	printf("\nerror in opening file");
	exit(0);
	}
	
while(1){
int ret=fscanf(fp,"%s",line);
p = strtok(line,","); 
	while (p != NULL)
  	{	
  		int x=atoi(p);
  		temparray[i]=x;
   		i++;
    		p = strtok (NULL, ","); //parses and prepares input in valid format
  	}
  	if (ret != 1)
        break;
  }
  
int k=0; 
for(i=0;i<n;i++){ //transfers elements from 1D array to matrix
	for(j=0;j<n;j++){
	array[i][j]=temparray[k];
	k++;
	}
}
fclose(fp);
}

void display(int **array, int n) //displays matrix elements
{
int i,j;
printf("\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
		printf("%d\t",array[i][j]);
		}
	printf("\n");
	}
}

void initializepatharray(int **patharray,int n) //initializes path matrix
{
int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i!=j)
			patharray[i][j]=j;
		}	
	}
}

void floyd(int **distancearray,int **patharray,int n) //checks for the input, applies floyd algorithm and populate distance and path array
{
int i,j,k;
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(distancearray[i][j]> (distancearray[i][k] + distancearray[k][j])){
				distancearray[i][j]=distancearray[i][k] + distancearray[k][j];
				patharray[i][j]=k;
				}
				else{
				distancearray[i][j]=distancearray[i][j];
				}
				
			}
		}
		
	}
		printf("\ndistancearray");
		display(distancearray,n);
		printf("\npatharray");
		display(patharray,n);
}

void path(int **patharray,int i,int j) //calculates shortest path from each node
{
	if(patharray[i][j]!=j){
	path(patharray,i,patharray[i][j]);
	printf("V%d",patharray[i][j]+1);
	path(patharray,patharray[i][j],j);
	return;
	}else
	return;
}


int main(int argc,char *argv[])
{
	if(argc!=2){ //checks for valid arguments
		printf("\nInvalid arguments!!!!\n");
		exit(0);
	}
int length,i,j;
int **distancearray,**patharray; 
length=parsefile(argv[1]);
distancearray=allocatearray(length);
patharray=allocatearray(length);
populatearray(distancearray,length,argv[1]);
initializepatharray(patharray,length);
floyd(distancearray,patharray,length);
printf("\nShortest paths are\n");
for(i=0;i<length;i++){  //prints shortest paths
	for(j=0;j<length;j++){
		if(distancearray[i][j]<500 && i!=j){
		printf("V%d",i+1);
		path(patharray,i,j);
		printf("V%d",j+1);
		printf("\n");
		}
		
	}
	printf("\n");
}
	 
}

