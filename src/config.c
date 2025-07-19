#include "config.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


static char* read_file(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    const int64_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = calloc(size + 1, sizeof(char));
    if (!buffer) {
        return NULL;
    }

    fread(buffer, sizeof(char), size, file);
    fclose(file);

    return buffer;
}

/// read_section_header() receives a pointer to the start of a line and copies
/// the section header to a newly allocated buffer
/// @param content A pointer to the start of the line
/// @return The name of the section header, or NULL if invalid
static char* read_section_header(const char* content) {
    if (!content || content[0] != '[') {
        return NULL;
    }


}

config_t* config_read_file(const char* filepath) {
    const char* file_content = read_file(filepath);
    if (file_content == NULL) {
        return NULL;
    }

    config_value_t* values = malloc(sizeof(config_value_t));

    char*

    const char* idx = file_content;
    while (*idx != '\0') {
        if (*idx == '[') {

        }
    }

    config_t* ret = malloc(sizeof(config_t));
    
}

void config_free(config_t* cfg) {}


void config_get_int(const config_t* cfg, const char* name, int* value) {}

void config_get_double(const config_t* cfg, const char* name, double* value) {}

void config_get_bool(const config_t* cfg, const char* name, bool* value) {}

void config_get_string(const config_t* cfg, const char* name, char** value) {}