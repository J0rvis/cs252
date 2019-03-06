#include <stdio.h> 

/* you will be loading in a set of quiz scores from a file, 
 * counting the frequency each number occurs, 
 * sorting the results, 
 * and finally displaying them.
 * */

/* The only place where [] notation is allowed is in the main */

//prototypes: if forgotten they cause CONFLICTING TYPES errors
//void readScores(int* pScanned, int* pCount);
//void displayScores(int* pScanned, int* pCount);
//void calcHistogram(struct freq* pHistogram, int* pCountH);
/**
 *Ties together x and y for frequency and object
 * */

//winscp turns the virtual files into legit files
struct freq{
	int v;
	int f;
};
//makes it so that all you have to declare a freq struct is type "freq sHist"
/*typedef struct freq{
        int v;
        int f;
 } freq;
*/


void readScores(int* pScanned, int* pCount);
void displayScores(int* pScanned, int* pCount);
void calcHistogram(struct freq* pHistogram, int* pScanned, int* pCountH, int* pCount);
void displayHistogram(struct freq* pHistorgram, int* pCount);
void sortHistogram(struct freq* pHistogram, int* pCount);
void swap(int* v1, int* f1, int* v2, int* f2);

int main (){
	
	int scanned[100]; //opens memory slots
	int count = 0; //opens int variable 
	readScores(scanned, &count); //pass variables to readScores
	displayScores(scanned, &count); 
	 
	int countH = 0; // new counter to make correctly sized arry
	struct freq sHist[count];//worst case is freq = 1 for each
//	printf("sHist array size: %d\n", count);
	//hist.v = 3;
	//(*(pHistogram +(0))).f = 10;

	calcHistogram(sHist, scanned, &countH, &count);// freq is like the object name sHist is the var
	displayHistogram(sHist, &countH);
	sortHistogram(sHist, &countH);
	displayHistogram(sHist, &countH);
}
/***
 *@param int* pScanned is the pointers to the scanned array
 *@param int* pCount is pointer to the counter
 *
 *
 * This method fills the memory for the array one element at a time.
 * @return void
 * **/
void readScores(int* pScanned, int* pCount){// int* pScanned is Array, int* count is  
	int buffer; // recieves each pointer element
	printf("readScores \n\n");
	while( scanf("%d", &buffer) != EOF) {//while getting legit address before End Of File
		// *pScanned[*count] = buffer;
 
		*(pScanned+(*pCount)) = buffer;// place element into memory slot 
		(*pCount)++; //asks for next  memory slot
		//printf("BUFFER:  %d\n", buffer);// prints current element
	}
	//now the scanned memory slots needed are filled 
	//memory spot count is filled as well
}

void displayScores(int* pScanned, int* pCount){
	printf("displayScores\n\n");// displays 12
	int i = 0;
	while (i < *pCount){
	printf("Score %d: %d\n", i, *(pScanned+(i)));
	i++;
	}	
	printf("\n");

}

void calcHistogram(struct freq* pHistogram, int* pScanned, int* pCountH,  int* pCount){
	int i = 0;
	//printf("Size of pHist: %d\n", *pCount);
	 printf("calcHistogram \n");
	for(i = 0 ; i < *pCount ; i++){ //less than array size
	int val = *(pScanned + i); 
	int j = 0;
	
		while((*(pHistogram + j)).v != val && j < *pCountH){//
		j++;
		}
		
		if( j == *pCountH){
		//(pHistogram + j)->v = val;
		(*(pHistogram + j)).v = val; // new val
		(*(pHistogram + j)).f = 1; // first occurance of val means new frequency
		(*pCountH)++;//increment size of histogram 
		} else {
		(*(pHistogram + j)).f ++;// add freq
		}

	}
	//make structure array 
 	printf("\n"); 

}


void displayHistogram(struct freq* pHistogram, int* pCountH){

//printf("Value: %d\nFrequency: %d\n", (*(pHistogram + (3))).v, (*(pHistogram + (3))).f);
	//printf("Display Scores pCount : %d\n", *pCountH);// displays 12
 	printf("displayHistogram \n");
	int i = 0;
		while (i < *pCountH){
		printf("Value %d: freq %d\n",(*(pHistogram+i)).v, (*(pHistogram + i)).f);
		i++;
		}
 	printf("\n");
}

void sortHistogram(struct freq* pHistogram, int* pCountH){
	//selection sort
	 printf("sortHistogram\n");
	int i, j;
	struct freq temp;//initialize the struct with 0
	for(i = 0; i < *pCountH -1 ; i++){
		for(j= i; j < (*pCountH) - i-1; j++){
		if( (*(pHistogram + j)).f < (*(pHistogram + (j+1))).f ){ //f comparison
		temp = *(pHistogram + j);
		*(pHistogram + j) = *(pHistogram + (j+1));
		*(pHistogram + (j + 1)) = temp;
		//swap(&(*(pHistogram + j).v),&(*(pHistogram + j).f) , &(*(pHistogram + (j+1)).v), &(*(pHistogram + j+1).f));
		}
		}

	}		
	 printf("\n");
}

void swap(int* v1, int* f1, int* v2, int* f2){
	//struct freq t1 = {*v1,*f1};//don't probs need
	//struct freq t2 = {*v2, *f2};
	
	int tempV = *v1;
	int tempF = *f1;
	*v1 = *v2;
	*f1 = *f2;
	*v2 = tempV;
	*f2 = tempF;


}
