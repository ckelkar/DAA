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

int minimumcostindex(int *costarray,int length){ //finds minimum cost in costmatrix
int min=999;
int i,minindex;
	for(i=0;i<length;i++){
		if(costarray[i]<min){
			min=costarray[i];
			minindex=i;
		}
	}
return minindex;
}

void printedges(int *parent,int **egdematrix,int length){ // prints output
int i;
printf("\nEdges in minimum spanning tree:");
printf("\nFrom->To\n");
   for ( i = 1; i < length; i++){
      printf("%d->%d", parent[i]+1,i+1);
      printf("\n");
   }
}

void prim(int **edgematrix, int length){ // finds minimum spanning tree using prim algorithm
int *costarray,*parent,*priorityqueue; 
int i,j,u,v;

costarray=(int *)malloc(length*sizeof(int)); //contains costs of edges
parent=(int *)malloc(length*sizeof(int)); //stores parent of vertex
priorityqueue=(int *)malloc(length*sizeof(int)); //vertex with highest priority is selected 


for(i=0;i<length;i++){
	costarray[i]=999;
	parent[i]=-1;
	priorityqueue[i]=i;
}

costarray[0]=0;
j=0;
	for(i=0;i<length;i++){
	u=minimumcostindex(costarray,length);
	priorityqueue[u]=-1;
	
		for(v=0;v<length;v++){
			if(priorityqueue[v]!=-1 && costarray[v] > edgematrix[u][v]){
			costarray[v]=edgematrix[u][v];
			parent[v]=u;			
			}
		}
	costarray[u]=999;
	}
	
	printedges(parent,edgematrix,length);
	
	free(costarray);
	free(parent);
	free(priorityqueue);
	free(edgematrix);
}


int main(int argc,char *argv[])
{
	if(argc!=2){ //checks for valid arguments
		printf("\nInvalid arguments!!!!\n");
		exit(0);
	}
int length,i,j;
int **edgematrix; // adjacency matrix
length=parsefile(argv[1]); //calculates dimension of matrix
edgematrix=allocatearray(length); //creates edgematrix
populatearray(edgematrix,length,argv[1]);
prim(edgematrix,length);
}
