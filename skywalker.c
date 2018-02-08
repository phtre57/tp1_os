# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>

void child(void);
void parent(void);
int child_pid;

int main(){
	
	pid_t pid;
	pid = fork();
	if (pid == 0){ 
		child();
	}
	else{
		parent();
	}

	return 0;
}

void child(void){
	printf("\nNoooonn, je suis le processus %d\n", getpid());
	child_pid = getpid();
	sleep(120);
	exit(0);
	
}

void parent(void){
	printf("\nLuc! Je suis ton pere ton numero de processus est %d\n", child_pid);
	wait(0);
}
