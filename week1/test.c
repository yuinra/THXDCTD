#include <stdio.h>


int main(){
	int row = 1;
	FILE *fin = fopen("vanban.txt", "r");
	while(!feof(fin)){
		char a = fgetc(fin);
		if(a=='\n'){
			row++;
		}
	}
	printf("%d\n", row);
}