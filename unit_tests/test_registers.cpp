#include "min_unit.h"
#include <assert.h>
#include "../register.h"
#include <cstdio>

int tests_run = 0;
Register register1;

static char* test_set_hi() {
    register1.set_hi(0x49);
    char* message = "Hi bit set to wrong value\n"   ;
    mu_assert(message, register1.get_all() == 0x4900);
    return NULL;
}

static char* all_tests() {
    mu_run_test(test_set_hi);
    return NULL;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}