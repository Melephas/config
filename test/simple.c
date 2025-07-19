#include <criterion/criterion.h>

#include "../src/config.h"


Test(simple, ) {
    const config_t* cfg = config_read_file("simple.ini");
    char* username = NULL;
    config_get(cfg, "user.name", &username);
}
