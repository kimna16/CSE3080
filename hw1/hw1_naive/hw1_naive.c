#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 9999999
#define MAX_PATTERN 2999

char string[MAX_STRING];
char pattern[MAX_PATTERN];
int position[MAX_STRING];

int findmatchingpoint(char* str, char* pat, int m, int n, int* position); //by using naive algorithm

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

	RESULT = fopen("result_naive.txt", "w");

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

	int arraynumber = findmatchingpoint(str, pat, m, n, position); 

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

	printf("Program completed. Result saved to result_naive.txt.\n");

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
		printf("result_naive.txt file is not closed.\n");
		exit(1);
	}

	return 0;
}
int findmatchingpoint(char* str, char* pat, int m, int n, int* position) {
	int lastindex_pat = n - 1;
	int lastindex_str = m - 1;
	int startindex, endindex = lastindex_pat;
	int checkindex;

	int arraynumber = 0;
	int i, j;

	for (i = 0; i <= m - n; i++) {
		startindex = i;
		checkindex = startindex;
		endindex = i + lastindex_pat;
		if (pat[0] == str[startindex] && pat[lastindex_pat] == str[endindex]) {
			for (j = 0; j < lastindex_pat; j++) {
				if (str[checkindex] == pat[j])
					checkindex++;
				else
					break;
			}
			if (j == lastindex_pat) {
				position[arraynumber] = startindex;
				arraynumber++;
			}
		}
	}

	return arraynumber;
}