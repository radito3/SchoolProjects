#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

char** parse_cmdline(const char*);
unsigned int count_words(const char*);
void run_command(char**);
void free_cmdline(char**);

int main(int argc, char* argv[]) {
    char* buffer = NULL;
    size_t buff_capacity = 0;
    ssize_t read;

    printf("$ ");
    while ((read = getline(&buffer, &buff_capacity, stdin)) != -1) {
        buffer[read-1] = '\0'; // truncate the newline kept by getline()
        char** cmdline = parse_cmdline(buffer);
        if (cmdline != NULL) {
            run_command(cmdline);
            free_cmdline(cmdline);
        }
        printf("$ ");
    }
    free(buffer);

    return 0;
}

char** parse_cmdline(const char* line) {
    unsigned int num_words = count_words(line);
    if (num_words == 0) {
        return NULL;
    }

    char* duplicated = strdup(line);
    char* line_copy = duplicated;
    char** words = (char**) malloc(sizeof(char*) * (num_words + 1)); // +1 for the final NULL
    int word_idx = 0;
    char* word;

    while ((word = strsep(&line_copy, " ")) != NULL) {
        if (*word != '\0') { // skip empty tokens
            words[word_idx++] = strdup(word);
        }
    }
    words[word_idx] = NULL;

    free(duplicated);
    return words;
}

unsigned int count_words(const char* str) {
    unsigned int count = 0;
    int in_word = 0;
    
    for (; *str != '\0'; str++) {
        if (!isspace(*str)) {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }
    return count;
}

void run_command(char** cmd) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }
    if (pid == 0) {
        // execv() will not read PATH, so it will expect a full path to an executable file
        // execvp() is more convenient
        execvp(cmd[0], cmd);
        perror("execv");
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return;
        }
        if (!WIFEXITED(status)) {
            fprintf(stderr, "program didn't terminate normally\n");
            return;
        }
        if (WEXITSTATUS(status) != 0) {
            fprintf(stderr, "%s exited with status %d\n", cmd[0], WEXITSTATUS(status));
            return;
        }
    }
}

void free_cmdline(char** cmdline) {
    for (int i = 0; cmdline[i] != NULL; i++) {
        free(cmdline[i]);
    }
    free(cmdline);
}
