#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


void func(char* str);
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
			strncat_s(ptr, l, buf, k);
		}
	} while (n > 0);
	return ptr;
}

int load(char* fname)
{
	FILE* fd;
	int t = 0;
	char* s = (char*)malloc(100);
	fopen_s(&fd, fname, "r");

	if (fd == NULL)
		return 0;
	while (t != EOF) {
		char* str = "\0";// (char*)malloc(99);
		str = fgetstr(fd);
		if (*str == '\0')
			break;
		str[strlen(str)] = '\0';
		func(str);
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
			strncat_s(ptr, l, buf, k);
		}
	} while (n > 0);
	return ptr;
}

char* find_format(char* str, char* format_str1, char* format_str2, int* ind) {
	char* s = str;
	*ind = 0;
	while (*s != '\0') {
		char* format = NULL;
		if (*s == *format_str1) {
			s++;
			char* f = format_str1 + 1;
			while (*s != '\0') {
				if (*s == *f) {
					format = format_str1;
					return format;
				}
				s++;
			}
			
		}
		else if (*s == *format_str2) {
			format = format_str2;
			return format;
		}
		s++;
		(*ind)++;
	}
	return NULL;
}

char* find_mask(char* str, char* format) {
	char* mask = (char*)calloc(1,sizeof(char));
	mask[0] = '\0';
	char* s = str;
	char* f = format;
	while (*s != '\0' && *f != '\0') {
		mask = (char*)realloc(mask, strlen(mask) + 2);
		mask[strlen(mask)+1] = '\0';
		if ( *f<=*s && *s <= '9') {
			f++;
			mask[strlen(mask)] = '1';
		}
		else
			mask[strlen(mask)] = '0';
		s++;
	}
	char* null_mask = (char*)malloc(strlen(mask) + 1);
	null_mask[strlen(mask)] = '\0';
	for (int i = 0; i < strlen(mask); i++)
		null_mask[i] = '0';
	//if (*f == '\0')
	//	free(null_mask);
	//else
	//	free(mask);
	return (*f == '\0') ? mask : null_mask;
}

int find_str(char* format, char* str) {
	char* s = str;
	char* f = format;
	while(*s != '\0' && *f != '\0'){
		if (*s == *f)
			f++;
		s++;
	}
	return (*f == '\0') ? 1 : 0;
}

void func(char* str) {
	char* format_str1 = "+74000000000";
	char* format_str2 = "84000000000";
	char* mask = (char*)malloc(1);
	char* m = "\0";
	mask[0] = '\0';
	while (*str != '\0') {
		int ind = 0;
		int truth = -1;
		char* format = find_format(str, format_str1, format_str2, &ind);
		if (format != NULL) {
			m = find_mask(str, format);
		}
		else {
			m = (char*)malloc(strlen(str) + 1);
			for (int i = 0; i < strlen(str); i++) {
				m[i] = '0';
			}
			m[strlen(str)] = '\0';
		}
		mask = strcat(mask, m);
		str += strlen(m);
	}
	printf("%s\n", mask);
	//free(mask);
	//free(str);
}

int main() {
	printf("Enter file name --> ");
	char* file_name = getstr();
	int* a = NULL;
	load(file_name);

}