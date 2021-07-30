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