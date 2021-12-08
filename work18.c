#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WRITE 1
#define READ 0


int main() {
	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	int f = fork();
	if (f) {
		close(pipe1[READ]);
		close(pipe2[WRITE]);
		while (1) {
			char input[200];
			input[0] = '\0';
			printf("input a string: ");
			fgets(input, 200, stdin);
			write(pipe1[WRITE], input, strlen(input));
			char output[200];
			read(pipe2[READ], output, 200);
			printf("output: %s\n", output);
		}
	}
	else {
		close(pipe1[WRITE]);
		close(pipe2[READ]);
		while (1) {
			char input[200];
			read(pipe1[READ], input, 200);
			int i;
			for (i = 0; i < strlen(input); i++) {
				input[i] = input[i] + 1;
			}
			write(pipe2[WRITE], input, 200);
		}
	}
	return 0;
}
