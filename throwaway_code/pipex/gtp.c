#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    // Split the command into separate commands based on the pipe characters
    char *commands[num_pipes + 1];
    commands[0] = strtok(command, "|");
    for (int i = 1; i <= num_pipes; i++) {
        commands[i] = strtok(NULL, "|");
    }

    // Execute each command in a separate child process
    pid_t pid;
    int stdin_fd = 0;  // Initially set to stdin
    for (int i = 0; i <= num_pipes; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (i < num_pipes) {
                // Redirect stdout to the write end of the pipe
                if (dup2(pipes[i][WRITE_END], STDOUT_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }
            if (i > 0) {
                // Redirect stdin to the read end of the previous pipe
                if (dup2(stdin_fd, STDIN_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }
            // Close all unused pipe ends
            for (int j = 0; j < num_pipes; j++) {
                if (j != i - 1 && j != i) {
                    close(pipes[j][READ_END]);
                    close(pipes[j][WRITE_END]);
                }
            }
            // Execute the command
            execlp(commands[i], commands[i], NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            if (i > 0) {
                // Close the read end of the previous pipe
                close(pipes[i - 1][READ_END]);
            }
            if (i < num_pipes) {
                // Keep the write end of the current pipe open for the next command
                stdin_fd = pipes[i][READ_END];
            }
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i <= num_pipes; i++) {
        wait(NULL);
    }

    return 0;
}
