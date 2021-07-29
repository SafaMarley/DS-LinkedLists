//Mehmet Safa Katýrcýoðlu 150118047
#include <stdio.h>
#include <stdlib.h>

struct StackNode {			//This is our node struct
	int data;
	struct StackNode* next;
};

struct StackNode* newNode(int data) {		//This function let's us to create new node in type StackNode
	struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
	stackNode->data = data;
	stackNode->next = NULL;
	return stackNode;
}

int isEmpty(struct StackNode* root) {		//If our stack is empty this function returns 1, if it is not function returns 0
	if(&root->data == NULL) {
		return 1;
	}
	
	else {
		return 0;
	}
}

void push(struct StackNode** root, int data) {	//This function pushes the given data to stack by creating a new node for it
	struct StackNode* stackNode = newNode(data);
	stackNode->next = *root;
	*root = stackNode;
	printf("%d has been pushed to stack.\n", data);	//Informing user to saying that the function is completed
}

void pop(struct StackNode** root) {	//This function pops the node from stack if stack is empty function imforming the user
	
    if (isEmpty(*root)) {
    	printf("Stack is empty.\n");
 	}
 	
 	else {
 		struct StackNode* temp = *root;
    	*root = (*root)->next;
    	int popped = temp->data;
    	free(temp);
    	printf("%d has been popped from the stack.\n", popped);	//Informing user to saying that the function is completed
	}

}

int main() {		//In main function user building the stack by his/her desire
	int selection;
	struct StackNode* root = NULL;
	
	while (selection != 3) {
		printf("Select the stack function\n1-Push\n2-Pop\n3-Exit\n");
		scanf("%d",&selection);
		
		if(selection == 1) {
			int data;
			printf("Enter an integer to push.\n");
			scanf("%d", &data);
			push(&root, data);
		}
		
		else if(selection == 2) {
			pop(&root);
		}
		
		else if(selection == 3) {
			printf("Exiting....");
		}
		
		else {
			printf("Enter a valid input.\n");
		}
	}
	
	return 0;
}

