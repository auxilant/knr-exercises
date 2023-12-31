/* original loop:
	for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
		s[i] = c;
*/

#include <stdio.h>

main() {
	const int lim = 10;
	char c, s[lim];
	
	enum boolean { NO, YES };
	enum boolean readable = YES;

	int i = 0;

	while (readable) {
		if (i < lim-1) {
			c = getchar();
			if (c != '\n') {
				if (c != EOF) {
					s[i] = c;
					++i;
				} else {
					readable = NO;
				}
			} else {
				readable = NO;
			}
		} else {
			readable = NO;
		}
	}
	
	s[i+1]='\0';
	printf("%s\n", s);	

	return 0;
}
