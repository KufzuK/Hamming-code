#include <stdio.h>
 
int main(void) {
	char line[3] = "012";
	printf("Hello world!\n");
    printf("\x1B[38;2;255;0;0m");
	printf("%s\n", line);
	printf("\x1B[0m");
    printf("YASOSYBIBY\n");
	return 0;
}
