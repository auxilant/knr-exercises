#include <string.h>

void reverse_r(char[], int);

void reverse(char s[]) {
	reverse_r(s, 0);	
}	

void reverse_r(char s[], int pos) {
	int pos_r =  strlen(s) - 1 - pos;
	if (pos >= pos_r) {
		return;
	}
	
	int tmp = s[pos];
	s[pos] = s[pos_r];
	s[pos_r] = tmp;
	
	reverse_r(s, pos+1);
}

