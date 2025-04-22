#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
	char c;
	pid_t pid;


	int fd = open("test.txt", O_RDWR);
	if (fd == -1) {
		perror("error opening file\n");
	}
	read(fd, &c, 1);
	printf("before the fork: %c\n", c);
	pid = fork();
	if (pid == -1) {
		perror("error fork()...\n");
	}

	if (pid == 0) { // child
		read(fd, &c, 1); // we want 4 here
		printf("child: %c\n", c);
	} else { // parent
		read(fd, &c, 1); // we want 4 here
		printf("parent: %c\n", c);
	}
	return 0;
}
