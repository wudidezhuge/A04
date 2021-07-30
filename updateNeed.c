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