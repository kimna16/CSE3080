#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10000
#define MAX_EDGES 50000000

typedef struct {
	int weight;
	int u;
	int v;
}element;

element minheap_edge[MAX_EDGES];

int edge_number;
int vertex_number;
int remainEdge_number = 0;      
int printEdge_number = 0;
int totalcost = 0;
int parent[MAX_VERTICES];

void insert_minheap(element, int*);
element delete_minheap(int*);
int Check(element);
int Find(int);
void WeightedUnion(int, int);

void main(int argc, char** argv) {

	if (argc != 2) {
		printf("usage: ./hw3 input_filename\n");
		exit(1);
	}

	FILE* fp1;
	fp1 = fopen(argv[1], "r");

	if (!fp1) {
		printf("The input file does not exist.\n");
		exit(1);
	}

	clock_t start, end;
	double duration;

	start = clock();

	element item;
	int u, v, weight;

	fscanf(fp1, "%d", &vertex_number);
	fscanf(fp1, "%d", &edge_number);

	for (int i = 0; i < edge_number; i++) {
		fscanf(fp1, "%d %d %d", &u, &v, &weight);
		item.u = u;
		item.v = v;
		item.weight = weight;
		insert_minheap(item, &remainEdge_number);
	}

	fclose(fp1);

	FILE* fp2;
	fp2 = fopen("hw3_result.txt", "a");

	for (int i = 0; i < vertex_number; i++) {
		parent[i] = -1;
	}

	while (printEdge_number < vertex_number - 1 && remainEdge_number != 0) {
		item = delete_minheap(&remainEdge_number);
		if (Check(item)) {
			printEdge_number++;
			totalcost += item.weight;
			fprintf(fp2, "%d %d %d\n", item.u, item.v, item.weight);
		}
	}
	fprintf(fp2, "%d\n", totalcost);

	int check = 0;

	for (int i = 0; i < vertex_number; i++) {
		if (parent[i] < 0) {
			if (parent[i] == (-1) * vertex_number) {
				check = 1;
			}
			else
				check = 0;
		}
	}
	if (check) {
		fprintf(fp2, "CONNECTED\n");
	}
	else {
		fprintf(fp2, "DISCONNECTED\n");
	}

	fclose(fp2);

	end = clock();
	duration = end - start;

	printf("output written to hw3_result.txt.\n");
	printf("running time: %f seconds\n", duration / CLOCKS_PER_SEC);

}
void insert_minheap(element item, int* remainEdge_number) {
	int i;
	i = ++(*remainEdge_number);

	while ((i != 1) && (item.weight < minheap_edge[i / 2].weight)) {
		minheap_edge[i] = minheap_edge[i / 2];
		i /= 2;
	}
	minheap_edge[i] = item;
}
element delete_minheap(int* remainEdge_number) {
	int parent, child;
	element item, temp;

	item = minheap_edge[1];
	temp = minheap_edge[(*remainEdge_number)--];
	parent = 1;
	child = 2;
	while (child <= *remainEdge_number) {
		if ((child < *remainEdge_number) && (minheap_edge[child].weight > minheap_edge[child + 1].weight)) child++;
		if (temp.weight <= minheap_edge[child].weight) break;
		minheap_edge[parent] = minheap_edge[child];
		parent = child;
		child *= 2;
	}
	minheap_edge[parent] = temp;
	return item;
}
int Find(int i) {
	for (; parent[i] >= 0; i = parent[i]) {
		;
	}
	return i;
}
void WeightedUnion(int i, int j) {
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) {
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
	}
}
int Check(element item) {
	if (Find(item.u) == -1 && Find(item.v) == -1) {
		WeightedUnion(item.u, item.v);
		return TRUE;
	}
	else if (Find(item.u) != Find(item.v)) {
		WeightedUnion(Find(item.u), Find(item.v));
		return TRUE;
	}
	else
		return FALSE;
}