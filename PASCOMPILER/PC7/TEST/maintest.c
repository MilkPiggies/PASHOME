#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void copy_and_modify_file(const char *filename) {
    FILE *source_file = fopen(filename, "r");
    if (!source_file) {
        perror("Failed to open source file");
        return;
    }

    // Create new filename with .temp extension
    char temp_filename[256];
    snprintf(temp_filename, sizeof(temp_filename), "%s.temp", filename);

    FILE *temp_file = fopen(temp_filename, "w");
    if (!temp_file) {
        perror("Failed to create temp file");
        fclose(source_file);
        return;
    }

    char line[256];
    int line_count = 0;

    // Read lines from the source file and write to temp file
    while (fgets(line, sizeof(line), source_file)) {
        fprintf(temp_file, "%s", line);
        line_count++;
    }

    fclose(source_file);
    fclose(temp_file);

    // Now modify the temp file to remove the first and last lines
    source_file = fopen(temp_filename, "r");
    if (!source_file) {
        perror("Failed to open temp file");
        return;
    }

    // Create a new temporary file to store modified content
    FILE *modified_file = fopen("modified.temp", "w");
    if (!modified_file) {
        perror("Failed to create modified file");
        fclose(source_file);
        return;
    }

    int current_line = 0;
    while (fgets(line, sizeof(line), source_file)) {
        if (current_line > 0 && current_line < line_count - 1) {
            fprintf(modified_file, "%s", line);
        }
        current_line++;
    }

    fclose(source_file);
    fclose(modified_file);

    // Optionally, rename modified.temp to the original temp filename
    remove(temp_filename); // Remove the original temp file
    rename("modified.temp", temp_filename); // Rename modified file
}

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (!dir) {
        perror("Failed to open directory");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Check if the file starts with an underscore
        if (entry->d_name[0] == '_') {
            copy_and_modify_file(entry->d_name);
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}

