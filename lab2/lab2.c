#include "lab2.h"

int main()
{
    char str[] = "201040";
    char hex[] = "123456789h";
    State * b10_state = new_state();
    b10_state->count = 6;
    State * hex_state = new_state();
    hex_state->base = 16;
    hex_state->count = 9;

    printf("%s: %s\n", str, sum(str, b10_state));
    printf("%s: %s\n", hex, sum(hex, hex_state));
    
    return 0;
}
