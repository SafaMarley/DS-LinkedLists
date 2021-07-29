//Mehmet Safa Katýrcýoðlu 150118047

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Path {
	char source[10];					//source vertex
	char destination[10];				//destination vertex
	int weight;							//weight of the path
	struct Path* nextPath;
};
struct Path *headPointer = NULL;		//head pointer of linked list
struct Path *currentPointer = NULL;		//current pointer for searching through linked list

struct Edge {
	char name[10];						//name of vertex
	struct Edge* nextEdge;
};
struct Edge *edgeHeadPointer = NULL;
struct Edge *edgeCurrentPointer = NULL;
int sizeOfEdgeArray = 0;				//stores how many unique vertex in the graph

struct Path* createNewPath(char nameSource[10], char nameDestination[10], int weight) {		//creates new Path with given inputs
	struct Path* newPath=(struct Path*)malloc(sizeof(struct Path));			//allocates memory
	
	strcpy(newPath->source, nameSource);				//assigns the input
	strcpy(newPath->destination, nameDestination);
	newPath->weight = weight;
	newPath->nextPath = NULL;
	return newPath;
}

void addNewPath(char nameSource[10], char nameDestination[10], int weight) {		//finds an appropriate position for new Path
	if(headPointer == NULL) {
		headPointer = createNewPath(nameSource, nameDestination, weight);
		currentPointer = headPointer;
	}
	else {
		currentPointer = headPointer;
		while(currentPointer->nextPath != NULL) {
			currentPointer = currentPointer->nextPath;
		}
		currentPointer->nextPath = createNewPath(nameSource, nameDestination, weight);
	}
}

void arrayConstructor(struct Path pathArray[]) {		//constructs an array from linked list
	currentPointer = headPointer;						//resets the current pointer
	int i = 1;
	while(currentPointer != NULL) {
		pathArray[i] = *currentPointer;					//transfers the elemans from linked list to array
		currentPointer = currentPointer->nextPath;
		i++;
	}
}

void heapify(struct Path pathArray[], int size) {		//creates min heap from given array
	int a = 0;
	int b = size;
	while(a < b) {
		while(size > 0) {
			if(size%2 == 1) {
				if(pathArray[size].weight < pathArray[((size-1)/2)].weight) {	//if index is odd
					pathArray[0] = pathArray[size];								//then formulates
					pathArray[size] = pathArray[((size-1)/2)];					//acording to 2n-1
					pathArray[((size-1)/2)] = pathArray[0];
				}
			}
			else if(size%2 == 0) {
				if(pathArray[size].weight < pathArray[(size/2)].weight) {		//if index is even
					pathArray[0] = pathArray[size];								//then formulates
					pathArray[size] = pathArray[(size/2)];						//acording to 2n
					pathArray[(size/2)] = pathArray[0];
				}
			}
			size--;
		}
		size = b;
		a++;
	}
}

void edgeSort(struct Edge edgeArray[], int size) {								//sorts the vertexes in alphabetical order
	int a = 0;
	int b = size;
	while(a < b) {
		while(size > 0) {
			if(strcmp(edgeArray[size].name, edgeArray[(size-1)].name) < 0) {	//sorts with string compare function
				edgeArray[0] = edgeArray[size];
				edgeArray[size] = edgeArray[(size-1)];
				edgeArray[(size-1)] = edgeArray[0];
			}
			size--;
		}
		size = b;
		a++;
	}
}

int isAlreadyExist(char name[10]) {				//returns 1 if given name already exist in linked list
	edgeCurrentPointer = edgeHeadPointer;
	while(edgeCurrentPointer != NULL) {
		if(strcmp(edgeCurrentPointer->name, name) == 0) {
			return 1;
		}
		edgeCurrentPointer = edgeCurrentPointer->nextEdge;
	}
	return 0;
}

struct Edge* createNewEdge(char name[10]) {		//creates new vertex
	struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
	strcpy(newEdge->name, name);
	newEdge->nextEdge = NULL;
	return newEdge;
}

void addEdge(char name[10]) {
	if(edgeHeadPointer == NULL) {					//if the pointer is null then there is no element in linked list
		edgeHeadPointer = createNewEdge(name);
		edgeCurrentPointer = edgeHeadPointer;
		sizeOfEdgeArray++;
	}
	else if(!(isAlreadyExist(name))) {				//add new vertex if it is not already exist
		edgeCurrentPointer = edgeHeadPointer;
		while(edgeCurrentPointer->nextEdge != NULL) {
			edgeCurrentPointer = edgeCurrentPointer->nextEdge;
		}
		edgeCurrentPointer->nextEdge = createNewEdge(name);
		sizeOfEdgeArray++;
	}
}

void edgeArrayConstructor(struct Edge edgeArray[]) {	//constructs vertex array from linked list
	edgeCurrentPointer = edgeHeadPointer;
	int i = 1;
	while(edgeCurrentPointer != NULL) {
		edgeArray[i] = *edgeCurrentPointer;
		edgeCurrentPointer = edgeCurrentPointer->nextEdge;
		i++;
	}
}

void relationFinder(struct Edge edgeArray[], char name[10], int size) {
	int i = 1;												//finds the weight of the edge that connects 2 vertexes if there is no connection writes 0
	int output = 0;
	
	while(i <= size) {
		currentPointer = headPointer;
		while(currentPointer != NULL) {
			if((strcmp(edgeArray[i].name, currentPointer->source) == 0) &&
			(strcmp(name, currentPointer->destination) == 0)) {
				output = currentPointer->weight;
			}
			currentPointer = currentPointer->nextPath;
		}
		printf("\t%d", output);
		output = 0;
		i++;
	}
	printf("\n");
}

void matrixPrinter(struct Edge edgeArray[], int size) {			//prints the connections between vertexes
	currentPointer = headPointer;
	int i = 1;
	int k = 1;
	while(i <= size) {
		printf("\t%s", edgeArray[i].name);
		i++;
	}
	while(k <= size) {
		printf("\n%s", edgeArray[k].name);
		relationFinder(edgeArray, edgeArray[k].name, size);
		k++;
	}
	
}

void dijkstraAlgorithm(struct Path pathArray[], int size, char tempSource[10], char tempDestination[10], int weight) {
	char source[10];					//finds the shortest path between two nodes
	char destination[10];
	
	int j = 0;
	while(j < 10) {
		source[j] = toupper(tempSource[j]);
		destination[j] = toupper(tempDestination[j]);
		j++;
	}
	char allOftheDestinations[size][10];
	int weightOfTheDestinations[size];
	int i = 0;
	while(i <= size) {
		if((strcmp(pathArray[i].source, source)) == 0) {
			if((strcmp(pathArray[i].destination, destination)) == 0) {
				weight += pathArray[i].weight;
				printf("hit from %s to %s with weight=%d\ttotal weight=%d\n", pathArray[i].source, destination, pathArray[i].weight, weight);
			}
			else{
				strcpy(allOftheDestinations[i], pathArray[i].destination);
				weightOfTheDestinations[i] = pathArray[i].weight;
				int tempWeight = weight;
				weight += pathArray[i].weight;
				printf("from %s to %s with weight=%d\n", pathArray[i].source, allOftheDestinations[i], pathArray[i].weight);
				dijkstraAlgorithm(pathArray, size, allOftheDestinations[i], destination, weight);
				weight = tempWeight;
			}
		}
		i++;
	}
}

int main(int argc, char *argv[]) {
	int sizeOfArray = 0;
	int menuChoice = 0;
	FILE *filePointer;
	
	while (menuChoice != 4) {
		printf("1-Enter the input file\n2-Show adjacency matrix\n3-Find shortest path\n4-Exit\nYour choice:");		//prints the menu
		scanf("%d", &menuChoice);
		if(menuChoice == 1) {
			char nameOfInputFile[50];
			scanf("%s", &nameOfInputFile);
			filePointer = fopen(nameOfInputFile, "r");
			if(filePointer == NULL) {
				printf("no such file exist\n");			//if the given file name doesn't exist
			}
			else {
				while(!feof(filePointer)) {
					sizeOfArray++;					//size of array indicates that how many connections are there in the graph
					char source[10];
					char destination[10];
					char tempWeight[5];
					char lineOfInputFile[25];
					fgets(lineOfInputFile, 25, filePointer);
					
					strcpy(source, strtok(lineOfInputFile,","));
					strcpy(destination, strtok(NULL,","));
					strcpy(tempWeight, strtok(NULL,","));
					
					int weight = atoi(tempWeight);
					
					addNewPath(source, destination, weight);
				}
			}
		}
		else if(menuChoice == 2) {
			if(sizeOfArray == 0) {
				printf("Enter an input file first.\n");
			}
			else {
				currentPointer = headPointer;
				
				while(currentPointer != NULL) {		//creates the vertexes both source and destination
					addEdge(currentPointer->source);
					addEdge(currentPointer->destination);
					
					currentPointer = currentPointer->nextPath;
				}
				
				struct Edge edgeArray[sizeOfEdgeArray];
				edgeArrayConstructor(edgeArray);
				
				edgeSort(edgeArray, sizeOfEdgeArray);

				matrixPrinter(edgeArray, sizeOfEdgeArray);
			}
		}
		else if(menuChoice == 3) {
			if(sizeOfArray == 0) {
				printf("Enter an input file first.\n");
			}
			else {
				char sourceVertex[10];
				char destinationVertex[10];
				printf("Enter the source vertex: ");
				scanf("%s", &sourceVertex);
				printf("Enter the destination vertex: ");
				scanf("%s", &destinationVertex);
				
				struct Path pathArray[sizeOfArray];
				arrayConstructor(pathArray);

				heapify(pathArray, sizeOfArray);
				
				dijkstraAlgorithm(pathArray, sizeOfArray, sourceVertex, destinationVertex, 0);
			}
		}
		else {
			printf("Wrong input!");
		}
	}
	return 0;
}
