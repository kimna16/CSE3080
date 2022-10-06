#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 1000000

typedef struct {
	int key;
}element;

element maxheap[MAX_ELEMENTS];
element minheap[MAX_ELEMENTS];
element copymaxheap[MAX_ELEMENTS];
element copyminheap[MAX_ELEMENTS]

int maxheap_number = 0;
int minheap_number = 0;

void print_maxheap();
void print_minheap();
void insert_element(element item, int* maxheap_number, int* minheap_number);
element delete_maxheap(int* maxheap_number);
element delete_minheap(int* minheap_number);

void main(int argc, char **argv) {

	if (argc > 2) {
		printf("usage: ./hw2 input_filename\n");
		exit(1);
	}

	FILE* fp;
	fp = fopen(argv[1], "r");
	if (!fp) {
		printf("The input file does not exist.\n");
		exit(1);
	}

	clock_t start, end;
	double duration;

	start = clock();

	element item;
	int key;
	char c;
	int tempnumber;

	while (1) {
		if (feof(fp) != 0)
			break;
		else {
			fscanf(fp,"%c", &c);
			if (c == 'I') {
				for (int i = 0; i < 6; i++) {
					fscanf(fp, "%c", &c);
				}
				fscanf(fp, "%d", &key);
				item.key = key;
				insert_element(item, &maxheap_number, &minheap_number);
			}
			else if (c=='D') {
				for (int i = 0; i < 7; i++) {
					fscanf(fp, "%c", &c);
				}
				tempnumber = maxheap_number;
				print_maxheap();
				maxheap_number = tempnumber;
			}
			else if (c=='A') {
				for (int i = 0; i < 6; i++) {
					fscanf(fp, "%c", &c);
				}
				tempnumber = minheap_number;
				print_minheap();
				minheap_number = tempnumber;
			}
		}

	}
	fclose(fp);

	end = clock();
	duration = end - start;

	fprintf(stderr, "output written to hw2_result.txt.\n");
	fprintf(stderr, "running time: %f seconds\n", duration / CLOCKS_PER_SEC);

}
void insert_element(element item, int* maxheap_number, int* minheap_number) { 
	int i;

	i = ++(*maxheap_number);
	while ((i != 1) && (item.key > maxheap[i / 2].key)) {
		maxheap[i] = maxheap[i / 2];
		i /= 2;
	}
	maxheap[i] = item;

	i = ++(*minheap_number);
	while ((i != 1) && (item.key < minheap[i / 2].key)) {
		minheap[i] = minheap[i / 2];
		i /= 2;
	}
	minheap[i] = item;
}
void print_maxheap() {
	element item;
	int count = maxheap_number;
	
	for (int i = 1; i <= maxheap_number; i++) {
		copymaxheap[i] = maxheap[i];
	}

	FILE* fp;
	fp = fopen("hw2_result.txt", "a");
	for (int i = 1; i <= count; i++) {
		item = delete_maxheap(&maxheap_number);
		fprintf(fp, "%d ", item.key);
	}
	fprintf(fp, "\n");
	fclose(fp);

	for (int i = 1; i <= count; i++) {
		maxheap[i] = copymaxheap[i];
	}
}
void print_minheap() {
	element item;
	int count = minheap_number;
	
	for (int i = 1; i <= minheap_number; i++) {
		copyminheap[i] = minheap[i];
	}

	FILE* fp;
	fp = fopen("hw2_result.txt", "a");
	for (int i = 1; i <= count; i++) {
		item = delete_minheap(&minheap_number);
		fprintf(fp, "%d ", item.key);
	}
	fprintf(fp, "\n");
	fclose(fp);

	for (int i = 1; i <= count; i++) {
		minheap[i] = copyminheap[i];
	}
}
element delete_maxheap(int *maxheap_number) {
	int parent, child;
	element item, temp;

	item = maxheap[1];
	temp = maxheap[(*maxheap_number)--];
	parent = 1;
	child = 2;
	while (child <= *maxheap_number) {
		if ((child < *maxheap_number) && (maxheap[child].key < maxheap[child + 1].key)) child++;
		if (temp.key >= maxheap[child].key) break;
		maxheap[parent] = maxheap[child];
		parent = child;
		child *= 2;
	}
	maxheap[parent] = temp;
	return item;
}
element delete_minheap(int *minheap_number) {
	int parent, child;
	element item, temp;

	item = minheap[1];
	temp = minheap[(*minheap_number)--];
	parent = 1;
	child = 2;
	while (child <= *minheap_number) {
		if ((child < *minheap_number) && (minheap[child].key > minheap[child + 1].key)) child++;
		if (temp.key <= minheap[child].key) break;
		minheap[parent] = minheap[child];
		parent = child;
		child *= 2;
	}
	minheap[parent] = temp;
	return item;
}