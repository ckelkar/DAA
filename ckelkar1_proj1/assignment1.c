#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int flag=0;
int printarray_size=0;

void animation(int *input,int start,int end)   //displays textual visualization of input
{
int i,j;	
printf("\n");
	for(i=start;i<end;i++){
		for(j=input[i];j>0;j--){
			printf("*");
		}
		printf("\n");
	}
printf("----------------------------------------------------------");

}

void insertion_sort(int *input,int size) //sorts input data by using insertion sort technique
{
int i,j,temp;
	for (i = 1; i < size; i++){
		for (j = i; j >= 0 && input[j] < input[j-1]; j--){
			if(flag==1)
				printf("\n[%d] needs to be swapped with [%d]\n",input[j-1],input[j]);
			temp= input[j];
      			input[j]   = input[j-1];
      			input[j-1] = temp;
				if(flag==1){
				printf("After swapping\n");
					animation(input,0,size);	
				}
		}
		
	}

printf("\nsorted array is\n");
	for(i=0;i<size;i++)   //Prints sorted array
		printf("%d\t",input[i]);
	
	if(flag==1){ //calls animation function 
		animation(input,0,size);
		flag=0;
	}
free(input);
	
}

void count_sort(int *input,int size) //sort input data by using counting sort technique
{
int *countarray,*resultarray;
resultarray=malloc((size+1)*sizeof(int));
int max=input[0],i;

printf("\nmax=%d",max);
	for(i=1;i<size;i++)  //finds maximum element in input array
		if(max<input[i])
			max=input[i];

countarray=malloc((max+1)*sizeof(int));

	for(i=0;i<=max;i++) //Initialize auxiliary array
		countarray[i]=0;
	for(i=0;i<=size;i++) //Initialize output array
		resultarray[i]=0;


	
	for(i=0;i<size;i++)
		countarray[input[i]]=countarray[input[i]] + 1; //updates auxiliary array 
	
	
	if(flag==1){
		printf("\nInitial count array\n");
		for(i=0;i<=max;i++)
		printf("%d",countarray[i]);
		//animation(countarray,0,max);
	}

	for(i=1;i<=max;i++)
		countarray[i]=countarray[i]+countarray[i-1]; //updates auxiliary array
	
	if(flag==1){
		printf("\nUpated count array\n");
			for(i=0;i<=max;i++)
				printf("%d",countarray[i]);
		//animation(countarray,0,max);
	}
	
	 for(i=0;i<size;i++){  //updates result array according to the auxiliary array
		resultarray[countarray[input[i]]]=input[i];
		countarray[input[i]]=countarray[input[i]]-1;
			if(flag==1){
				printf("\nFilling result array according to countarray");
				animation(resultarray,1,size+1);
			}
	}

	printf("\nSorted array is\n"); //prints sorted array
	for(i=1;i<=size;i++)
		printf("%d\t",resultarray[i]);

	if(flag==1){
		printf("\nGraphical representation of sorted array\n");
		animation(resultarray,1,size+1);
		flag=0;
	}
free(countarray);
free(resultarray);
free(input);
	
}


void merge(int *input,int low,int mid,int high){

    int i,m,k,l;
    int *temparray=malloc((high+1)*sizeof(int));
    l=low;
    i=low;
    m=mid+1;

    while((l<=mid)&&(m<=high)){ //compares elements in two partitioned array and merge accordingly

         if(input[l]<=input[m]){
         	temparray[i]=input[l];
         	l++;
         }
         else{
         	temparray[i]=input[m];
         	m++;
         }
         i++;
    }

   
    if(l>mid){ //merges remaining elements
         for(k=m;k<=high;k++){
             temparray[i]=input[k];	     
             i++;
         }
	
    }
    
    else{  //merges remaining elements
         for(k=l;k<=mid;k++){
             temparray[i]=input[k];
             i++;
         }
	
    }
    
    for(k=low;k<=high;k++)
         input[k]=temparray[k];


free(temparray);
}



void partition(int arr[],int low,int high){ //partitions array into two parts

    int mid;

    if(low<high){
         mid=(low+high)/2;
         partition(arr,low,mid);
         partition(arr,mid+1,high);
         merge(arr,low,mid,high);
	if(flag==1){
		printf("\nAfter partitioning and merging");
		animation(arr,0,printarray_size);	
		}
	 
		
    }
}


void merge_sort(int input[], int size)
{
printarray_size=size;
partition(input,0,size-1);
}

int partition_quicksort(int *input,int start, int end) //partitions input array according to partition index
{
srand(time(NULL));
int temp,pindex,i;
int pivotindex = start+rand() % (end-start+1); //selects pivot in random fashion
int pivot=input[pivotindex];

	if(flag==1)
		printf("\nselected pivot element is=[%d]",pivot);

	if(flag==1)
		printf("\n[%d] needs to be swapped with end element [%d]",pivot,input[end]);
temp=input[end];
input[end]=input[pivotindex];
input[pivotindex]=temp;
	if(flag==1){
		printf("\nafter swapping");
		animation(input,start,end);
	}

pindex=start;

	for(i=start;i<end;i++){
		if(input[i]<pivot){
				if(flag==1)
					printf("\n[%d] needs to be swapped with end element [%d]",input[i],input[pindex]);
			temp=input[i];
			input[i]=input[pindex];
			input[pindex]=temp;
				if(flag==1){
					printf("\nafter swapping");
					animation(input,start,end);
				}
			pindex++;
		}
	}

	if(flag==1)
		printf("\nFinal Swap.[%d] needs to be swapped with end element [%d]",input[i],input[pindex]);
temp=input[i];
input[i]=input[pindex];
input[pindex]=temp;
	if(flag==1){
		printf("\nafter swapping");
		animation(input,start,end);
	}	
return pindex;	

}

void quick_sort(int *input,int start, int end)
{
	int partition_index;
	if(start>=end)
	return;
	partition_index=partition_quicksort(input,start,end);
	quick_sort(input,start,partition_index-1);
	quick_sort(input,partition_index+1,end);
}


/*displays menu, gets input from user and 
selects sorting function according to user choice
and handles program for invalid user inputs*/
int main()         		
{				   
	int choice,size,i,r;
	int *input;

	do{
		printf("\n1.Insertion Sort\n2.Counting Sort\n3.Merge Sort\n4.Randomized Quick Sort\n5.Exit");
		printf("\nEnter your Choice");
		scanf("%d",&choice);
		if(choice<=0 || choice>5){
			printf("Invalid choice: ");
			exit(0);
		}

		if(choice==5)
			exit(0);

		printf("\nEnter size: ");
		scanf("%d",&size);

		if(size<1 || size >1000){
			printf("\nNot in range\n");
			exit(0);
		}

	
		input=malloc(size*sizeof(int)); //allocates input array dynamically

		if(choice==2 && size >20){
			for(i=0;i<size;i++)
				input[i]=rand() %100+0;
		}else if(size <= 20){	
			for(i=0;i<size;i++)
				input[i]=rand() %16+0;
			flag=1;
		}else{
			for(i=0;i<size;i++)
			input[i]=rand();
		}
	
	printf("\nRandomly generated elements are\n");
	for(i=0;i<size;i++)
	printf("%d\t",input[i]);

	if(flag==1){
		//printf("\n\nGraphical representation of data\nInitial array\n");
		//animation(input,0,size);
	}
	
	switch(choice){ //selects sorting algorithm according to user choice 
	case 1:insertion_sort(input,size);
		break;
	case 2:count_sort(input,size);
		break;
	case 3:merge_sort(input,size);
		printf("\n\nsorted elements are:\n ");
			
    		for(i=0;i<size;i++)
         		printf("%d\t",input[i]);
		if(flag==1){
			animation(input,0,size);
			flag=0;
		}
		free(input);
		break;
	case 4:quick_sort(input,0,size-1);
		printf("\n\nsorted elements are: \n");
    		for(i=0;i<size;i++)
       			printf("%d\t",input[i]);
		if(flag==1){
			animation(input,0,size);
			flag=0;
		}
		free(input);
		break;
	
	}
    }
		
	while(choice!=5);

}

