#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 9999999
#define MAX_PATTERN 2999

char string[MAX_STRING];
char pattern[MAX_PATTERN];
int failure[MAX_PATTERN];
int position[MAX_STRING];

int failurefunction(int* failure, char* pat, int n); //return the value of failure[n-1]
int findmatchingpoint(char* str, char* pat, int* failure, int m, int n, int value, int* position); //by using kmp algorithm

int main() {

	FILE* STRING;
	FILE* PATTERN;
	FILE* RESULT;

	STRING = fopen("string.txt", "r");
	PATTERN = fopen("pattern.txt", "r");

	if (STRING == NULL) {
		printf("String file does not exist. Unable to execute Naive Algorithm.\n");
		exit(1);
	}
	else if (PATTERN == NULL) {
		printf("Pattern file does not exist. Unable to execute Naive Algorithm.\n");
		exit(1);
	}

	RESULT = fopen("result_kmp.txt", "w");

	char* str = fgets(string, MAX_STRING, STRING);
	char* pat = fgets(pattern, MAX_PATTERN, PATTERN);

	int m = strlen(str); //m is the length of the string
	if (str[m - 1] == '\n') {
		str[m - 1] = '\0';
		m = m - 1;
	}
	int n = strlen(pat); //n is the length of the pattern 
	if (pat[n - 1] == '\n') {
		pat[n - 1] = '\0';
		n = n - 1;
	}

	int value = failurefunction(failure, pat, n);
	int arraynumber = findmatchingpoint(str, pat, failure, m, n, value, position); 

	if (arraynumber != 0) {
		fprintf(RESULT, "%d\n", arraynumber);
		for (int i = 0; i < arraynumber; i++) {
			fprintf(RESULT, "%d ", position[i]);
		}
		fprintf(RESULT, "\n");
	}
	else {
		fprintf(RESULT, "Pattern %s is not in String %s.\n",pat,str);
	}

	printf("Program completed. Result saved to result_kmp.txt.\n");

	int closeS, closeP, closeR;
	closeS = fclose(STRING);
	closeP = fclose(PATTERN);
	closeR = fclose(RESULT);

	if (closeS != 0) {
		printf("string.txt file is not closed.\n");
		exit(1);
	}
	if (closeP != 0) {
		printf("pattern.txt file is not closed.\n");
		exit(1);
	}
	if (closeR != 0) {
		printf("result_kmp.txt file is not closed.\n");
		exit(1);
	}

	return 0;
}
int failurefunction(int* failure, char* pat, int n) {
	int i;
	failure[0] = -1; //value of the first index of failure function is always -1.
	
	for (int j = 1; j < n; j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0))
			i = failure[i];
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else
			failure[j] = -1; 
	}

	return failure[n - 1];
}
int findmatchingpoint(char* str, char* pat, int* failure, int m, int n, int value, int* position) {
	int arraynumber = 0;
	int i = 0, j = 0;
	
	while (i < m && j < n) {
		if (str[i] == pat[j]) {
			i++;
			j++;
		}
		else {
			if (j == 0)
				i++;
			else
				j = failure[j - 1] + 1;
		}

		if (j == n) {
			position[arraynumber] = i - n; //add starting index of fully matched pattern in string into position array. 
			arraynumber++;

			if (value == -1)
				j = 0;
			else
				j = value + 1;
		}
	}
	
	return arraynumber;
}
