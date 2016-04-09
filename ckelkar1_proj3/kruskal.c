#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Edge{ //stores all the source vertex, destination vertex and weight
int source;
int destination;
int weight;
}edge;

struct graph{ //stores edges
int vertices;
int edges;
struct Edge *edge;
};

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
	while (p != NULL){	
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

int partition_quicksort(struct graph *edgearray,int start, int end) //partitions input array according to partition index
{
edge temp;
srand(time(NULL));
int pindex,i;
int pivotindex = start+rand() % (end-start+1); //selects pivot in random fashion
int pivot=edgearray->edge[pivotindex].weight;

temp=edgearray->edge[end];
edgearray->edge[end]=edgearray->edge[pivotindex];
edgearray->edge[pivotindex]=temp;

pindex=start;

	for(i=start;i<end;i++){
		if(edgearray->edge[i].weight< pivot){
			temp=edgearray->edge[i];
			edgearray->edge[i]=edgearray->edge[pindex];
			edgearray->edge[pindex]=temp;
			pindex++;
		}
	}

temp=edgearray->edge[i];
edgearray->edge[i]=edgearray->edge[pindex];
edgearray->edge[pindex]=temp;
return pindex;	

}

void quick_sort(struct graph *edgearray,int start, int end) //performs randomised quicksort
{
	int partition_index; //partitionindex
	if(start>=end)
	return;
	partition_index=partition_quicksort(edgearray,start,end);
	quick_sort(edgearray,start,partition_index-1);
	quick_sort(edgearray,partition_index+1,end);
}


int find3(int subset[],int x) //finds vertex in the tree
{
	int root=x;
	
	int node,parent;
	while(root!=subset[root])
	root=subset[root];
	
	node=x;
	while(node!=root){
	parent=subset[node];
	subset[node]=root;
	node=parent;
	}

return root;
}
	

void Union3(int subset[],int height[],int x,int y){ //calculates union of sets
	if(height[x] == height [y]){
	height[x]++;
	subset[y] = x;
	}
    	else{
        	if (height[x] > height[y])
            	subset[y]=x;
            	else
           	subset[x]=y;
        }
}
	


void kruskal(struct graph* graph_Kruskal,int length){ // finds minimum spanning tree using kruskal algorithm
int i,x,y,j;
edge output[length*length]; // stores minimum spanning tree
edge next_edge;
int e=0;
int count=0;


int subset[length];
int height[length];

for(i=0;i<length;i++){
	subset[i]=i;	
	height[i]=0;
}
	

for(i=0;i<length*length;i++)
{	
	if(graph_Kruskal->edge[i].weight!=0 ){
		if(graph_Kruskal->edge[i].weight!=999){
		next_edge= graph_Kruskal->edge[i];
	
		x=find3(subset,next_edge.source);
		y=find3(subset,next_edge.destination);
			
			if(x!=y){
			output[e++]=next_edge;
			Union3(subset,height,x,y);
			count++;
			}
		
    		}
    	}
	
}	

printf("\nEdges in minimum spanning tree:"); 
printf("\nFrom->To\n");
for(i=0;i<count;i++){ //prints edges which form minimum spanning tree
	printf("%d->%d",output[i].source+1,output[i].destination+1);
	printf("\n");
	}

}

void main(int argc,char *argv[]){
if(argc!=2){ //checks for valid arguments
		printf("\nInvalid arguments!!!!\n");
		exit(0);
	}
int length,i,j;
int **weightmatrix; //adjacency-matrix
struct graph *graph;
length=parsefile(argv[1]); //calculates dimension of matrix
struct graph *edgearray =  (struct graph *)malloc(sizeof(struct graph)); // allocates graph 
edgearray->vertices = length;
edgearray->edges = length*length;
weightmatrix=allocatearray(length);
populatearray(weightmatrix,length,argv[1]);
int k = 0;
edgearray->edge =  (struct Edge *)malloc(sizeof(struct Edge)); // allocates edges
	for(i=0;i<length;i++){
		for(j=0;j<length;j++){
			edgearray->edge[k].source=i;
			edgearray->edge[k].destination=j;
			edgearray->edge[k].weight=weightmatrix[i][j];
		k++;
		}
	}

quick_sort(edgearray,0,length*length); 
kruskal(edgearray,length);
free(weightmatrix);

}
