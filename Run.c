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