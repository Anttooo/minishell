#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    while (1) {
        input = readline("Enter a line (or type 'quit' to exit): ");
        if (!input) {
            printf("\n");
            break;
        }

        if (strcmp(input, "quit") == 0) {
            free(input);
            break;
        }

        if (strcmp(input, "clear_history") == 0) {
            rl_clear_history();
        } else if (strcmp(input, "new_line") == 0) {
            rl_on_new_line();
        } else if (strcmp(input, "replace_line") == 0) {
            rl_replace_line("This line is replaced.", 1);
            rl_redisplay();
        } else {
            add_history(input);
        }
        free(input);
    }

    return 0;
}
