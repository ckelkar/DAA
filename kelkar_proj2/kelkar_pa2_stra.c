#include<stdio.h>
#include<stdlib.h>

int** allocatearray(n) //allocates memory to martrix
{
int **strassen;
int i;
strassen=malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	strassen[i]=malloc(n*sizeof(int));
return strassen;
}

int** populatearray(int** strassen,int n) //populates matrix with elements in the range of -10 to 10
{
int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		strassen[i][j]=rand() %(10 + 1 + 10) + (-10);
	}
return strassen;
}

void display(int **strassen, int n) //displays matrix elements
{
int i,j;
printf("\n");
printf("\nStrassen matrix multiplication\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
		printf("%d\t",strassen[i][j]);
		}
	printf("\n");
	}
}

void divide(int **strassen, int **A11, int m, int n,int size) //divides matrices
{

int i,j,i1,j1;
	for(i=0,i1=m;i<size;i++,i1++)
		for(j=0,j1=n;j<size;j++,j1++)
		A11[i][j]=strassen[i1][j1];

//display(A11,size);
}

int** add(int **firstmatrix,int **secondmatrix,int n) //performs addition
{
int **thirdmatrix=allocatearray(n);
int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		thirdmatrix[i][j]=firstmatrix[i][j]+secondmatrix[i][j];
	}
return thirdmatrix;
}

int** subtract(int **firstmatrix,int **secondmatrix,int n) //performs substraction
{
int **thirdmatrix=allocatearray(n);
int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		thirdmatrix[i][j]=firstmatrix[i][j]-secondmatrix[i][j];
	}
return thirdmatrix;
}

void join(int **C, int** P, int iB, int jB,int size)  //perform join
    {
    	int i1,j1,i2,j2;
        for(i1 = 0, i2 = iB; i1 < size; i1++, i2++)
            for(j1 = 0, j2 = jB; j1 < size; j1++, j2++)
                P[i2][j2] = C[i1][j1];
    }    


		

int** multiplication(int** firstmatrix,int** secondmatrix,int n) //applies strassen algorithm on matrices to perform multiplications
{
int **A11,**A12,**A21,**A22,**B11,**B12,**B21,**B22,**M1,**M2,**M3,**M4,**M5,**M6,**M7,**C11,**C12,**C21,**C22,**result;
result=allocatearray(n);
	if(n==1)
	{
		result[0][0]=firstmatrix[0][0]*secondmatrix[0][0];
		return result;
	}
A11=allocatearray(n/2);
A12=allocatearray(n/2);
A21=allocatearray(n/2);
A22=allocatearray(n/2);
B11=allocatearray(n/2);
B12=allocatearray(n/2);
B21=allocatearray(n/2);
B22=allocatearray(n/2);

divide(firstmatrix,A11,0,0,n/2); //divides firstmatrix A11
divide(firstmatrix,A12,0,n/2,n/2);//divides firstmatrix A12
divide(firstmatrix,A21,n/2,0,n/2);//divides firstmatrix A21
divide(firstmatrix,A22,n/2,n/2,n/2);//divides firstmatrix A22

divide(secondmatrix,B11,0,0,n/2);//divides secondmatrix B11
divide(secondmatrix,B12,0,n/2,n/2);//divides secondmatrix B12
divide(secondmatrix,B21,n/2,0,n/2);//divides secondmatrix B21
divide(secondmatrix,B22,n/2,n/2,n/2);//divides secondmatrix B22

M1=allocatearray(n/2);
M2=allocatearray(n/2);
M3=allocatearray(n/2);
M4=allocatearray(n/2); 
M5=allocatearray(n/2);
M6=allocatearray(n/2);
M7=allocatearray(n/2);

M1=multiplication(add(A11,A22,n/2),add(B11,B22,n/2),n/2);//M1=(A11+A12)x(B11+B12)
M2=multiplication(add(A21,A22,n/2),B11,n/2);//M2=(A21+A22)xB11
M3 = multiplication(A11, subtract(B12, B22,n/2),n/2);//M3=A11x(B12-B22)
M4 = multiplication(A22, subtract(B21, B11,n/2),n/2);//M4=A22x(B21-B11)
M5 = multiplication(add(A11, A12,n/2), B22,n/2);//M5=(A11+A12)xB22
M6 = multiplication(subtract(A21, A11,n/2), add(B11, B12,n/2),n/2);//(A21-A11)x(B11+B12)
M7 = multiplication(subtract(A12, A22,n/2), add(B21, B22,n/2),n/2);//(A12-A22)x(B21+B22)

C11 = add(subtract(add(M1, M4,n/2), M5,n/2), M7,n/2); //C11=M1+M4-M5+M7
C12 = add(M3, M5,n/2);// C12=M3+M5
C21 = add(M2, M4,n/2);// C21=M2+M4
C22 = add(subtract(add(M1, M3,n/2), M2,n/2), M6,n/2);//C22= M1+M3-M2+M6

join(C11, result, 0 , 0, n/2); 
join(C12, result, 0 , n/2,n/2);
join(C21, result, n/2, 0,n/2);
join(C22, result, n/2, n/2,n/2);

return result;

}



void normalmatrixmultiplication(int **firstmatrix,int **secondmatrix,int n) //performs normal multiplication
{
int i,j,k;
int **mult;
mult=allocatearray(n);
for(i=0; i<n; i++)
    for(j=0; j<n; j++)
    for(k=0; k<n; k++)
    {
        mult[i][j]+=firstmatrix[i][k]*secondmatrix[k][j];
    }
    
    printf("\nNormal matrix multiplication\n"); //prints normal matrix multiplication
    for(i=0;i<n;i++){
		for(j=0;j<n;j++){
		printf("%d\t",mult[i][j]);
		}
	printf("\n");
	}	
    		
}
int main(int argc, char*argv[])
{
int n,check;
int **firstmatrix; //first matrix
int **secondmatrix; //second matrix
int **result;
		if(argc!=2){
		printf("\nplease enter valid input!!!");
		exit(0);
		}
	
	n=atoi(argv[1]);
	if(n==0){
	printf("\nPlease enter the number in the range of 2^n");
	exit(0);
	}
	if(n%2!=0 && n!=1){
	printf("\nPlease enter the number in the range of 2^n\n");
	exit(0);
	}
	else{  //checks for the input in the range of 2^n
	check=n;
		if(n!=1){
			do{
			check=check/2;
				if(check!=1 && check%2!=0){
				printf("\nPlease enter the number in the range of 2^n\n");
				exit(0);
				}
			}while(check!=1);
		}
	}
	

firstmatrix=allocatearray(n);
secondmatrix=allocatearray(n);
result=allocatearray(n);
populatearray(firstmatrix,n);
populatearray(secondmatrix,n);
result=multiplication(firstmatrix,secondmatrix,n);
display(result,n);
normalmatrixmultiplication(firstmatrix,secondmatrix,n);
}






