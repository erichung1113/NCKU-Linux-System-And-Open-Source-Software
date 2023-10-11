#include "../include/strcpy.h"

int len(const char *str){
	int len=0;
	while(str[len]) len++;
	return len;
}

char *sstrcpy(char *dest, const char *src)
{
	int n = len(dest);
	int m = len(src);
	for(int i = 0; i < m; i++){
		dest[n++]=src[i];
	}
	dest[n]='\0';
	return dest;
}
