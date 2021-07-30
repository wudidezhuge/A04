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