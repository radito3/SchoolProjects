#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_stdin(void);
void read_file(const char*);
void read_files(char**, int);

// ran with gcc -Wall -Wpedantic -std=c11 tail.c
int main(int argc, char* argv[]) {
    switch (argc) {
        case 1:
            read_stdin();
            break;
        case 2:
            read_file(argv[1]);
            break;
        default: {
            char** files = &argv[1];
            read_files(files, argc - 1);
            break;
        }
    }
    return 0;
}

void read_stdin(void) {
    int num_lines = 0;
    int num_overflow = 0; // to act as a circular ring buffer
    char** lines = (char**) malloc(sizeof(char*) * 10);
    char* buffer = NULL;
    size_t buff_capacity = 0;
    ssize_t read;

    // getline() keeps the newline character in the buffer
    while ((read = getline(&buffer, &buff_capacity, stdin)) != -1) {
        if (num_lines < 10) {
            lines[num_lines] = (char*) malloc(sizeof(char) * read);
            memcpy(lines[num_lines++], buffer, read);
        } else {
            free(lines[num_overflow]);
            lines[num_overflow] = NULL;
            lines[num_overflow] = (char*) malloc(sizeof(char) * read);
            memcpy(lines[num_overflow++], buffer, read);
            if (num_overflow == 10) {
                num_overflow = 0; // loop to the beginning
            }
        }
    }
    free(buffer);

    printf("\n");
    for (int i = 0; i < num_lines; i++) {
        printf("%s", lines[(i + num_overflow) % num_lines]);
        free(lines[(i + num_overflow) % num_lines]);
    }
    free(lines);
}

void read_file(const char* file) {
    FILE* f = fopen(file, "r");
    if (!f) {
        perror("fopen");
        return;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    long chunk_size = 512 < size ? 512 : size;
    long total_offset = 0;
    int lines = 0;

    while (lines < 10 && total_offset < size) {
        fseek(f, -(chunk_size + total_offset), SEEK_CUR);
        char* buff = (char*) malloc(sizeof(char) * chunk_size);
        fread(buff, sizeof(char), chunk_size, f);

        for (int i = chunk_size - 1; i >= 0; i--) { // i needs to be a signed type, otherwise, an underflow occurs
            if (buff[i] == '\n' && ++lines > 10) {
                break;
            }
            total_offset++;
        }
        free(buff);
    }

    fseek(f, -total_offset, SEEK_END);
    char* buffer = NULL;
    size_t buff_capacity = 0;
    ssize_t read;

    while ((read = getline(&buffer, &buff_capacity, f)) != -1) {
        printf("%s", buffer);
    }
    free(buffer);

    fclose(f);
}

void read_files(char** files, int num_files) {
    for (int i = 0; i < num_files; i++) {
        if (strcmp(files[i], "-") == 0) {
            printf("==> stdin <==\n");
            read_stdin();
        } else {
            printf("==> %s <==\n", files[i]);
            read_file(files[i]);
        }
    }
}
