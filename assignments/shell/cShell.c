#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
#include<sys/msg.h>
#include<dirent.h>
#include"linkedList.h"
#define _GNU_SOURCE
#include <unistd.h>

/*Get extra credit by 
 *		1. get rid of break in this function
 *		2. add a history command
 *			i. list last 25 commands run
 *			ii. !5 = execute 5th item from history list
 *
 * */


//buffer is the input string of characters
//args is the output array of arguments. Already created with argSize slots.
//nargs as the number filled in that is passed back

void parseArgs(char *buffer, char** args, int argsSize, int *nargs) {
 char *bufArgs[argsSize];
 char **cp;
 char *wbuf;
 int i, j;
 wbuf=buffer;
 bufArgs[0]=buffer;
 args[0]=buffer;

	for(cp=bufArgs; (*cp=strsep(&wbuf, " \n\t")) != NULL ;){
 		if ((*cp != '\0') && (++cp >= &bufArgs[argsSize]))
 		 break;
 		}
 		for (j=i=0; bufArgs[i]!=NULL; i++){
 			if(strlen(bufArgs[i])>0)
		 args[j++] = bufArgs[i];
		}
//Add the NULL as the end argument bc we need that for later
 *nargs=j;
 args[j]=NULL;

}

int isAND(char** input){ //will delete at index as well 
 char* in = input[0];
 int i = 0;
 int isAND = 0;
         if(input[1] == NULL){
          isAND = 0;

         } else {
                 while(in != NULL && isAND == 0){
                  i++;
                  in = input[i];
                         if(strcmp(input[i],"&") == 0){
                          isAND = i;
                         }
                 }
         }
//  input[i] = NULL; // deletes & so parse can be used 
  printf("contains & = %d\n", isAND);
return isAND;

}

int hasToken(char** input){
 char* in = input[0];
 int i =0;
 int isToken = 0;
 	if(input[1] == NULL){
 	 isToken = 0;

	} else { 
		while(in != NULL && isToken == 0){
		 i++;
		 in = input[i];
			if(strcmp(input[i],">") == 0){
			 isToken = i;
			} else if(strcmp(input[i],"<") == 0){
			 isToken = -1 * i; //returns status and also args locaton in one method
			}
		}
	}
 printf("TOKEN = %d\n",isToken);
 return isToken;
}


void handler(int signal){
	waitpid(-1, 0, WNOHANG);
	//printf("result = %d\n", result);
}
/*
void concatArry(char** cat, char** arry){ //cat is malloc'd to be able to be edited
 int i = 0;
 printf("1 \n");
	if(arry[1] == NULL){
	 strcpy(*cat,arry[0]); // just copy first element 
	} else if (arry[2] == NULL){
	 printf("2\n");
	 char temp1[25];
	 char temp2[25];

	 strcpy(temp2, arry[1]); //avoid messing up original
	 strcpy(temp1, arry[0]);//first char
	 strcat(temp1, " "); //format
	 strcat(temp1, temp2); // add second char
	 strcat(*cat,temp1); //move from temp
	printf("3 \n");
	} else { //ex ps > foo.txt
	printf("4 \n");
		strcpy(*cat,arry[0]); //ps
		strcat(*cat," ");// format ps_
		i++;//1
		while(arry[i] != NULL){	
		 printf("i = %d\n",i); 
        	 char temp2[25]; 
       		 strcpy(temp2, arry[i]); //avoid messing up original // temp = >
		 strcat(*cat,temp2);//ps_>_foo.txt
         	 strcat(*cat, " "); //format // ps_>_
		 i++;
		}
	}
 cat[i] = "\0"; // append null terminating char

printf("CAT = %s\n", *cat);
}
*/


int main(){
 int exitCall = 0;
 int background = 0;
 //history should be a queue and every add after 25 pushes front off 
 int histCount = 0; //if = 25 drop front then add
 LinkedList* historyList = llCreate();

 	while(exitCall == 0){
	 char cwd[50];//random amount of accepted chars
	 getcwd(cwd, sizeof(cwd));
	 printf("%s> ",cwd);//filename prompt
	 int ex = 0;	 
 	 char buffer[127];
 	 char* args[127]; 
 	 int nargs;
 	 fgets(buffer,127,stdin);//(where to save, max chars,input area) 
 		if(strcmp(buffer, "\n")==0){		 
		 printf("try agian next time\n");

		} else if (strcmp(buffer, "exit\n") == 0 ){
		 printf("exiting process \n");
		 exitCall = 1;
		 ex = 1;
		} else {//start asking fpr actual arguments		
 	 	 parseArgs(buffer, args, 25, &nargs);
 	 	 printf(" args[0] = %s\n", args[0]);// args[0] should be buffer?
	 		int isAnd = isAND(args); // if 0 then no & 
			if(isAnd != 0){
			 args[isAnd] = NULL; // delete & so you can run
			 background = 1;
			 signal(SIGCHLD, handler); // start up handler
			} else {
			 background = 0; // if it's not a background function reset background
			}
		/*cd*/
			if(strcmp(args[0], "cd") == 0){// cd
				printf("HERE \n"); 
			 	if(args[1] == NULL){ //cd entered 
				 printf("\n\n\tShell unable to find home directories \n\tPlease enter valid path\n\n");
				} else { //args[1] exists
				 char temp0[125];
				 strcpy(temp0, args[0]);
				 strcat(temp0," ");
				 char temp1[125];
				 strcpy(temp1, args[1]);
				 strcat(temp0,temp1);
				 char* temp3 = (char*) malloc(1 * sizeof(temp0));
				 strcpy(temp3,temp0); 
			//	 printf("\n\n\nTEMP 3 %s\n", temp3);
				 	if(histCount > 25){
				//	 printf(">25\n");
				 	 llRemoveTop(&historyList);
				 	 llAdd(&historyList, &temp3);
					 histCount++;
				 	} else {
				//	 printf("LESS THAN 25\n");
					 llAdd(&historyList, &temp3);
					 histCount++;
					}
				 
			 	 int changeDir = chdir(args[1]);
			 		if(changeDir != 0){
				  	 printf("Unable to change Directories \nPlease try again\n\n");
					}
				}
			 ex = 1;//did something so pass execvp
		/*history queue*/
			} else if(strcmp(args[0], "history") == 0){
				char* temp = "history";
				llDisplay(historyList);
				if(histCount > 25){
				 llRemoveTop(&historyList);
				 llAdd(&historyList, &temp);
				 histCount++;
				} else {
				 llAdd(&historyList, &temp);
				 histCount++;
				}	
			ex = 1;
		/*!5 item execute*/
			} else if(strcmp(args[0], "!5") == 0){
				char* temp = "!5";
				if(histCount < 5){
				 printf("\tERROR: You haven't had 5 commands yet\n");
				} else if (histCount > 25){
				 //char* cmd = llGetAtIndex(historyList,histCount);
				 parseArgs(buffer, args, 25, &nargs);
				 llRemoveTop(&historyList);
				 llAdd(&historyList, &temp);
				 //printf("!5 command executed:\t %s\n",cmd);
				 histCount++;
				} else {
				// char* cmd = llGetAtIndex(historyList, histCount);
				 parseArgs(buffer, args, 25, &nargs);
				 llAdd(&historyList, &temp);
				 histCount++;
				 //printf("!5 command executed:\t %s\n",cmd);
				} //parse passes to fork
			
		/*BEGIN FORKS*/
			} else if(ex != 1 ){
				//concat
				/*char* temp = args[0]; 
				int index = 1;
				strcpy(temp, args[0]); //throw first concat in
				while(index < nargs){
				 char* innerTemp;
				 strcpy(innerTemp, args[index]);
				 strcat(temp, " " );
				 strcat(temp, innerTemp);
				 index++;
				}
				printf("TEMP = %s\n",temp);
				if(histCount > 25){
                                 //printf(">25\n");
                                 llRemoveTop(&historyList);
                                 llAdd(&historyList, &temp);
                                 histCount++;
                                } else {
                                 //printf("LESS THAN 25\n");
                                 llAdd(&historyList, &temp);
                                 histCount++;
                                }*/
	
			 int pid = fork();
			 int tk = hasToken(args);			
			 	if(pid == -1){
				 printf("\tEEROR: PROCESS FAILED\n");
				
				} else if (pid == 0 && tk == 0) {
				 printf("EXECUTE \n\n");
				 execvp(args[0], args); 
				
				} else if(pid == 0 && tk != 0){ //has <
					 printf("\tHAS TOKEN\n ");
			 		 int token = hasToken(args);
					 char input[25];
					 char output[25];
					 FILE* fInput;
					 FILE* fOutput;
						if(token < 0){// input
					
				 		 token = -1 * token;
						 printf("token contains < at %d\n",token);
				 		 strcpy(input, args[token + 1]);// path
						 args[token + 1] = NULL;
						 args[token] = NULL;
						 fInput = freopen(input, "r", stdin);
						 execvp(args[0], args); 
						 fclose(fInput);
						} else if(token > 0) {//output
						
						 strcpy(output, args[token+1]);
						 printf("output = %s\n",output);
						 args[token + 1] = NULL;
						 args[token] = NULL;
						 fOutput = freopen(output, "w",stdout); // path	
						 execvp(args[0], args);
						 fclose(fOutput);

						}

					 //printf("original execvp \n");
					// execvp(args[0], args);	
				} else { 
				//parent
				 	if(background == 0){ //if background isn't going then do the next thing
				 	 int reapBuf;
				 	 waitpid(pid, &reapBuf,0);
					}
				}
			 ex = 0;
			}
		}
	} 
 llFreeAll(&historyList);
 return 0;
}



