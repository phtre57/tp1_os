# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int main(){

	char* ptr = (char*) malloc(25);
	free(ptr);
	free(ptr);
	printf("test");

	return 0;
}

