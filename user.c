#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3

int main() {
    printf("Parent PID: %d\n", getpid());

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process
            printf("Child %d PID: %d, Parent PID: %d\n", i + 1, getpid(), getppid());
            sleep(10); // Keep child alive for visibility
            exit(0);
        }
    }

    // Parent waits for all children
    for (int i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    sleep(5); // Allow time to inspect the process tree
    return 0;
}
