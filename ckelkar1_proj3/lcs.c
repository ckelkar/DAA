#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void calculate_lengths(char *filename,int *firststring_length,int *secondstring_length){ //calculates lengths of the inputs
FILE *fp;
int c;

fp=fopen(filename,"r"); //checks for the input file
	if(!fp){
	printf("\nerror in opening file");
	exit(0);
	}

 	while ((c = fgetc(fp)) != '\n'){
         (*firststring_length)++;
    	}

 	while ((c = fgetc(fp)) != '\n'|| (c = fgetc(fp))!= EOF){
         (*secondstring_length)++;
    	}



    
fclose(fp);
}

char *createarray(int length){
char *array=(char *)malloc(length*sizeof(char));
return array;
}

void populatearray(char *firststring, char *secondstring,char *filename){ //reads inputs from text file and stores them in array
FILE *fp;
int c;
int n=0;

fp=fopen(filename,"r"); //checks for the input file
	if(!fp){
	printf("\nerror in opening file");
	exit(0);
	}

	while ((c = fgetc(fp)) != '\n'){
        firststring[n++] = (char) c;
    	}
    	firststring[n] = '\0';
    	n=0;
    	
    	while ((c = fgetc(fp)) != '\n'|| (c = fgetc(fp))!= EOF){
         secondstring[n++]=(char)c;
    	}
    	secondstring[n]='\0';
	
fclose(fp);
}

int **createLCSarray(int firststring_length, int secondstring_length){ //creates LCSarray
int **array;
int i;
array=malloc((firststring_length+1)*sizeof(int*));
	for(i=0;i<=firststring_length;i++)
	array[i]=malloc((secondstring_length+1)*sizeof(int));
return array;
}

char **createchararray(int firststring_length, int secondstring_length){ //creates solutionarray
char **array;
int i;
array=malloc((firststring_length+1)*sizeof(char*));
	for(i=0;i<=firststring_length;i++)
	array[i]=malloc((secondstring_length+1)*sizeof(char));
return array;
}

int findmax(int a,int b) //finds maximum of two integers
{
	if(a>b)
	return a;
	else
	return b;
}

void printLCS(int firststring_length,int secondstring_length,char **solutionarray,char *firststring,int **LCSarray){ //calculates longest 																common subsequence

char x=solutionarray[firststring_length][secondstring_length];
char *output=createarray(secondstring_length);
int a=firststring_length;
int b=secondstring_length;
int k=0;

int i,j;

	while(x!='0'){
		if(solutionarray[a][b]=='D'){
		output[k++]= firststring[a-1];
		a--;
		b--;
		}else if(solutionarray[a][b] == 'L') {
			b--;
		}else if(solutionarray[a][b] == 'U') {
			a--;
		}
			x = solutionarray[a][b];
		}
		output[k]='\0';
		
		printf("\nLongest Common Subsequesnce is:");
		
		for(k=strlen(output)-1;k>=0;k--){
		printf("%c",output[k]);
		}
		printf(" %d",LCSarray[firststring_length][secondstring_length]);
		printf("\n");
}



void LCS(int firststring_length,int secondstring_length,int **LCSarray,char *firststring,char *secondstring){ //populates LCSarray and 															solutionarray used in 
														//finding subsequence	
int i,j;
char **solutionarray=createchararray(firststring_length,secondstring_length); //stores directions for traversal
int n=0;
	for(i=0;i<=firststring_length;i++){
	LCSarray[i][0]=0;
	solutionarray[i][0]='0';
	}
		
	for(j=0;j<=secondstring_length;j++){
	LCSarray[0][j]=0;
	solutionarray[0][j]='0';
	}
		
		
	for(i=1;i<=firststring_length;i++){
		for(j=1;j<=secondstring_length;j++){
			if(firststring[i-1]==secondstring[j-1]){
				LCSarray[i][j]=LCSarray[i-1][j-1]+1;
				solutionarray[i][j]='D';
			}
			else{
				if(LCSarray[i-1][j] >= LCSarray[i][j-1]){
				LCSarray[i][j]=LCSarray[i-1][j];
				solutionarray[i][j]='U';
				}
				else{
				LCSarray[i][j]=LCSarray[i][j-1];
				solutionarray[i][j]='L';
				}
			}
		}
	}
printLCS(firststring_length,secondstring_length,solutionarray,firststring,LCSarray);

free(solutionarray);			
}

void main(int argc,char *argv[]){

int *first_length_pointer,*second_length_pointer; //pointers to the lengths of arrays
int **LCSarray; //stores lengths of the subsequences
int i;
char *firststring,*secondstring; //input strings
int firststring_length=0;
int secondstring_length=0;
first_length_pointer=&firststring_length;
second_length_pointer=&secondstring_length;
	if(argc!=2){
	printf("\nInvalid Arguments");
	exit(0);
	}
calculate_lengths(argv[1],&firststring_length,&secondstring_length);
firststring_length=*first_length_pointer;
secondstring_length=*second_length_pointer;
firststring=createarray(firststring_length); //allocates memory for first input string
secondstring=createarray(secondstring_length);//allocates memory for second input string
populatearray(firststring,secondstring,argv[1]);
LCSarray=createLCSarray(firststring_length,secondstring_length); //creates LCSmatrix
LCS(firststring_length,secondstring_length,LCSarray,firststring,secondstring);

free(LCSarray);

}
