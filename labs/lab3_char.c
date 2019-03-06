#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
/* you will be loading in a set of quiz scores from a file, 
 * counting the frequency each number occurs, 
 * sorting the results, 
 * and finally displaying them.
 * */

/* The only place where [] notation is allowed is in the main */

//prototypes: if forgotten they cause CONFLICTING TYPES errors
/**
 *Ties together x and y for frequency and object
 * */

//winscp turns the virtual files into legit files
typedef struct freq{
	char* v;
	int f;
} freq;
//makes it so that all you have to declare a freq struct is type "freq sHist"


char** readScores(int* pCount);
void displayScores(char** pScanned, int count);
int calcHistogram(freq** pHistogram, char** pScanned, int count);
void displayHistogram(freq* pHistorgram, int countH);
void sortHistogram(freq* pHistogram, int count);

int main (){
 
	int count;	//size
	//int scanned[100]; //opens memory slots
	//int count =0; //opens int variable 
	char** scanned = readScores(&count); //pass variables to readScores
	displayScores(scanned, count); 	

	int countH;//create in calc hist 
	freq* sHist;//pass in a pointer to be malloced 

	countH = calcHistogram(&sHist, scanned, count);// freq is like the object name sHist is the var
	displayHistogram(sHist, countH);
	sortHistogram(sHist, countH);
	displayHistogram(sHist, countH);

	int i =0;
	for(i =0; i < count; i++){
	free(scanned[i]);
	}
	free(scanned);
	free(sHist);
}
/***
 *@param int* pCount is pointer to the counter
 *
 *
 * This method fills the memory for the array on the heap one element at a time.
 * @return char** a char* array called an array of strings
 * **/
char** readScores(int* pCount){// int* pScanned is Array, int* count is	
	char** pScanned = (char**) malloc(100 * sizeof(char*));	// char** - * sizeof...
	*pCount = 0;
	char* buffer = (char*) malloc(10 * sizeof(char)); // recieves each pointer element
	
	printf("\n readScores \n\n");
	while( scanf("%s", buffer) != EOF) {//while getting legit address before End Of File
	pScanned[*pCount] = (char*) malloc((strlen(buffer) + 1) * sizeof(char)); //+1 is the null character or "_\0"
		strcpy(pScanned[*pCount],buffer);// place element into memory slot 
		(*pCount)++; //asks for next  memory slot
		
	}
	//now the scanned memory slots needed are filled 
	//memory spot count is filled as well
	free(buffer);
	return pScanned;
}


void displayScores(char** pScanned, int count){
	printf("\n displayScores\n\n");// displays 12
	int i = 0;
	while (i < count){
	printf("Score %d: %s\n", i, pScanned[i]);
	i++;
	}	
	printf("\n");

}
/* get rid of original malloc to 'resize'*/
int calcHistogram(freq** pHistogram, char** pScanned, int count){
	int countH = 0;
	*pHistogram = (freq*) malloc(count * sizeof(freq)); //set up space on heap
	(*pHistogram)[0].v = pScanned[0];
	(*pHistogram)[0].f = 1;
	int i = 0;
	printf("\n calcHistogram \n");
	//printf("\n count : %d\n ", count);
	for(i = 0 ; i < count ; i++){ //less than array size
	char* val;
	val = pScanned[i]; 
	int j = 0;
	 
		while(strcmp(pScanned[j],val) !=0 && j < countH){//
		j++;
		}
		
		if( j == countH){
		//(pHistogram + j)->v = val;
		(*pHistogram)[j].v = val; // new val
		(*pHistogram)[j].f = 1; // first occurance of val means new frequency
		(countH)++;//show size of histogram
		} else {
		(*pHistogram)[j].f ++;// add freq

		}
	}

	return countH;
}


void displayHistogram(freq* pHistogram, int countH){

 	printf("\n displayHistogram \n");
	int i = 0;

		while (i < countH){
		printf("Value: %s \tfreq: %d\n",pHistogram[i].v, pHistogram[i].f);	
		i++;
		}
 	printf("\n");
}

void sortHistogram(freq* pHistogram, int countH){
	//selection sort
	 printf("\n sortHistogram\n");
	int i, j;
	freq temp;//initialize the struct with 0
	for(i = 0; i < countH -1 ; i++){
		for(j= i; j < countH - i-1; j++){
		if( pHistogram [j].f < pHistogram [j+1].f ){ //f comparison
		temp = pHistogram [j];
		pHistogram [j] = pHistogram [j+1];
		pHistogram[j + 1] = temp;
		}
		}

	}		
	 printf("\n");
}


