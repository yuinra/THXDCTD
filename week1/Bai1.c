#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include <ctype.h>

int checkProperNoun(int i, FILE *fin){
	char a[4] = ""; 
	fseek(fin, i-2, SEEK_SET);
	fgets(a, 4, fin);
	fseek(fin, i, SEEK_SET);
	if(a[0]!='.'&&(int)a[2]>=65&&(int)a[2]<=90){
		return 1;
	}

	return 0;
}

node checkInList(node p[], node new){
	node tmp = p[(int)new->data[0]];
	while(tmp!=NULL){
		if(strcmp(new->data, tmp->data)==0){return tmp;} 
		tmp=tmp->next;
	}
	return tmp;
}

int checkInStopw(node stopw[], node new){
	node tmp = stopw[(int)new->data[0]];
	while(tmp!=NULL){
		if(strcmp(new->data, tmp->data)==0){
			return 1;
		}
		tmp=tmp->next;
	}
	return 0;
}

void readFile(char *filename, node p[], node stopw[]){
	FILE *fin = fopen(filename, "r");
	int i = 0, row = 1, check = 0;
	if(fin==NULL){
		printf("ERROR!\n");
	}
	else{
		char tmp[100] = "";
		while(!feof(fin)){
			char a[100] = ""; 
			a[0] = fgetc(fin);
			if(a[0]=='\n'){row++;}
			i++;
			if(isalpha(a[0])){
				a[0] = tolower(a[0]);
				strcat(tmp, a);
			}
			else{
				if(a[0]==' '){if(checkProperNoun(i, fin)){
					char x[100];check++;
					fscanf(fin, "%s", x);
					i=i+strlen(x);}} //check danh tu rieng
				if(strcmp(tmp, "")!=0){
					node new = createNode(tmp, row);
					if(p[(int)tmp[0]]==NULL){
						p[(int)tmp[0]]=new;
					}
					else{
						if(checkInStopw(stopw, new)!=1){
						node t = checkInList(p, new);
							if(t!=NULL){
								t->count++;
								t->row[t->i]=row;
								t->i++;
							}
							else{
								addTail(p[(int)tmp[0]], tmp,  row);
							}
						}
					}
				}
				strcpy(tmp, "");
			}
		}
	}
	fclose(fin);
}

void readList(char *filename, node p[]){
	FILE *fin = fopen(filename, "r");
	char s[100];
	if(fin==NULL){
		printf("ERROR!\n");
	}
	else{
		while(!feof(fin)){
			fscanf(fin, "%s\n", s);
			if(p[(int)s[0]]==NULL){
				p[(int)s[0]] = createNode(s, 0);
			}
			else{
				addTail(p[(int)s[0]], s, 0);
			}
		}
	}
}




int main(){
	node p[123];
	node stopw[123];
	int i;
	for(i = 97;i<=122;i++){
		p[i]=NULL;
		stopw[i]=NULL;
	}
	
	readList("stopw.txt", stopw);
	readFile("vanban.txt", p, stopw);
	for(i = 97;i<=122;i++){
		if(p[i]!=NULL){
			node tmp = p[i];
			while(tmp!=NULL){
				int j;
				printf("%s, %d", tmp->data, tmp->count);
				for(j=0;j<tmp->i;j++){
					printf(", %d", tmp->row[j]);
				}
				tmp=tmp->next;
				printf("\n");
			}
		}
		
	}
}


