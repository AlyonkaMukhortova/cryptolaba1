#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "passwordmask.h"

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
	char* mask = (char*)malloc(1);
	if(mask == NULL)
		printf("ERR 126");
	mask[0] = '\0';
	char* s = str;
	char* f = format;
	while (*s != '\0' && *f != '\0') {
		int l = strlen(mask);
		//printf("%d\n", l);
		mask = (char*)realloc(mask, l + 2);
		if(mask == NULL)
			printf("ERR 133");
		mask[l+1] = '\0';
		if ( *f<=*s && *s <= '9') {
			f++;
			mask[l] = '1';
		}
		else
			mask[l] = '0';
		s++;
	}
	int k = strlen(mask);
	if (*f != '\0')
		for (int i = 0; i < k; i++)
			mask[i] = '0';
		mask[k] = '\0';

	return mask;
}

char* mask_fun(char* str) {
	char* s = str;
	char* format_str1 = "+74000000000";
	char* format_str2 = "84000000000";
	char* mask = (char*)malloc(1);
	if(mask == NULL)
		printf("ERR 157");
	char* m = "\0";
	mask[0] = '\0';
	while (*str != '\0') {
		int size = strlen(str);
		int ind = 0;
		int truth = -1;
		char* format = find_format(str, format_str1, format_str2, &ind);
		if (format != NULL) {
			m = find_mask(str, format);
		}
		else {
			m = (char*)malloc(size + 1);
			if(m == NULL)
				printf("ERR 169");
			for (int i = 0; i < size; i++) {
				m[i] = '0';
			}
			m[size] = '\0';
		}
		int ms = strlen(mask);
		int sm = strlen(m);
		mask = (char*)realloc(mask, sm + ms + 1);
		if(mask == NULL)
			printf("ERR 178");
		mask = strncat(mask, m, sm);
		str += sm;
		free(m);
		m = NULL;
	}
	//free(mask);

	//mask = NULL;
	str = s;
	//str = NULL;
	return mask;
}
