#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Linkedlist{
	char data[30];
	int row[100];
	int count;
	int i;
	struct Linkedlist *next;
} *node;

node createNode(char data[], int row){
	node temp;
	temp = (node)malloc(sizeof(struct Linkedlist));
	temp->next = NULL;
	strcpy(temp->data, data);
	temp->count = 1;
	temp->i=1;
	temp->row[0]=row;
	return temp;
}

node addTail(node head, char data[], int row){
	node p;
	node temp = createNode(data, row);
	if(head == NULL){
		head = temp;
	}
	else{
		p = head;
		while(p->next!=NULL){
			p=p->next;
		}
		p->next = temp;
	}
	return head;
}
