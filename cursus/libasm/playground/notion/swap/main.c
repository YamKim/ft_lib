#include <stdlib.h>
#include <stdio.h>
#if 0
void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
#endif
extern void swap(int *a, int *b);

int main(void) {
	int a = 4;
	int b = 2;

	swap(&a, &b);
	printf("a: %d, b: %d\n", a, b);

	return (0);
}
