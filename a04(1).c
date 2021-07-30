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