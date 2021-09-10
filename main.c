#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "scaletoscale.h"
#include "passwordmask.h"



char* fgetstr(FILE* fd)
{
	char* ptr = (char*)malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	do {
		n = fscanf(fd, "%80[^\n]", buf);
		//if (n < 0) {
		//	free(ptr);
		//	ptr = NULL;
		//	continue;
			//break;
		//}
		if (n == 0) {
			fscanf(fd, "%*c");
			//break;
		}
		else if (n>0){
			len += strlen(buf);
			ptr = (char*)realloc(ptr, len + 1);
			int k = strlen(buf);
			int l = strlen(ptr) + k + 1;
			strncat(ptr,buf, k);
		}
	} while (n > 0);
	return ptr;
}

int load(char* fname)
{
	FILE* fd;
	int t = 0;
	fd = fopen(fname, "r");

	if (fd == NULL)
		return 0;
	while (t != EOF) {
		char* str = "\0";// (char*)malloc(99);
		str = fgetstr(fd);
		if (*str == '\0')
			break;
		str[strlen(str)] = '\0';
		char * mask;
		mask = mask_fun(str);
    printf("PASSWORD:\n%s\n\n", str);
		printf("MASK:\n%s\n\n",mask);
		char* hex = bintohex(mask);
		printf("MASK IN HEXADECIMAL:\n%s\n\n", hex);
		free(str);
		free(hex);
		hex=NULL;
		str = NULL;
		free(mask);
		mask = NULL;
		if (t > 0)
			t++;
	}
	fclose(fd);
	return 0;
}

char* getstr()
{
	char* ptr = (char*)malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			free(ptr);
			ptr = NULL;
			continue;
			break;
		}
		if (n == 0) {
			scanf("%*c");
			//break;
		}
		else {
			len += strlen(buf);
			ptr = (char*)realloc(ptr, len + 1);
			int k = strlen(buf);
			int l = strlen(ptr) + k + 1;
			strncat(ptr, buf, k);
		}
	} while (n > 0);
	return ptr;
}



int main() {
	printf("Enter file name --> ");
	char* file_name = getstr();
	load(file_name);
	free(file_name);
}
