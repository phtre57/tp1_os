# include <unistd.h>
# include <stdio.h>
int main() {
	printf("Numero de l’utilisateur: %d\n", getuid());
	printf("Numero du processus: %d\n", getpid());
	printf("Numero du processus parent: %d\n", getppid());
	printf("-Nom: ??votre nom??\n");

	return 0;

}
