#include "../../include/common.h"
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        // 1. Display the prompt you requested
        printf("g18-shell> ");
        fflush(stdout);

        // 2. Read input
        if (!fgets(line, MAX_LINE, stdin)) break;

        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // 3. Tokenize input (split by spaces)
        int i = 0;
        args[i] = strtok(line, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            args[++i] = strtok(NULL, " ");
        }
        
        if (args[0] == NULL) continue; // Empty command

        // Built-in exit command
        if (strcmp(args[0], "exit") == 0) break;

        // 4. Create child process to run the command
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
        } else if (pid == 0) {
            // In Child Process
            // Look for the command in the bin folder
            char path[128];
            snprintf(path, sizeof(path), "./bin/%s", args[0]);
            
            execv(path, args);
            
            // If execv returns, it failed
            printf("Command '%s' not found in ./bin/\n", args[0]);
            exit(1);
        } else {
            // In Parent Process
            wait(NULL); // Wait for utility to finish
        }
    }

    return 0;
}