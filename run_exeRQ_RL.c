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
