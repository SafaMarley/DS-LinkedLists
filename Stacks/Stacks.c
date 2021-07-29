//Mehmet Safa Katýrcýoðlu 150118047
#include <stdio.h>
#include <stdlib.h>

struct StackNode {
	char data;
	struct StackNode* next;
};

struct StackNode* newNode(int data) {
	struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
	stackNode->data = data;
	stackNode->next = NULL;
	return stackNode;
}

int isEmpty(struct StackNode* root) {
	if(&root->data == NULL) {
		return 1;
	}
	
	else {
		return 0;
	}
}

int isOperand(char ch) {
	return (ch >= '0' && ch <= '9');
}

int isOperator(char ch) {
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
		return 1;
	}
	return 0;
}

int precedence(char ch) {		//This function determines the precedence of the operation
	switch(ch) {
		case'+':
		case'-':
		return 1;
		
		case'*':
		case'/':
		return 2;
		
		case'^':
		return 3;
	}
	return -1;
}

void push(struct StackNode** root, char data) {			//pushes data to stack
	struct StackNode* stackNode = newNode(data);
	stackNode->next = *root;
	*root = stackNode;
}

char pop(struct StackNode** root) {			//pops an element from stack returns the popped item's data
	
    if (isEmpty(*root)) {
 	}
 	
 	else {
 		struct StackNode* temp = *root;
    	*root = (*root)->next;
    	char popped = temp->data;
    	free(temp);
    	return popped;
	}

}

int main() {		//in main all of the functions are being called and for different inputs code done it's job so i don't think test code is needed
	struct StackNode* root = NULL;
	FILE *fPointer;
	fPointer = fopen("infix_input.txt", "r");		//reads file
	char character = fgetc(fPointer);
	push(&root, '$');								//we are pushing a symbol to stack so this way when we are calculating the precedence we are avoiding the error for 1st comparison 
	
	while(character != EOF) {
		
		if(isOperand(character)) {					//if it's an operand write it on screen
			printf("%c", character);
		}
		
		else if(character == '(') {
			push(&root, character);
		}
		
		else if(isOperator(character)) {				//if its an operator compare the precedence
			if(precedence(root->data) >= precedence(character)) {	//if there is a operation waiting in stack with higher precedence pop it
				printf("%c", pop(&root));
			}
			push(&root, character);				//push the operation to stack
		}
		
		else if(character == ')') {			//when paranthesis is closed pop until opening paranthesis
			
			while(root->data != '(') {
				printf("%c", pop(&root));
			}
			pop(&root);
		}
		
		character = fgetc(fPointer);
	}
	
	while(root->data != '$') {			//write the last operation to screen
		printf("%c", pop(&root));
	}
	fclose(fPointer);
	
	return 0;
}

