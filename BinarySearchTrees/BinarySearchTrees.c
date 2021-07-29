//Mehmet Safa Katýrcýoðlu 150118047
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct element {
	int number;
	char word[25];
	int frequency;
	struct element *left;
	struct element *right;
};

struct element* newElement(int number, char word[25], int frequency) {			//this method creates a new element
	struct element* element=(struct element*)malloc(sizeof(struct element));
	element->number=number;
	strcpy(element->word,word);
	element->frequency=frequency;
	element->left=NULL;
	element->right=NULL;
	return(element);
}

struct element* treeBuilder(int number, char word[25], int frequency, struct element* spot) {	//this method builds a tree by using the given data
	if(spot == NULL) {													//when it finds the right spot it calls the new element to create the element
		spot = newElement(number, word, frequency);
	}
	else if((stricmp(spot->word,word)) > 0) {							//determines the right spot for given element
		spot->left = treeBuilder(number, word, frequency, spot->left);
	}
	else if((stricmp(spot->word,word)) <= 0) {							//determines the right spot for given element
		spot->right = treeBuilder(number, word, frequency, spot->right);
	}
	return spot;
}

/*void treeBuilder(int number, char word[25], int frequency,struct element *root) {		this method was the first method i tried to create tree but it didnt work and i didnt want to delete it so here it is in comment
	//printf("%d:%s:%d\n",number,word,frequency);
	//printf("%d-%s-%d\n",root->number,root->word,root->frequency);
	struct element *spot;
	spot = root;

	while(spot != NULL || spot != NULL){
		if((stricmp(root->word,word)) > 0) {
			spot = spot->left;
		}
		else if((stricmp(root->word,word)) <= 0) {
			spot = spot->right;
		}
	}
	spot = newElement(number,word,frequency);
	//printf("1%s\n",spot->word);
}*/

void printTree(struct element *spot) {			//prints the tree in lnr format
	if(spot != NULL) {
		printTree(spot->left);
		printf("%s %d\n",spot->word, spot->frequency);
		printTree(spot->right);

	}
}

int totalTime = 0;
int totalTimeCalculator(int depth,struct element *spot) {		//calculates the accesstime by multipling depth+1 and frequency of the element(i am starting depth value at 1 so i am calculating this by depth * frequency)
	if(spot != NULL) {
		totalTime += ((depth)*(spot->frequency));
		totalTimeCalculator(depth+1, spot->left);
		totalTimeCalculator(depth+1, spot->right);
	}
	return totalTime;
}

int i = 0;
void arrayBuilder(struct element *elementArray, struct element *spot) {		//fills the array by using the elements of the tree we need this array because we have to sort it by their frequency
	if(spot != NULL) {
		elementArray[i].frequency = spot->frequency;
		elementArray[i].number = spot->number;
		strcpy(elementArray[i].word, spot->word);
		i++;
		arrayBuilder(elementArray, spot->left);
		arrayBuilder(elementArray, spot->right);
	}
}

void sortArray(struct element *elementArray, int sizeOArray) {				//this is bubble sorting algorithm that sorts our array by their frequency(first index(root) has the greatest frequency)
	int j,k;
	for(j = 0; j < (sizeOArray - 1); j++) {
		for(k = 0; k < (sizeOArray - 1); k++) {
			if(elementArray[k].frequency < elementArray[k+1].frequency) {
				struct element temp = elementArray[k];
				elementArray[k] = elementArray[k+1];
				elementArray[k+1] = temp;
			}
		}
	}
}

struct element* arrayBBuilder(struct element* elementArray,struct element* spot, int l, int lineCounter) {			//this method creates a tree by using the sorted element array
	if(l < lineCounter) {
		struct element* temp = &elementArray[l];
		spot = temp;
		spot->left = arrayBBuilder(elementArray, spot->left, (2*l)+1, lineCounter);								//the idea of (2*l)+1 and (2*l)+2, is putting the elements into the tree in order
		spot->right = arrayBBuilder(elementArray, spot->right, (2*l)+2, lineCounter);
		return spot;
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	struct element *root;			//pointer that points the root of our tree
	struct element *begining;		//pointer that points the 0th index of out array
	char allTemp[35];				//all line of the input text
	char cNumTemp[5];
	char wordTemp[25];
	char cFreTemp[5];
	int lineCounter = 0;			//calculates how many lines are there in input.text
	int numTemp;
	int freTemp;
	int aDepth = 1;					//we will use this for calculating acces time
	int cDepth = 1;
	FILE *filePointer;				//file pointer
	filePointer = fopen("input.txt","r");		//opens the input.text
			
	while(!feof(filePointer)){					//until we reach end of the input.text loop will go on
		fgets(allTemp,35,filePointer);			//we take the every each line of input text and store it in allTemp
		
		strcpy(cNumTemp,strtok(allTemp,","));	//we seperate allTemp into cNumTemp, wordTemp, cFreTemp
		strcpy(wordTemp,strtok(NULL,","));
		strcpy(cFreTemp,strtok(NULL,","));
		numTemp=atoi(cNumTemp);					//cNumTemp and freTemp are string at the moment so we are converting them to integer
		freTemp=atoi(cFreTemp);

		if(numTemp == 1){						//if the numTemp = 1 it means it is the first element so we are assigning it as the root
			root = newElement(numTemp,wordTemp,freTemp);
		}
		else{									//else we are calling the treeBuilder to determine where we are gonna place our new element
			treeBuilder(numTemp,wordTemp,freTemp,root);
		}
		lineCounter++;							//line counter calculates how many line are there in input.text
	}
	printTree(root);							//after the while loop we have a tree so we are calling the printing function
	printf("Total time in a = %d\n",totalTimeCalculator(aDepth, root));			//we are printing the access time
	struct element elementArray[lineCounter];	//declairing the elementArray with size of lineCounter
	arrayBuilder(elementArray, root);			//building an array by using the tree
	sortArray(elementArray, lineCounter);		//bubble sort algorithm for sorting array
	begining = &elementArray[0];				//pointer points the 0th index of array
	arrayBBuilder(elementArray, begining, 0, lineCounter);		//creating a tree by using a sorted array
	printTree(begining);						//printing the tree
	totalTime = 0;								//reseting the total time
	printf("Total time in c = %d\n",totalTimeCalculator(cDepth, begining));		//calculates the total access time in c
	fclose(filePointer);						//closes the file
	return 0;
}

