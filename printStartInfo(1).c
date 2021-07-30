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