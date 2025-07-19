#ifndef CONFIG_H
#define CONFIG_H

#ifndef CONFIG_HEADER_MAX
#define CONFIG_HEADER_MAX 1024
#endif

#ifndef CONFIG_NAME_MAX
#define CONFIG_NAME_MAX 1024
#endif

#ifndef CONFIG_VALUE_MAX
#define CONFIG_VALUE_MAX 1024
#endif

#include <stdbool.h>
#include <stddef.h>


typedef struct {
    char* section;
    char* name;
    char* value;
} config_value_t;

typedef struct {
    config_value_t* values;
    size_t count;
} config_t;


config_t* config_read_file(const char* filepath);
void config_free(config_t* cfg);

void config_get_int(const config_t* cfg, const char* name, int* value);
void config_get_double(const config_t* cfg, const char* name, double* value);
void config_get_bool(const config_t* cfg, const char* name, bool* value);
void config_get_string(const config_t* cfg, const char* name, char** value);

#define config_get(C, N, TV) _Generic((TV),\
    int*: config_get_int,\
    double*: config_get_double,\
    bool*: config_get_bool,\
    char**: config_get_string\
    )(C, N, TV)

#endif
