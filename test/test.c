#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t child_id;

void sigparent(int sig) {
    const char msg[] = "The parent will kill the child.\n";

    switch (sig) {
    case SIGINT:
    case SIGQUIT:
        write(STDOUT_FILENO, msg, (sizeof msg) - 1);
        kill(child_id, SIGQUIT);
        break;
    default:
        break;
    }
}

void sigchild(int sig, siginfo_t *info, void *ctx) {
    const char msg[] = "The child will now die.\n";

    if (getppid() == info->si_pid)
        switch (sig) {
        case SIGINT:
        case SIGQUIT:
            write(STDOUT_FILENO, msg, (sizeof msg) - 1);
            _exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
}

void parent(void) {
    signal(SIGINT, sigparent);
    signal(SIGQUIT, sigparent);

    puts("Parent will wait...");
    waitpid(child_id, NULL, WUNTRACED);
    puts("Parent is done waiting.");
}

void child(void) {
    struct sigaction action;

    sigemptyset(&action.sa_mask);
    action.sa_flags = (SA_SIGINFO);
    action.sa_sigaction = sigchild;

    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);

    while (1) {
        puts("Child is sleeping...");
        sleep(2);
    }
}

int main(void) {
    if ((child_id = fork()))
        parent();
    else
        child();
}
