#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ONE_LINE_MAX_CHAR 100
#define MAX_LINE 100
#define MAX_RES_NUM 100
#define MAX_CUSTOMER 100
#define COMMAND_MAX_CHAR 100
int available[MAX_RES_NUM] = {0};
int maximum[MAX_CUSTOMER][MAX_RES_NUM] = {0};
int allocated[MAX_CUSTOMER][MAX_RES_NUM] = {0};
int need[MAX_CUSTOMER][MAX_RES_NUM] = {0};
int customerIndexSeq[MAX_CUSTOMER] = {0};
int customerNumber = 0;
int resourceNumber = 0;

int initMaximum();
void printStartInfo();
void execRQ();
int bankAlgorithm();
void execRL();
void execStatus();
void updateNeed();
void execRun();
void run();

int main(int argc,char * argv[]) {
    resourceNumber = argc-1;
    for(int i = 0; i < resourceNumber; ++i){
        available[i] = atoi(argv[i+1]);
    }
    customerNumber = initMaximum();
    updateNeed();
    printStartInfo();
    run();
	return 0;
}

int initMaximum(){
    int customerCount = 0;
    FILE *fp = fopen("./sample4_in.txt","r");
    char content[ONE_LINE_MAX_CHAR];
    char *contents[MAX_LINE];
    while(!feof(fp)){
        if(fgets(content,ONE_LINE_MAX_CHAR,fp) != NULL){
            contents[customerCount] = malloc(sizeof(content) * sizeof(char));
            strcpy(contents[customerCount], content);
            customerCount++;
        }
    }
	for (int i = 0; i < customerCount; ++i) {
		char *token = NULL;
		token = strtok(contents[i], ",");
        int j = 0;
		while (token != NULL) {
            maximum[i][j] = atoi(token);
			token = strtok(NULL, ",");
            j++;
		}
	}
    return customerCount;
}

void printStartInfo(){
    printf("Number of Customer: %d \n",customerNumber);
    printf("Currently Available resources:");
    for(int i = 0; i < resourceNumber; ++i){
        printf(" %d",available[i]);
    }
    printf("\n");
    printf("Maximum resources from file:\n");
    for(int i = 0; i < customerNumber; ++i){
        for(int j = 0; j < resourceNumber; ++j){
            printf("%d ",maximum[i][j]);
        }
        printf("\n");
    }
}
void run(){
    char command[COMMAND_MAX_CHAR];
    while(1){
        printf("Enter Command:");
        scanf("%s",command);
        if(strcmp(command,"RQ") == 0){
            execRQ();
        }
        else if(strcmp(command,"RL") == 0){
            execRL();
        }
        else if(strcmp(command,"Status") == 0){
            execStatus();
        }
        else if(strcmp(command,"Run") == 0){
            execRun();
        }
        else if(strcmp(command,"Exit") == 0){
            break;
        }
    }
}
void execRQ(){
    int customerIndex;
    int rqCount[resourceNumber];
    scanf("%d",&customerIndex);
    for(int i = 0; i < resourceNumber; ++i){
        int resCount;
        scanf("%d",&resCount);
        allocated[customerIndex][i] += resCount;
        available[i] -= resCount;
        rqCount[i] = resCount;
    }
    updateNeed();
    if(bankAlgorithm() == 1){
        printf("State is safe, and request is satisfied\n");
    }
    else{
        for(int i = 0; i < resourceNumber; ++i){
            available[i] += rqCount[i];
            allocated[customerIndex][i] -= rqCount[i];
        }
        updateNeed();
    }
}

void execRL(){
    int customerIndex;
    scanf("%d",&customerIndex);
    for(int i = 0; i < resourceNumber; ++i){
        int resCount;
        scanf("%d",&resCount);
        allocated[customerIndex][i] -= resCount;
        available[i] += resCount;
    }           
    updateNeed();
    printf("The resources have been released successfully\n") ;
}

int bankAlgorithm(){
    int work[MAX_RES_NUM]={0};
    int finish[MAX_CUSTOMER]={0};
    int currentFinshNum = 0;
    for(int i = 0; i < MAX_RES_NUM; ++i){
        work[i] = available[i];
    }
    while(1){
        int isExistValid = 0;
        for(int i = 0; i < customerNumber; ++i){
            if(finish[i] == 1 ){
                continue;
            }
            int resourceSuf = 1;
            for(int j = 0; j < resourceNumber; ++j){
                if(need[i][j] > work[j]){
                    resourceSuf = 0;
                    break;
                }
            }
            if(resourceSuf == 1){
                for(int m = 0; m < resourceNumber; ++m){
                    work[m]+= allocated[i][m];
                }
                finish[i] = 1;
                customerIndexSeq[currentFinshNum] = i;
                currentFinshNum++;
                isExistValid = 1;
                break;
            }
        }        
        if(isExistValid == 0){
            return 0;
        }
        if(currentFinshNum == customerNumber){
            return 1;
        }
    }
    return 0;
}

void updateNeed(){
    for(int i = 0; i < customerNumber; ++i){
        for(int j = 0; j < resourceNumber; ++j){
            need[i][j] = maximum[i][j] - allocated[i][j];
        }
    }
}

void execStatus(){
    printf("Available Resources:\n");
    for(int i = 0; i < resourceNumber; ++i){
        printf("%d ",available[i]);
    }
    printf("\n");
    printf("Maximum Resources:\n");
    for(int i = 0; i < customerNumber; ++i){
        for(int j = 0; j < resourceNumber; ++j){
            printf("%d ",maximum[i][j]);
        }
        printf("\n");
    }
    printf("Allocated Resources:\n");
    for(int i = 0; i < customerNumber; ++i){
        for(int j = 0; j < resourceNumber; ++j){
            printf("%d ",allocated[i][j]);
        }
        printf("\n");
    }    
    printf("Need Resources:\n");
    for(int i = 0; i < customerNumber; ++i){
        for(int j = 0; j < resourceNumber; ++j){
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }    
}

void execRun(){
    if(bankAlgorithm() == 1){
        printf("Safe Sequence is:");
        for(int i = 0; i < customerNumber; ++i){
            printf(" %d",customerIndexSeq[i]);
        }
        printf("\n");
        for(int i = 0; i < customerNumber; ++i){
            printf("--> Customer/Thread %d\n",customerIndexSeq[i]);
            printf("Allocated resources:");
            for(int k = 0;k < resourceNumber; ++k){
                printf(" %d",allocated[customerIndexSeq[i]][k]);
            }
            printf("\n");
            printf("Needed:");
            for(int j = 0; j < resourceNumber; ++j){
                printf(" %d",maximum[customerIndexSeq[i]][j] - allocated[customerIndexSeq[i]][j]);
            }
            printf("\n");
            printf("Available:");
            for(int j = 0; j < resourceNumber; ++j){
                printf(" %d",available[j]);
            }
            printf("\n");
            printf("Thread has started\n");
            printf("Thread has finished\n");
            printf("Thread is releasing resources\n");
            for(int j = 0; j < resourceNumber; ++j){
                available[j] += allocated[customerIndexSeq[i]][j];
            }
            printf("New Available:");
            for(int j = 0; j < resourceNumber; ++j){
                printf(" %d",available[j]);
            }
            printf("\n");
        }
    }        
}