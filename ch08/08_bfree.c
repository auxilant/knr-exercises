#include "07_malloc.c"

void bfree(void *p, unsigned size) {
	Header *bp;
	bp = (Header *)p - 1;
	unsigned oldsize = bp->s.size;
	unsigned newsize = (size + sizeof(Header) - 1)/sizeof(Header) + 1;

	bp->s.size = newsize;
	free(p);
	bp += newsize;
	bp->s.size = oldsize - newsize - 1; 
}
