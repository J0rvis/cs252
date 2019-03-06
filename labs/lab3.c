#include <stdio.h> 
#include <stdlib.h>
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
	int v;
	int f;
} freq;
//makes it so that all you have to declare a freq struct is type "freq sHist"


int* readScores(int* pCount);
void displayScores(int* pScanned, int count);
int calcHistogram(freq** pHistogram, int* pScanned, int count);
void displayHistogram(freq* pHistorgram, int countH);
void sortHistogram(freq* pHistogram, int count);

int main (){
 
	int* scanned;
	int count;	//size

	scanned  = readScores(&count); //pass variables to readScores
	displayScores(scanned, count); 	
 
	int countH;//create in calc hist 
	freq* sHist;//pass in a pointer to be malloced 

	countH = calcHistogram(&sHist, scanned, count);// freq is like the object name sHist is the var
	displayHistogram(sHist, countH);
	sortHistogram(sHist, countH);
	displayHistogram(sHist, countH);
	free(scanned);
	free(sHist);
}
/***
 *@param int* pScanned is the pointers to the scanned array
 *@param int* pCount is pointer to the counter
 *
 *
 * This method fills the memory for the array one element at a time.
 * @return void
 * **/
int* readScores(int* pCount){// int* pScanned is Array, int* count is	
	int* buffer = malloc(sizeof(int)); 

	int* pScanned  = (int*) malloc(100 * sizeof(int));	
	*pCount = 0;
	//int buffer = (int) malloc(1 * sizeof(int)); // recieves each pointer element
	printf("readScores \n\n");
	printf("count:  %d\n", *pCount);
	while(scanf("%d", buffer) != EOF) {//while getting legit address before End Of File

	//	pScanned[*pCount] = malloc(1 * sizeof(int));
		pScanned[*pCount] = *buffer;// place element into memory slot
		(*pCount)++; //asks for next  memory slot
	}
	//now the scanned memory slots needed are filled 
	//memory spot count is filled as well
	free(buffer);
	return pScanned;
}


void displayScores(int* pScanned, int count){
	printf("displayScores\n\n");// 
	int i = 0;
	while (i < count){
	printf("Score %d: %d\n", i, pScanned[i]);
	i++;
	}	
	printf("\n");

}
/* get rid of original malloc to 'resize'*/
int calcHistogram(freq** pHistogram, int* pScanned, int count){
	int countH = 0;
	*pHistogram = (freq*) malloc(count * sizeof(freq)); //set up space on heap
	(*pHistogram)[0].v = pScanned[0];
	(*pHistogram)[0].f = 1;
	int i = 0;
	printf("\n CalcHistogram \n");
	printf("\n count (12) : %d\n ", count);
	for(i = 0 ; i < count ; i++){ //less than array size
	int val = pScanned[i]; 
	int j = 0;
	 
		while((*pHistogram)[j].v != val && j < countH){//
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

 	printf("displayHistogram \n");
	int i = 0;
		//printf(" count: %d\n", count);
		while (i < countH){
		printf("Value: %d \t freq %d\n",pHistogram[i].v, pHistogram[i].f);	
		i++;
		}
 	printf("\n");
}

void sortHistogram(freq* pHistogram, int countH){
	//selection sort
	 printf("sortHistogram\n");
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


