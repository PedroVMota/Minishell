#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void parent_handler(int sig) {
    printf("Custom handler in parent process for signal %d\n", sig);
    // Parent's custom handling logic here
}

void child_handler(int sig) {
    printf("Custom handler in child process for signal %d\n", sig);
    // Child's custom handling logic here
}

int main() {
    // Set a custom handler for SIGINT in the parent process
    signal(SIGINT, parent_handler);

    pid_t pid = fork();

    if (pid == -1) {
        // Handle fork error
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        // Set a different custom handler for SIGINT in the child process
        signal(SIGINT, child_handler);

        // Child's specific logic

        // Simulate some work in the child process
        sleep(5);

        // Child process completed
    } else {
		
		signal(SIGINT, SIG_IGN);
        // Parent process
        // Parent's specific logic

        // Simulate some work in the parent process
        sleep(10);
		printf("Sinal ignorado\n");
		signal(SIGINT, SIG_DFL);
		printf("Sinal default\n");
        sleep(10);

        // Parent process completed

        // Wait for the child to finish
        wait(NULL);
    }

    return 0;
}
